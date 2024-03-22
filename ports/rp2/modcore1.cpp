#include "modcore1.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"
#include "TFT_eSPI.h"

TFT_eSPI tft = TFT_eSPI();

queue_t cmd_fifo;
typedef struct cmd {
    int color;
} cmd_t;
const int FIFO_LENGTH = 32;


void core1_main() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);

    long previousMillis = 0;
    long currentFramerate = 0;
    uint16_t seconds = 0;
    uint16_t fps = 0;
    int shapeColor = 0xff;
    int lastShapeColor = !shapeColor;
    uint8_t dir = 1;
    tft.setTextSize(1);
    
    
    while (1) {
        unsigned long currentMillis = to_ms_since_boot(get_absolute_time());

        if (currentMillis - previousMillis >= 1000) // every second
        {
          fps = currentFramerate;// - lastFramerate;
          currentFramerate = 0;
          previousMillis = currentMillis;
          seconds++;
        }
        if ((currentMillis - previousMillis) % 200 >= 100) {
          //shapeColor += dir;
          //shapeColor %= 0x100;
          if (shapeColor == 0)
            dir = -dir;
        }
        currentFramerate++;
        
        cmd_t cmd;
        if(queue_try_remove(&cmd_fifo, &cmd)) {
            shapeColor = cmd.color % 0x100;
        }

        tft.setCursor(5, 2, 1);
        tft.print("Secs :");
        tft.setCursor(50, 2);
        tft.print(seconds);

        tft.setCursor(5, 12, 1);
        tft.print("FPS  :");
        tft.setCursor(50, 12);
        tft.print(fps);

        if(lastShapeColor != shapeColor) {
          lastShapeColor = shapeColor;
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
}




extern "C" {

static bool launched = false;

int launch_interface() {
    if(launched) return 1;
    
    queue_init(&cmd_fifo, sizeof(cmd_t), FIFO_LENGTH);
    // push display/UI settings into queue
    
    multicore_launch_core1(core1_main);
    launched = true;
    
    return 0; 
}

int set_color_interface(int color) {
    if(!launched) return 2;
    cmd_t cmd = {
     .color = color
    };
    return !queue_try_add(&cmd_fifo, &cmd);
}


} // extern "C"
