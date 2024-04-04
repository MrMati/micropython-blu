#include "blu_ui.h"
#include "ui.h"


#define OU 7
#define INS 10
#define RW 1
#define PAD 3
#define TH 7

void SlotSelect::drawImpl(uint32_t millis) {
  tft.setTextColor(TFT_WHITE);

  for (int i = 0; i <= 2; i++) {
    tft.setCursor(10, OU + (RW + PAD) * (i + 1) + (TH + PAD + RW + INS) * i);
    tft.drawRoundRect(5, OU + (PAD + TH + PAD + 2 * RW + INS) * i, 15,
                      PAD + TH + PAD + 2 * RW, 1,
                      state.selectedSlot == i ? TFT_GREEN : TFT_DARKGREEN);
    tft.print((char)('0' + i + 1));
  }
}

void SensorStatus::drawImpl(uint32_t millis) {
  tft.fillScreen(TFT_BLACK);

  tft.setCursor(0, 0);
  tft.setTextColor(TFT_WHITE);
  tft.print("Sensor: ");
  if (!state.isSensorActive())
    tft.setTextColor(TFT_RED);
  tft.print(state.sensor.toString().c_str());
}

void FPSCounter::drawImpl(uint32_t millis) {
  if (millis - previousMillis >= 1000) // every second
  {
    fps = currentFrame /
          ((millis - previousMillis) / 1000.0); // - lastFramerate;
    currentFrame = 0;
    previousMillis = millis;
    seconds++;

    tft.fillScreen(TFT_BLACK);

    tft.setCursor(5*6, 0);
    tft.setTextColor(TFT_WHITE);
    //tft.print("FPS: ");
    tft.print(fps);
  }
  currentFrame++;


  scheduleRedraw();
}

void MeterBar::drawImpl(uint32_t millis) {
    tft.fillScreen(TFT_BLACK);
    tft.drawRect(0, 0, 20, 40, TFT_NAVY);
    tft.fillRect(1, 38 * (1 - state.value) + 1, 20 - 2, 38 * state.value, state.color);
}


void MainView::firstRender() {
  tft.fillScreen(TFT_BLACK);
  tft.resetViewport();
  tft.setCursor(0, 0, 1);
  tft.drawFastVLine(27, 0, 80, TFT_NAVY);
  tft.drawFastHLine(27, 14, 160 - 27, TFT_NAVY);
}

void MainView::render(uint32_t millis) {
  //slotSelect.state.selectedSlot = millis % 3000 / 1000;
  //if (millis > 2000)
  //  sensorStatus.state.sensor = SensorType::Hall;

  slotSelect.drawIfNeeded(millis);
  sensorStatus.drawIfNeeded(millis);
  sensorMeter.drawIfNeeded(millis);
  fpsCounter.drawIfNeeded(millis);
}

void SplashView::firstRender() {
    tft.fillScreen(TFT_BLACK);
    tft.setViewport(viewport.x, viewport.y, viewport.w, viewport.h);

    tft.setTextColor(tft.color565(43, 153, 255));
    tft.setCursor(0, 0, 2);
    tft.print("BLU");
}
