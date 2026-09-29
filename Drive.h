#pragma once
#include <Arduino.h>

class Motor {
public:
  Motor(uint8_t pwmPin, uint8_t in1Pin, uint8_t in2Pin)
    : pwm(pwmPin), in1(in1Pin), in2(in2Pin) {}

  void begin() {
    pinMode(pwm, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    stop();
  }

  void set(int16_t speed) {
    speed = constrain(speed, -255, 255);
    digitalWrite(in1, speed > 0 ? HIGH : LOW);
    digitalWrite(in2, speed < 0 ? HIGH : LOW);
    analogWrite(pwm, abs(speed));
  }

  void stop() {
    set(0);
  }

private:
  uint8_t pwm, in1, in2;
};

class Drive {
public:
  virtual void begin() = 0;
  virtual void move(int16_t throttle, int16_t turn) = 0;
  virtual void stop() = 0;
};

class DifferentialDrive : public Drive {
public:
  DifferentialDrive(Motor leftSide, Motor rightSide)
    : left(leftSide), right(rightSide) {}

  void begin() override {
    left.begin();
    right.begin();
  }

  void move(int16_t throttle, int16_t turn) override {
    left.set(throttle + turn);
    right.set(throttle - turn);
  }

  void stop() override {
    left.stop();
    right.stop();
  }

private:
  Motor left;
  Motor right;
};
