#include <sys/time.h>

#include <Arduino.h>
#include <FastLED.h>
#include "utils.h"

using namespace std;
#include <vector>

extern CRGB g_LEDs[];

#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))

static const CRGB ballColors[] = {
    CRGB::Green,
    CRGB::Red,
    CRGB::Blue,
    CRGB::Orange,
    CRGB::Indigo};

class BouncingBallEffect
{
private:
    double initialBallSpeed(double height) const
    {
        return sqrt(-2 * gravity * height);
    }
    size_t _cLength;
    size_t _cBalls;
    byte _fadeRate;
    bool _bMirrored;

    const double gravity = -9.81;
    const double startHeight = 1;
    const double impactVelocity = initialBallSpeed(startHeight);
    const double speedKnob = 4.0;

    vector<double> clockTimeAtLastBounce, height, ballSpeed, dampening;
    vector<CRGB> colors;

    static double Time()
    {
        timeval tv = {0};
        gettimeofday(&tv, nullptr);
        return (double)(tv.tv_usec / 1000000.0 + (double)tv.tv_sec);
    }

public:
    BouncingBallEffect(size_t cLength, size_t ballCount = 3, byte fade = 0, bool bMirrored = false)
        : _cLength(cLength - 1),
          _cBalls(ballCount),
          _fadeRate(fade),
          _bMirrored(bMirrored),
          clockTimeAtLastBounce(ballCount),
          height(ballCount),
          ballSpeed(ballCount),
          dampening(ballCount),
          colors(ballCount)
    {
        for (size_t i = 0; i < ballCount; i++)
        {
            height[i] = startHeight;                           // Current ball height
            clockTimeAtLastBounce[i] = Time();                 // When ball last hit ground
            dampening[i] = 0.90 - i / pow(_cBalls, 2);         // Bounciness of ball
            ballSpeed[i] = initialBallSpeed(height[i]);        // Don't dampen initial ball
            colors[i] = ballColors[i % ARRAYSIZE(ballColors)]; // Color of this ball
        }
    }

    virtual void draw()
    {
        if (_fadeRate != 0)
        {
            for (size_t i = 0; i < _cLength; i++)
            {
                g_LEDs[i].fadeToBlackBy(_fadeRate);
            }
        }
        else
        {
            FastLED.clear();
        }

        for (size_t i = 0; i < _cBalls; i++)
        {
            double timeSinceLastBounce = (Time() - clockTimeAtLastBounce[i]) / speedKnob;

            // Constant Acceleration function
            height[i] = 0.5 * gravity * pow(timeSinceLastBounce, 2.0) + ballSpeed[i] * timeSinceLastBounce;

            if (height[i] < 0)
            {
                height[i] = 0;
                ballSpeed[i] = dampening[i] * ballSpeed[i];
                clockTimeAtLastBounce[i] = Time();

                if (ballSpeed[i] < 0.01)
                {
                    ballSpeed[i] = initialBallSpeed(startHeight) * dampening[i];
                }
            }

            size_t position = (size_t)(height[i] * (_cLength - 1) / startHeight);

            drawPixels(position, 2, FastLED.leds()[position] += colors[i]);

            if (_bMirrored)
            {
                int mirroredPosition = _cLength - position + 1;
                drawPixels(mirroredPosition, 2, colors[i]);
            }
        }
        delay(20);
    }
};