//
// Created by deck on 8/20/25.
//

#include "sanitizer.h"

#include <string>
#include <string_view>
#include <regex>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <cctype>

static std::wstring utf8_to_wstring(const std::string& s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(s);
}

static std::string wstring_to_utf8(const std::wstring& ws) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(ws);
}

static std::wstring strip_diacritics_and_symbols(std::wstring in) {
    std::wstring out;
    out.reserve(in.size());

    auto to_ascii_cz = [](wchar_t c) -> wchar_t {
        switch (c) {
            case L'á': case L'ä': return L'a';
            case L'č':            return L'c';
            case L'ď':            return L'd';
            case L'é': case L'ě': return L'e';
            case L'í':            return L'i';
            case L'ľ': case L'ĺ': return L'l';
            case L'ň':            return L'n';
            case L'ó': case L'ö': return L'o';
            case L'ř':            return L'r';
            case L'š':            return L's';
            case L'ť':            return L't';
            case L'ú': case L'ů': case L'ü': return L'u';
            case L'ý':            return L'y';
            case L'ž':            return L'z';

            case L'Á': case L'Ä': return L'A';
            case L'Č':            return L'C';
            case L'Ď':            return L'D';
            case L'É': case L'Ě': return L'E';
            case L'Í':            return L'I';
            case L'Ľ': case L'Ĺ': return L'L';
            case L'Ň':            return L'N';
            case L'Ó': case L'Ö': return L'O';
            case L'Ř':            return L'R';
            case L'Š':            return L'S';
            case L'Ť':            return L'T';
            case L'Ú': case L'Ů': case L'Ü': return L'U';
            case L'Ý':            return L'Y';
            case L'Ž':            return L'Z';
            default:              return c;
        }
    };

    for (wchar_t c : in) { // whitespace
        if (c == 0x00A0 || c == L'\t' || c == L'\n' || c == L'\r' || c == L'\v' || c == L'\f') {
            out.push_back(L' ');
            continue;
        }

        if (c == 0x2013 /*–*/ || c == 0x2014 /*—*/ || c == 0x2212 /*−*/) {
            out.push_back(L'-');
            continue;
        }

        if (c == 0x201C /*“*/ || c == 0x201D /*”*/ || c == 0x201E /*„*/ || c == 0x201F /*‟*/ ||
            c == 0x00AB /*«*/ || c == 0x00BB /*»*/ || c == 0x2039 /*‹*/ || c == 0x203A /*›*/ ||
            c == 0x2018 /*‘*/ || c == 0x2019 /*’*/) {
            continue;
        }

        wchar_t mapped = to_ascii_cz(c);
        out.push_back(mapped);
    }
    return out;
}

static void trim_dashes(std::string& s) {
    while (!s.empty() && s.front() == '-') s.erase(s.begin());
    while (!s.empty() && s.back() == '-') s.pop_back();
}

std::string sanitize(const std::string_view sv_input) {
    const std::string input(sv_input);

    std::wstring w = utf8_to_wstring(input);
    w = strip_diacritics_and_symbols(std::move(w));
    std::string s = wstring_to_utf8(w);

    static const std::regex re_ws("\\s+");
    s = std::regex_replace(s, re_ws, " ");

    static const std::regex re_slash_spaces("\\s*/\\s*");
    s = std::regex_replace(s, re_slash_spaces, "/");

    static const std::regex re_dash_spaces("\\s*(-+)\\s*");
    s = std::regex_replace(s, re_dash_spaces, "$1");

    static const std::regex re_multiple_dashes("-{2,}");
    s = std::regex_replace(s, re_multiple_dashes, "-");

    std::replace(s.begin(), s.end(), '.', '-');
    std::replace(s.begin(), s.end(), ' ', '-');

    std::string filtered;
    filtered.reserve(s.size());
    for (unsigned char ch : s) {
        if ((ch >= '0' && ch <= '9') ||
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            ch == '/' || ch == '-' || ch == '_') {

            filtered.push_back(static_cast<char>(ch));
        }
    }

    static const std::regex re_multi_dash_after("-{2,}");
    filtered = std::regex_replace(filtered, re_multi_dash_after, "-");

    trim_dashes(filtered);

    return filtered;
}
