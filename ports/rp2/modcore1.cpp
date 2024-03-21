#include "modcore1.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "TFT_eSPI.h"

TFT_eSPI tft = TFT_eSPI();


void core1_main() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);

    long previousMillis = 0;
    long lastFramerate = 0;
    long currentFramerate = 0;
    uint16_t seconds = 0;
    uint16_t fps = 0;
    uint8_t shapeColor = 0;
    uint8_t dir = 1;
    tft.setTextSize(1);
    
    
    while (1) {
        unsigned long currentMillis = to_ms_since_boot(get_absolute_time());

        if (currentMillis - previousMillis >= 1000) // every second
        {
          fps = currentFramerate - lastFramerate;
          lastFramerate = currentFramerate;
          previousMillis = currentMillis;
          seconds++;
        }
        if ((currentMillis - previousMillis) % 200 >= 100) {
          shapeColor += dir;
          if (shapeColor % 0xff == 0)
            dir = -dir;
        }
        currentFramerate++;

        tft.setCursor(5, 2, 1);
        tft.print("Secs :");
        tft.setCursor(50, 2);
        tft.print(seconds);

        tft.setCursor(5, 12, 1);
        tft.print("FPS  :");
        tft.setCursor(50, 12);
        tft.print(fps);

        // print some graphics
        // tft.drawCircle(0, 0, 10, shapeColor);
        // tft.drawRect(0, 0, 160, 80, shapeColor);
        tft.fillRectHGradient(3, 22, 150, 55,
                              rgb565(0xff - shapeColor, shapeColor, 0),
                              rgb565(shapeColor, 0xff - shapeColor, 0));
        // tft.drawPixel(0, 0, TFT_RED);
        // tft.fillScreen(TFT_BLACK);
    }
}




extern "C" {

static bool launched = false;

int launch_interface() {
    if(launched) return 1;
    multicore_launch_core1(core1_main);
    launched = true;
    return 0;
    
}


} // extern "C"
