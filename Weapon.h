#pragma once
#include <Arduino.h>
#include <Servo.h>

class Weapon {
public:
  virtual void begin() = 0;
  virtual void engage() = 0;
  virtual void release() = 0;
  virtual void safe() = 0;
};

class SawWeapon : public Weapon {
public:
  SawWeapon(uint8_t motorPin, uint8_t motorPower)
    : pin(motorPin), power(motorPower) {}

  void begin() override {
    pinMode(pin, OUTPUT);
    safe();
  }

  void engage() override {
    analogWrite(pin, power);
  }

  void release() override {
    analogWrite(pin, 0);
  }

  void safe() override {
    analogWrite(pin, 0);
  }

private:
  uint8_t pin, power;
};

class ServoWeapon : public Weapon {
public:
  ServoWeapon(uint8_t servoPin, uint8_t restDeg, uint8_t strikeDeg)
    : pin(servoPin), rest(restDeg), strike(strikeDeg) {}

  void begin() override {
    servo.attach(pin);
    safe();
  }

  void engage() override {
    servo.write(strike);
  }

  void release() override {
    servo.write(rest);
  }

  void safe() override {
    servo.write(rest);
  }

private:
  Servo servo;
  uint8_t pin, rest, strike;
};
