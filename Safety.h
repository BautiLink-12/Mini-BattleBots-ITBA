#pragma once
#include <Arduino.h>

enum class SafetyState : uint8_t { Disarmed, Armed, Emergency };

class Safety {
public:
  explicit Safety(uint32_t timeoutMs) : timeout(timeoutMs) {}

  void begin() {
    state = SafetyState::Disarmed;
    lastSignal = millis();
  }

  void feed() {
    lastSignal = millis();
  }

  void update() {
    if (state == SafetyState::Armed && signalLost()) state = SafetyState::Disarmed;
  }

  bool signalLost() const {
    return millis() - lastSignal > timeout;
  }

  void arm() {
    if (state == SafetyState::Disarmed && !signalLost()) state = SafetyState::Armed;
  }

  void disarm() {
    if (state == SafetyState::Armed) state = SafetyState::Disarmed;
  }

  void emergency() {
    state = SafetyState::Emergency;
  }

  void clearEmergency() {
    if (state == SafetyState::Emergency) state = SafetyState::Disarmed;
  }

  bool isArmed() const {
    return state == SafetyState::Armed && !signalLost();
  }

  bool canDrive() const {
    return state != SafetyState::Emergency && !signalLost();
  }

  bool inEmergency() const {
    return state == SafetyState::Emergency;
  }

private:
  SafetyState state = SafetyState::Disarmed;
  uint32_t lastSignal = 0;
  uint32_t timeout;
};
