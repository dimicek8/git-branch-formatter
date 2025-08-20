#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include "app/MainWindow.h"

int main(int argc, char** argv) {
    MainWindow win(660, 160, "GIT branch formatter");
    win.show(argc, argv);

    return Fl::run();
}