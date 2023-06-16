#include "definitions.h"
#include <Arduino.h>
#include <FastLED.h>
#include "utils.h"

void drawMarquee()
{
    fill_solid(g_LEDs, NUM_LEDS, CRGB(199, 143, 38));

    static int scroll = 0;
    scroll++;

    for (int i = scroll % 5; i < NUM_LEDS - 1; i += 5) {
        g_LEDs[i] = CRGB::Black;
    }

    delay(50);
}

void drawSmoothMarquee() {
    static float scroll = 0.0f;
    scroll += 0.1f;
    if (scroll > 5.0) {
        scroll -= 5.0;
    }

    for (float i = scroll; i < NUM_LEDS; i+= 5) {
        drawPixels(i, 3, CRGB(199, 143, 38));
    }
}