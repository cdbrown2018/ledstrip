#include "definitions.h"
#include <Arduino.h>
#include <display.h>
#include <utils.h>
#include <FastLED.h>

CRGB g_LEDs[NUM_LEDS] = {0};

WebKit32Display display;
int g_Brightness = 64;
int g_maxPower = 900;

#include "effects/marquee.h"
#include "effects/twinkle.h"
#include "effects/comet.h"
#include "effects/bounce.h"
#include "effects/fire.h"

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial)
  {
  }
  Serial.println("ESP32-S3 Startup");

  display.init();

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(g_LEDs, NUM_LEDS);
  FastLED.setBrightness(g_Brightness);
  set_max_power_indicator_LED(LED_BUILTIN);
  FastLED.setMaxPowerInMilliWatts(g_maxPower);
}

FireEffect fire(NUM_LEDS, 30, 100, 3, 2, false, true);

void loop()
{
  while (true)
  {
    EVERY_N_MILLISECONDS(20)
    {
      FastLED.clear();
      // fire.drawFire();
    }

    EVERY_N_MILLISECONDS(250)
    {
      display.g_OLED.clearBuffer();
      display.clear(false);
      display.g_OLED.printf("FPS  : %u", FastLED.getFPS());
      display.newLine();
      display.g_OLED.printf("Power: %u mW", calculate_unscaled_power_mW(g_LEDs, NUM_LEDS));
      display.newLine();
      display.g_OLED.printf("Brite: %d", calculate_max_brightness_for_power_mW(g_Brightness, g_maxPower));
      display.g_OLED.sendBuffer();
    }
    FastLED.setBrightness(g_Brightness);
    FastLED.delay(10);
  }
}