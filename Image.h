#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace TerrGen {
  struct Color {
    double r,g,b;

    Color(int r_, int g_, int b_):r(r_),g(g_),b(b_){}
    Color():r(0),g(0),b(0){}
    Color(int c):r(c),g(c),b(c){}
  };
  
  struct Image {
    int w,h;
    std::vector<Color> pixels;

    Image(int w_, int h_):w(w_),h(h_){ pixels = std::vector<Color>(w_*h_); }
    Image():w(400),h(400){ pixels = std::vector<Color>(400*400); }

    void SetPixel(int x, int y, const Color color) {
      pixels[x+y*w] = color;
    }

    Color GetPixel(int x, int y) const {
      return pixels[x+y*w];
    }

    void ppm_out(std::string filename) const {
      std::ofstream file(filename);

      file << "P3" << std::endl;
      file << w << " " << h << std::endl;
      file << "255" << std::endl;

      for(int y=0; y<h; y++) for(int x=0; x<w; x++) {
        file << GetPixel(x,y).r << " "
             << GetPixel(x,y).g << " "
             << GetPixel(x,y).b
             << std::endl;
      }
    }
  };
};