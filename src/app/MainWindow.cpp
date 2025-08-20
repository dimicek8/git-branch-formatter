//
// Created by deck on 8/20/25.
//

#include "app/MainWindow.h"

#include <FL/fl_ask.H>
#include <FL/Fl.H>
#ifndef _WIN32
    #include <FL/Fl_PNG_Image.H>
#endif

#include <cstring>
#include "core/sanitizer.h"

MainWindow::MainWindow(int w, int h, const char *title) : Fl_Window(w, h, title) {
#ifndef _WIN32
    std::string iconPath = std::string(RESOURCE_DIR) + "/resources/icon.png";
    app_icon_ = new Fl_PNG_Image(iconPath.c_str());
    if (!app_icon_->fail()) {
        this->icon(app_icon_);
    }
#endif

    begin();

    input_ = new Fl_Input(20, 30, w - 40, 30, "Vstup:");
    input_->align(FL_ALIGN_TOP_LEFT);
    input_->callback(&MainWindow::InputChangedCb, this);
    input_->when(FL_WHEN_CHANGED);

    output_ = new Fl_Output(20, 90, w - 140, 30, "Výstup:");
    output_->align(FL_ALIGN_TOP_LEFT);

    copy_ = new Fl_Button(w - 110, 90, 90, 30, "Kopírovat");
    copy_->callback(&MainWindow::CopyClickedCb, this);

    end();
    resizable(this);
}

void MainWindow::InputChangedCb(Fl_Widget *, void *userdata) {
    static_cast<MainWindow*>(userdata)->onInputChanged();
}
void MainWindow::CopyClickedCb(Fl_Widget *, void *userdata) {
    static_cast<MainWindow*>(userdata)->onCopyClicked();
}

void MainWindow::onInputChanged() {
    const char* text = input_->value();
    std::string out = sanitize(text);
    output_->value(out.c_str());
}

void MainWindow::onCopyClicked() {
    const char* text = output_->value();
        Fl::copy(text, std::strlen(text), 1);
}

MainWindow::~MainWindow() {
#if !defined(_WIN32)
    delete app_icon_;
    app_icon_ = nullptr;
#endif
}