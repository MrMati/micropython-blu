#include "modcore1.h"
#include "TFT_eSPI.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "pico/util/queue.h"

#include "blu_ui.h"

TFT_eSPI tft = TFT_eSPI();

enum CMDSel {
  COLOR,
  SLOT,
  VIEW,
  SENSOR
};

queue_t cmd_fifo;
typedef struct cmd {
  CMDSel sel;
  uint32_t color;
  uint8_t slotSelect;
  uint8_t view; // 0 - SPLASH, 1 - MAIN
  SensorType::Value sensorStatus;
} cmd_t;
const int FIFO_LENGTH = 32;

MainView mainView(tft);
SplashView splashView(tft);

void core1_main() {
  unsigned long startMillis = to_ms_since_boot(get_absolute_time());
  tft.init();
  tft.setRotation(3);
  tft.setTextSize(1);

  tft.fillScreen(TFT_BLACK);

  View *currentView = &splashView;


  currentView->firstRender();

  while (1) {
    unsigned long currentMillis = to_ms_since_boot(get_absolute_time()) - startMillis;

    cmd_t cmd;
    if (queue_try_remove(&cmd_fifo, &cmd)) {
      switch(cmd.sel) {
        case VIEW:
          if(cmd.view == 0) currentView = &splashView;
          if(cmd.view == 1) currentView = &mainView;
          currentView->firstRender();
          break;
        case COLOR:
          mainView.sensorMeter.state.color = cmd.color;
          break;
        case SLOT:
          mainView.slotSelect.state.selectedSlot = cmd.slotSelect;
          break;
        case SENSOR:
          mainView.sensorStatus.state.sensor = cmd.sensorStatus;
          break;
      }
    }

    tft.startWrite();
    currentView->render(currentMillis);
    tft.endWrite();
  }
}

extern "C" {

static bool launched = false;

int launch_interface() {
  if (launched)
    return 1;

  queue_init(&cmd_fifo, sizeof(cmd_t), FIFO_LENGTH);
  // push display/UI settings into queue

  multicore_launch_core1(core1_main);
  launched = true;

  return 0;
}

int set_color_interface(uint32_t color) {
  if (!launched)
    return 2;
  cmd_t cmd = {.sel = COLOR, .color = color};
  return !queue_try_add(&cmd_fifo, &cmd);
}

int set_slot_interface(uint8_t slot) {
if (!launched)
    return 2;
  cmd_t cmd = {.sel = SLOT, .slotSelect = slot};
  return !queue_try_add(&cmd_fifo, &cmd);
}
int set_view_interface(uint8_t view) {
    if (!launched)
    return 2;
  cmd_t cmd = {.sel = VIEW, .view = view};
  return !queue_try_add(&cmd_fifo, &cmd);
}
int set_sensor_status_interface(uint8_t status) {
  if (!launched)
    return 2;
  cmd_t cmd = {.sel = SENSOR, .sensorStatus = SensorType::Value(status)};
  return !queue_try_add(&cmd_fifo, &cmd);
}

} // extern "C"
