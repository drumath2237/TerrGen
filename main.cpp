#include <iostream>
#include <random>

#include "TerrainGenerator.h"

using namespace std;

int main(int argc, const char** argv) {
  string seed = "test";
  TerrGen::TerrainGenerator gen = TerrGen::TerrainGenerator(seed);
  gen.RenderTerrain();
  return 0;
}