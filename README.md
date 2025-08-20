# Branch Formatter

A lightweight **desktop utility** (Windows & Linux/SteamOS) built with **C++17** and **FLTK** that helps developers generate clean and consistent **Git branch names**.

---

## 📖 About the Project

When working with Git and GitHub, branch names often contain spaces, diacritics (like `ěščřžýáíé`), or unwanted symbols that make them invalid or inconsistent.  
**Branch Formatter** solves this by providing a small GUI tool where you can paste a branch name idea and instantly get a sanitized, copy-ready branch name.

---

## 🛠️ Technologies Used

- **C++17** — core application logic
- **FLTK** — lightweight cross-platform GUI library
- **CMake + Ninja** — build system
- **Regex + string processing** — for sanitization logic
- **Cross-platform support**: runs on Linux (SteamOS/Arch) and Windows (via MinGW or GitHub Actions)

---

## ✨ Features

- Converts Czech/Slovak diacritics to ASCII (e.g., `Řešení` → `Reseni`)
- Removes or replaces special symbols (`.`, `–`, quotes, etc.)
- Collapses multiple spaces into one
- Converts spaces into `-` (hyphens)
- Replaces sequences like `.-` or `-.` with `-`
- Collapses multiple hyphens (`--`, `---`) into a single `-`
- Trims leading/trailing hyphens
- **Copy button**: one click to copy the result to clipboard
- Custom application icon

---

## 🔍 Example
- Input: **feat/FIRM-2548 - Řešení problému -s chybějícím -- nápisem**
- Output: **feat/FIRM-2548-Reseni-problemu-s-chybejicim-napisem**