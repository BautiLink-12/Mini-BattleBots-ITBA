#pragma once
#include <SoftwareSerial.h>
#include "Command.h"

class CommandSource {
public:
  virtual void begin() = 0;
  virtual Command read() = 0;
};

class BluetoothInput : public CommandSource {
public:
  BluetoothInput(uint8_t rxPin, uint8_t txPin, uint32_t baudRate)
    : serial(rxPin, txPin), baud(baudRate) {}

  void begin() override {
    serial.begin(baud);
  }

  Command read() override {
    if (!serial.available()) return Command::None;
    return decode(serial.read());
  }

private:
  SoftwareSerial serial;
  uint32_t baud;

  static Command decode(int c) {
    switch (c) {
      case 'F': return Command::Forward;
      case 'B': return Command::Backward;
      case 'L': return Command::Left;
      case 'R': return Command::Right;
      case 'S': return Command::Stop;
      case 'W': return Command::WeaponOn;
      case 'w': return Command::WeaponOff;
      case 'K': return Command::Arm;
      case 'D': return Command::Disarm;
      case 'X': return Command::Emergency;
      case 'C': return Command::ClearEmergency;
      case 'H': return Command::Heartbeat;
      default:  return Command::Unknown;
    }
  }
};
