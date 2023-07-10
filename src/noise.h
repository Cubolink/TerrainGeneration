//
// Created by major on 21-12-2021.
//

#ifndef TERRAINGEN_NOISE_H
#define TERRAINGEN_NOISE_H

#include <vector>
#include <iostream>
#include <cfloat>
#include "perlin_noise/PerlinNoise.hpp"

namespace NoiseGenerator  // It seems I can use namespaces as static classes, using functions instead of static methods, since I don't want to build objects
{
    /**
     * Fills a map with noise values using perlin noise.
     *
     * @param map where to fill
     * @param seed the random seed
     * @param scale scale of the map
     * @param octaves number of octaves of noise to add
     * @param persistance (greater than 1) amplitude factor each octave will have respect to the previous one
     * @param lacunarity  (between 0 and 1) frequency factor each octave will have respect to the previous one
     * @param x_offset  x offset to move the map (doesn't work well
     * @param y_offset  y offset to move the map (doesn't work well)
     * @param z_amplitude  normalize the noise map and then scales it to z_amplitude
     * @param resolution how many positions in the [0, 1] interval
     */
    static void generatePerlinNoiseMap(std::vector<std::vector<float>> &map, int seed, float scale, int octaves, float persistance, float lacunarity, float x_offset, float y_offset, float z_amplitude = 1, int resolution = 1)
    {
        int map_width = (int) map.size();
        int map_height = (int) map[0].size();

        srand(seed);
        auto octave_offsets = new float[octaves][2];
        for (int i = 0; i < octaves; i++)
        {
            octave_offsets[i][0] = (float) std::rand() + x_offset;
            octave_offsets[i][1] = (float) std::rand() + y_offset;
        }

        const siv::PerlinNoise::seed_type n_seed = seed;
        const siv::PerlinNoise perlinNoise{n_seed};

        if (scale <= 0)
            scale = 0.001f;

        float max_val = -FLT_MAX;
        float min_val = FLT_MAX;

        // Generate not-normalized map
        for (int i = 0; i < map_width; i++)
        {
            float x = (float) i / (float) resolution;
            for (int j = 0; j < map_height; j++)
            {
                float y = (float) j / (float) resolution;

                float amplitude = 1;
                float frequency = 1;
                float value = 0;

                // Generate octaves, increasing/decreasing not only amplitude, but frequency too
                for (int k = 0; k < octaves; k++)
                {
                    float tx = (x - (float) map_width/2.f) / scale * frequency + octave_offsets[k][0];
                    float ty = (y - (float) map_height/2.f) / scale * frequency + octave_offsets[k][1];

                    value += amplitude * (2 * (float) perlinNoise.noise2D_01(tx, ty) - 1);

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
                map[i][j] = z_amplitude * (map[i][j] - min_val) / (max_val - min_val);
        }

    }
}


#endif //TERRAINGEN_NOISE_H
