#pragma once
#include <Arduino.h>

enum class Command : uint8_t {
  None,
  Unknown,
  Forward,
  Backward,
  Left,
  Right,
  Stop,
  WeaponOn,
  WeaponOff,
  Arm,
  Disarm,
  Emergency,
  ClearEmergency,
  Heartbeat
};
