#pragma once

#include <vector>
#include <random>
#include <iostream>
#include <cmath>

#include "Vector2.h"

#define PI 3.14159265358

namespace TerrGen {
  struct PerlinNoise {
    int grid_count;
    int seed;
    std::vector<Vector2> grad_vecs;

    PerlinNoise(int seed);
    PerlinNoise(int seed, int count);

    double Noise(double x, double y);
  };

  PerlinNoise::PerlinNoise(int seed_, int count) {
    grid_count = count;
    seed = seed_;
    
    std::mt19937 engine(seed);
    std::uniform_real_distribution<> dist(0.0, 2*PI);

    for(int y=0; y<grid_count+1; y++) for(int x=0; x<grid_count+1; x++) {
      grad_vecs.push_back(
        Vector2(
          std::cos(dist(engine)),
          std::sin(dist(engine))
        )
      );
    }
  }

  PerlinNoise::PerlinNoise(int seed) {
    PerlinNoise(seed, 5);
  }
};