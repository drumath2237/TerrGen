#include <string>

#include "Vector2.h"
#include "Image.h"
#include "PerlinNoise.h"

namespace TerrGen {
  enum Biome {
    Water,
    Sand,
    Grass,
  };
  
  struct TerrainGenerator {
    PerlinNoise noise;
    Image img;
    std::string seed;

    TerrainGenerator(std::string seed);
    void RenderTerrain();
    Biome JudgeBiome(double);
    int SeedConverter(std::string);
  };

  int TerrainGenerator::SeedConverter(std::string seed) {
    int res = 0;
    for(int i=0; i<seed.size(); i++) {
      res += seed[i];
    }

    return res;
  }

  TerrainGenerator::TerrainGenerator(std::string seed_):
  seed(seed_),
  noise(PerlinNoise(SeedConverter(seed_))),
  img(Image()){}

  Biome TerrainGenerator::JudgeBiome(double value) {
    double water_max_range = -0.5;
    double sand_max_range = 0.3;
    double grass_max_range = 1.0;

    if(value < water_max_range) {
      return Water;
    }
    if(value < sand_max_range) {
      return Sand;
    }
    else {
      return Grass;
    }
  }

  void TerrainGenerator::RenderTerrain() {
    for(int j=0; j<img.h; j++) for(int i=0; i<img.w; i++) {
      double x = (double)noise.grid_count/(double)img.w;
      double y = (double)noise.grid_count/(double)img.h;

      switch(JudgeBiome(noise.Noise(x,y))){
        case Water:
          img.SetPixel(i,j, Color(0,0,255));
        case Sand:
          img.SetPixel(i,j,Color(240,221,195));
        case Grass:
          img.SetPixel(i,j,Color(0,255,0));
      }
    }

    img.ppm_out(seed);
  }
};