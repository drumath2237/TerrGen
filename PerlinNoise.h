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
    Vector2 GetGradVec(int gridx, int gridy);
    Vector2 GetGradVec(Vector2);
  };

  PerlinNoise::PerlinNoise(int seed_, int count) {
    grid_count = count;
    seed = seed_;
    
    std::mt19937 engine(seed);
    std::uniform_real_distribution<> dist(0.0, 2*PI);

    // e.g. 5 grids
    // 0-----1-----2-----3-----4-----5
    // |     |     |     |     |     |
    // |     |     |     |     |     |
    // 6-----7-----8-----9-----10----11
    // |     |     |     |     |     |

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

  // returns noise in [-1.0, 1.0]
  double PerlinNoise::Noise(double x, double y) {
    // 1------2
    // |      |
    // |      |
    // 3------4

    Vector2 grid1 = Vector2(floor(x), floor(y));
    Vector2 grid2 = grid1 + Vector2(1., 0);
    Vector2 grid3 = grid1 + Vector2(0, 1.);
    Vector2 grid4 = grid1 + Vector2(1., 1.);

    Vector2 grid1_grad = GetGradVec(grid1);
    Vector2 grid2_grad = GetGradVec(grid2);
    Vector2 grid3_grad = GetGradVec(grid3);
    Vector2 grid4_grad = GetGradVec(grid4);

    double tx = x-grid1.x;
    double ty = y-grid1.y;

    double u = tx * tx * tx * (tx * (tx * 6 - 15) + 10);
    double v = ty * ty * ty * (ty * (ty * 6 - 15) + 10);

    Vector2 target = Vector2(u,v) + grid1;

    Vector2 grid1_dist = normalized(target - grid1);
    Vector2 grid2_dist = normalized(target - grid2);
    Vector2 grid3_dist = normalized(target - grid3);
    Vector2 grid4_dist = normalized(target - grid4);

    double grid1_dot = dot(grid1_grad, grid1_dist);
    double grid2_dot = dot(grid2_grad, grid2_dist);
    double grid3_dot = dot(grid3_grad, grid3_dist);
    double grid4_dot = dot(grid4_grad, grid4_dist);

    double res = v*( u*grid1_dot + (1.0-u)*grid2_dot )
                 + (1.0-v)*( u*grid3_dot + (1.0-u)*grid4_dot );

    return res;
  }

  Vector2 PerlinNoise::GetGradVec(int gridx, int gridy) {
    int x = gridx % (grid_count+1);
    int y = gridy % (grid_count+1);

    return grad_vecs[x+y*(grid_count+1)];
  }

  Vector2 PerlinNoise::GetGradVec(Vector2 v) {
    return GetGradVec(v.x, v.y);
  }
};