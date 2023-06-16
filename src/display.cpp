#include <display.h>

void WebKit32Display::init()
{
    g_OLED.begin();
    g_OLED.clear();
    g_OLED.setFont(u8g2_font_profont15_tf);
    g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent();
    g_currentLine = 0;
    newLine();
}
void WebKit32Display::newLine()
{
    g_OLED.setCursor(0, g_lineHeight * ++g_currentLine);
};
void WebKit32Display::home()
{
    g_OLED.setCursor(0, g_lineHeight * g_currentLine);
}
void WebKit32Display::clear(bool resetPixels)
{
    if (resetPixels)
    {
        g_OLED.clear();
    }
    g_currentLine = 0;
    newLine();
    home();
}