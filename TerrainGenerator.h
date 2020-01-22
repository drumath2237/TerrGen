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

    TerrainGenerator(std::string seed);
    void RenderTerrain();
    Biome JudgeBiome(double);
  };
};