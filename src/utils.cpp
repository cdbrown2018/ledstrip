#include <utils.h>

double FramesPerSecond(double seconds)
{
    static double framesPerSecond;
    framesPerSecond = (framesPerSecond * .9) + (1.0 / seconds * .1);
    return framesPerSecond;
}

CRGB colorFraction(CRGB colorIn, float fraction) {
    fraction = min(1.0f, fraction);
    return CRGB(colorIn).fadeToBlackBy(255 * (1.0f - fraction));
}

void drawPixels(float fPos, float count, CRGB color) {
    // // fpos - (long)fpos removes everything to the left of the decimal.
    // float availFirstPixel = 1.0f - (fPos - (long)(fPos));
    // float amtFirstPixel = min(availFirstPixel, count);
    // float remaining = min(count, FastLED.size() - fPos);
    // int iPos = fPos;

    // // Draw first pixel
    // if (remaining > 0.0f) {
    //     FastLED.leds()[iPos++] += colorFraction(color, amtFirstPixel);
    //     remaining -= amtFirstPixel;
    // }

    // // Draw all remaining full pixels
    // while (remaining > 1.0f) {
    //     FastLED.leds()[iPos++] += color;
    //     remaining--;
    // }

    // // Draw trailing pixel
    // if (remaining > 0.0f) {
    //     FastLED.leds()[iPos] += colorFraction(color, remaining);
    // }

    // Calculate how much the first pixel will hold
    float availFirstPixel = 1.0f - (fPos - (long)(fPos));
    float amtFirstPixel = min(availFirstPixel, count);
    float remaining = min(count, FastLED.size() - fPos);
    int iPos = fPos;

    // Blend (add) in the color of the first partial pixel

    if (remaining > 0.0f)
    {
        FastLED.leds()[iPos++] += colorFraction(color, amtFirstPixel);
        remaining -= amtFirstPixel;
    }

    // Now draw any full pixels in the middle

    while (remaining > 1.0f)
    {
        FastLED.leds()[iPos++] += color;
        remaining--;
    }

    // Draw tail pixel, up to a single full pixel

    if (remaining > 0.0f)
    {
        FastLED.leds()[iPos] += colorFraction(color, remaining);
    }
}