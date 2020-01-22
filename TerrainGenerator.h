#pragma once

#include <string>
#include <iostream>

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
    int SeedConverter(std::string)const;
  };

  int TerrainGenerator::SeedConverter(std::string seed) const {
    int res = 0;
    for(int i=0; i<seed.size(); i++) {
      res += (int)seed[i];
    }

    return res;
  }

  TerrainGenerator::TerrainGenerator(std::string seed_):noise(PerlinNoise(0))
  {
    seed = seed_;
    int s = SeedConverter(seed);
    noise = PerlinNoise(s, 5);
    img = Image();
  }

  Biome TerrainGenerator::JudgeBiome(double value) {
    double water_max_range = -0.23;
    double sand_max_range = 0.2;
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
      double x = (double)i*(double)noise.grid_count/(double)img.w;
      double y = (double)j*(double)noise.grid_count/(double)img.h;

      double noise_value = noise.Noise(x,y);

      // std::cout << noise_value << std::endl;

      img.SetPixel(i,j, Color((noise_value+1.2)*106.25) );

      switch(JudgeBiome(noise.Noise(x,y))){
        case Water:
          img.SetPixel(i,j, Color(0,128,150));
          break;
        case Sand:
          img.SetPixel(i,j,Color(240,221,195));
          break;
        case Grass:
          img.SetPixel(i,j,Color(0,128,0));
          break;
      }
    }

    img.ppm_out(seed + ".ppm");
  }
};