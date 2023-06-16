#include <U8g2lib.h>

#define OLED_CLOCK 18
#define OLED_DATA 17
#define OLED_RESET 21

class WebKit32Display
{
private:
    int g_lineHeight;
    int g_currentLine;

public:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED;
    WebKit32Display() : g_OLED(U8G2_R0, OLED_RESET, OLED_CLOCK, OLED_DATA){};

    /**
     * Initializes the display.
     */
    void init();
    /**
     * Creates a new line.
     */
    void newLine();
    /**
     * Sets the cursoe to the beginning of the current line.
     */
    void home();
    /**
     * Clears and resets the display.
     */
    void clear(bool resetPixels);
};