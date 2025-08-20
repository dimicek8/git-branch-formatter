//
// Created by deck on 8/20/25.
//

#pragma once
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <string>
#include <FL/Fl_PNG_Image.H>

class MainWindow: public Fl_Window {
public:
    MainWindow(int w, int h, const char* title);
    ~MainWindow() override;

private:
    Fl_Input* input_ = nullptr;
    Fl_Output* output_ = nullptr;
    Fl_Button* copy_ = nullptr;

    Fl_PNG_Image* icon_ = nullptr;

    void onInputChanged();
    void onCopyClicked();

    static void InputChangedCb(Fl_Widget*, void* userdata);
    static void CopyClickedCb(Fl_Widget*, void* userdata);
};
