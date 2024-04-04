#pragma once

#include <TFT_eSPI.h>
#include <cstdint>

#include "ui.h"
#include "ui_state.h"

class SlotSelect : public Widget<SlotSelectState> {
public:
  explicit SlotSelect(TFT_eSPI &tft, SlotSelectState initState)
      : Widget(tft, initState){};

private:
  void drawImpl(uint32_t millis) override;
};

class SensorStatus : public Widget<SensorStatusState> {
public:
  explicit SensorStatus(TFT_eSPI &tft, SensorStatusState initState)
      : Widget(tft, initState){};

private:
  void drawImpl(uint32_t millis) override;
};

class FPSCounter : public Widget<FPSCounterState> {
public:
  explicit FPSCounter(TFT_eSPI &tft, FPSCounterState initState)
      : Widget(tft, initState){};

private:
  void drawImpl(uint32_t millis) override;

  uint32_t previousMillis = 0;
  uint32_t currentFrame = 0;
  uint16_t seconds = 0;
  uint16_t fps = 0;
};

class MeterBar : public Widget<MeterBarState> {
public:
    explicit MeterBar(TFT_eSPI &tft, MeterBarState initState)
            : Widget(tft, initState) {};

private:
    void drawImpl(uint32_t millis) override;
};


class MainView : public View {
public:
  explicit MainView(TFT_eSPI &tft) : View(tft) {
    slotSelect.viewport = {.w = 27, .h = 80};
    sensorStatus.viewport = {29, 3, 160 - 29, 10};
    sensorMeter.viewport = {35, 35, 20, 40};
    fpsCounter.viewport = {160-54, 80-7, 54, 7}; // lower-right corner
  };

  SlotSelect slotSelect{tft, {}};
  SensorStatus sensorStatus{tft, {SensorType::Disconnected}};
  MeterBar sensorMeter{tft, {0.2f, TFT_BLUE}};
  FPSCounter fpsCounter{tft, {}};

  void firstRender() override;

  void render(uint32_t millis) override;
};

class SplashView : public View {
public:
  explicit SplashView(TFT_eSPI &tft) : View(tft) {}


  void firstRender() override;

  void render(uint32_t millis) override {}

private:
  Rect viewport = {69, 32, 160, 80};
};