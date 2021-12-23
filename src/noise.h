//
// Created by major on 21-12-2021.
//

#ifndef TERRAINGEN_NOISE_H
#define TERRAINGEN_NOISE_H

#include <vector>
#include <iostream>
#include "perlin_noise/PerlinNoise.hpp"

namespace NoiseGenerator  // It seems I can use namespaces as static classes, using functions instead of static methods, since I don't want to build objects
{
    static void generatePerlinNoiseMap(std::vector<std::vector<float>> &map, int seed, float scale, int octaves, float persistance, float lacunarity, float x_offset, float y_offset)
    {
        int map_width = (int) map.size();
        int map_height = (int) map[0].size();

        srand(seed);
        float octave_offsets[octaves][2];
        for (int i = 0; i < octaves; i++)
        {
            octave_offsets[i][0] = (float) std::rand() + x_offset;
            octave_offsets[i][1] = (float) std::rand() + y_offset;
        }

        const siv::PerlinNoise::seed_type n_seed = seed;
        const siv::PerlinNoise perlinNoise{n_seed};

        if (scale <= 0)
            scale = 0.001f;

        float max_val, min_val;

        // Generate not-normalized map
        for (int i = 0; i < map_width; i++)
        {
            for (int j = 0; j < map_height; j++)
            {
                float amplitude = 1;
                float frequency = 1;
                float value = 0;

                // Generate octaves, increasing/decreasing not only amplitude, but frequency too
                for (int k = 0; k < octaves; k++)
                {
                    float x = ((float) i - (float) map_width/2.f) / scale * frequency + octave_offsets[k][0];
                    float y = ((float) j - (float) map_height/2.f) / scale * frequency + octave_offsets[k][1];

                    value += amplitude * (2 * (float) perlinNoise.noise2D_01(x, y) - 1);

                    amplitude *= persistance;
                    frequency *= lacunarity;
                }

                if (value > max_val)
                    max_val = value;
                if (value < min_val)
                    min_val = value;

                map[i][j] = value;
            }
        }

        // normalize
        for (int i = 0; i < map_width; i++)
        {
            for (int j = 0; j < map_height; j++)
                map[i][j] = (map[i][j] - min_val) / (max_val - min_val);
        }

    }
}


#endif //TERRAINGEN_NOISE_H
