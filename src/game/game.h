#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>

namespace Game {
  //class MainWindow : public Fl_Window {
  //public:
  //      MainWindow() : Fl_Window(200, 100, 300, 300, "Hello world (drawing)") {
  //          resizable(this);
  //      }
  //};
  class MainWindow {
    public:
        MainWindow() {
            Fl_Window window(200, 100, 300, 300, "Hello world (drawing)");
            window.resizable(&window);
            window.show();
        }
        void show() {}
  };
}

