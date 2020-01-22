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
    if(value < grass_max_range) {
      return Grass;
    }
  }
};