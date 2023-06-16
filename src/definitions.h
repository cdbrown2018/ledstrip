#define NUM_LEDS 144
#define LED_PIN 5
#define FASTLED_INTERNAL

#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#define TIMES_PER_SECOND(x) EVERY_N_MILLISECONDS(1000/x)