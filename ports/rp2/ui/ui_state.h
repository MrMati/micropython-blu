#pragma once

#include <cstdint>
#include <string>

using namespace std;

struct SliderState {
  uint32_t color;
  int32_t value;
  string name;
};

struct SlotSelectState {
  uint8_t selectedSlot = 0;
};

class SensorType {
public:
  enum Value : int8_t {
    Unknown = -1,
    Disconnected,
    LightIntensity,
    Hall,
    Temperature,
  };

  SensorType() = default;

  constexpr SensorType(Value aFruit) : value(aFruit) {}

  // Allow switch and comparisons.
  // constexpr operator Value() const { return value; }

  constexpr bool operator==(SensorType a) const { return value == a.value; }

  constexpr bool operator!=(SensorType a) const { return value != a.value; }

  // Prevent usage: if(fruit)
  explicit operator bool() const = delete;

  constexpr string toString() const {
    switch (value) {
    case Unknown:
      return "Unknown";
    case Disconnected:
      return "Disconnected";
    case Hall:
      return "Magnetism";
    case LightIntensity:
      return "Light";
    case Temperature:
      return "Temperature";
    default:
      return "";
    }
  }

private:
  Value value;
};

struct SensorStatusState {
  SensorType sensor;

  bool isSensorActive() const {
    return sensor != SensorType::Unknown && sensor != SensorType::Disconnected;
  }
};

struct FPSCounterState {};

struct MeterBarState {
    float value;
    uint32_t color;
};