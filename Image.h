#include <vector>
#include <string>
#include <fstream>

namespace TerrGen {
  struct Color {
    double r,g,b;

    Color(int r_, int g_, int b_):r(r_),g(g_),b(b_){}
    Color():r(0),g(0),b(0){}
    Color(int c):r(c),g(0),b(0){}
  };
  
  struct Image {
    int w,h;
    std::vector<Color> pixels;

    Image(int w_, int h_):w(w_),h(h_){}
    Image():w(800),h(800){}

    void SetPixel(int x, int y, const Color color) {
      pixels[x+y*w] = color;
    }

    void ppm_out(std::string filename) const {
      std::fstream file(filename);
    }
  };
};