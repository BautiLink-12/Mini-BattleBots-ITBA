#pragma once
#include <Arduino.h>

namespace Config {
constexpr uint8_t BT_RX_PIN = 2;
constexpr uint8_t BT_TX_PIN = 4;
constexpr uint32_t BT_BAUD = 9600;

constexpr uint8_t LEFT_PWM = 5;
constexpr uint8_t LEFT_IN1 = 7;
constexpr uint8_t LEFT_IN2 = 8;

constexpr uint8_t RIGHT_PWM = 6;
constexpr uint8_t RIGHT_IN1 = 9;
constexpr uint8_t RIGHT_IN2 = 10;

constexpr uint8_t WEAPON_PIN = 11;
constexpr uint8_t EMERGENCY_PIN = 12;

constexpr int16_t DRIVE_SPEED = 200;
constexpr int16_t TURN_SPEED = 170;
constexpr uint8_t WEAPON_POWER = 255;

constexpr uint32_t SIGNAL_TIMEOUT_MS = 1000;
}
