#pragma once
#include "Config.h"
#include "Command.h"
#include "Input.h"
#include "Drive.h"
#include "Weapon.h"
#include "Safety.h"

class Robot {
public:
  Robot(CommandSource& inputSource, Drive& driveSystem, Weapon& weaponSystem, Safety& safetySystem)
    : input(inputSource), drive(driveSystem), weapon(weaponSystem), safety(safetySystem) {}

  void begin() {
    pinMode(Config::EMERGENCY_PIN, INPUT_PULLUP);
    input.begin();
    drive.begin();
    weapon.begin();
    safety.begin();
    shutdownOutputs();
  }

  void update() {
    Command c;
    while ((c = input.read()) != Command::None) handle(c);

    if (digitalRead(Config::EMERGENCY_PIN) == LOW) emergencyStop();

    safety.update();
    enforce();
  }

  void emergencyStop() {
    safety.emergency();
    throttle = 0;
    turn = 0;
    weaponWanted = false;
    shutdownOutputs();
  }

private:
  CommandSource& input;
  Drive& drive;
  Weapon& weapon;
  Safety& safety;

  int16_t throttle = 0;
  int16_t turn = 0;
  bool weaponWanted = false;

  void handle(Command c) {
    if (c == Command::Unknown) return;
    safety.feed();

    switch (c) {
      case Command::Forward:
        throttle = Config::DRIVE_SPEED;
        turn = 0;
        break;
      case Command::Backward:
        throttle = -Config::DRIVE_SPEED;
        turn = 0;
        break;
      case Command::Left:
        throttle = 0;
        turn = -Config::TURN_SPEED;
        break;
      case Command::Right:
        throttle = 0;
        turn = Config::TURN_SPEED;
        break;
      case Command::Stop:
        throttle = 0;
        turn = 0;
        break;
      case Command::WeaponOn:
        weaponWanted = safety.isArmed();
        break;
      case Command::WeaponOff:
        weaponWanted = false;
        break;
      case Command::Arm:
        safety.arm();
        break;
      case Command::Disarm:
        weaponWanted = false;
        safety.disarm();
        break;
      case Command::Emergency:
        emergencyStop();
        break;
      case Command::ClearEmergency:
        safety.clearEmergency();
        break;
      default:
        break;
    }
  }

  void enforce() {
    if (safety.canDrive()) {
      drive.move(throttle, turn);
    } else {
      throttle = 0;
      turn = 0;
      drive.stop();
    }

    if (safety.isArmed() && weaponWanted) {
      weapon.engage();
    } else {
      weaponWanted = false;
      weapon.release();
    }
  }

  void shutdownOutputs() {
    drive.stop();
    weapon.safe();
  }
};
