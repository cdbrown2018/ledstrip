#include <FastLED.h>
#define NUM_COLORS 5

static const CRGB TwinkleColors[NUM_COLORS] = {
    CRGB::Red,
    CRGB:: Blue,
    CRGB::Purple,
    CRGB::Green,
    CRGB::Orange
};

void drawTwinkle(bool colorful) {
    static int passCount = 0;
    passCount++;

    if (passCount == NUM_LEDS / 4) {
        passCount = 0;
        FastLED.clear(false);
    }

    CRGB color = colorful ? TwinkleColors[random(NUM_COLORS)] : /* CRGB(206, 179, 30) */ CRGB(195, 155, 118);
    g_LEDs[random(NUM_LEDS)] = color;
    delay(200);
}