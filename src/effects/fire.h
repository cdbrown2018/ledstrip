#include <Arduino.h>
#include <FastLED.h>

#include "utils.h"

class FireEffect
{
protected:
    int size;        // How many total pixels the flame is
    int cooling;     // Rate at which the pixels cool off
    int sparks;      // How many sparks will be attempted each frame
    int sparkHeight; // If created, maz height for a spark
    int sparking;    // Probability of a spark each attempt
    bool bReversed;  // If reversed we draw from 0 outwards
    bool bMirrored;  // If mirrored we split and duplicate the drawing

    byte *heat;

    static const byte blendSelf = 2;
    static const byte blendNeighbor1 = 3;
    static const byte blendNeighbor2 = 2;
    static const byte blendNeighbor3 = 1;
    static const byte blendTotal = (blendSelf + blendNeighbor1 + blendNeighbor2 + blendNeighbor3);

public:
    FireEffect(int _size, int _cooling = 80, int _sparking = 50, int _sparks = 3, int _sparkHeight = 4, bool _bReversed = true, bool _bMirrored = false)
        : size(_size),
          cooling(_cooling),
          sparking(_sparking),
          sparks(_sparks),
          sparkHeight(_sparkHeight),
          bReversed(_bReversed),
          bMirrored(_bMirrored)
    {
        if (bMirrored)
        {
            size = size / 2;
        }

        heat = new byte[size]{0};
    }

    virtual ~FireEffect()
    {
        delete[] heat;
    }

    virtual void drawFire()
    {
        // Cool each cell
        for (int i = 0; i < size; i++)
        {
            heat[i] = max(0L, heat[i] - random(0, ((cooling * 10) / size) + 2));
        }

        // Drift heat up and diffuse
        for (int i = 0; i < size; i++)
        {
            heat[i] = (heat[i] * blendSelf +
                       heat[(i + 1) % size] * blendNeighbor1 +
                       heat[(i + 2) % size] * blendNeighbor2 +
                       heat[(i + 3) % size] * blendNeighbor3) /
                      blendTotal;
        }

        // Randomly ignite sparks
        for (int i = 0; i < sparks; i++)
        {
            if (random(255) < sparking)
            {
                int y = size - 1 - random(sparkHeight);
                heat[y] = heat[y] + random(160, 255);
            }
        }

        // Convert heat to color
        for (int i = 0; i < size; i++)
        {
            CRGB color = HeatColor(heat[i]);
            int j = bReversed ? (size - 1 - i) : i;
            drawPixels(j, 1, color);
            if (bMirrored)
            {
                drawPixels(!bReversed ? (2 * size - 1 - i) : size + i, 1, color);
            }
        }
    }
};