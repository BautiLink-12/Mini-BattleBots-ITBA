#include "Config.h"
#include "Command.h"
#include "Input.h"
#include "Drive.h"
#include "Weapon.h"
#include "Safety.h"
#include "Robot.h"

BluetoothInput input(Config::BT_RX_PIN, Config::BT_TX_PIN, Config::BT_BAUD);

DifferentialDrive drive(
  Motor(Config::LEFT_PWM, Config::LEFT_IN1, Config::LEFT_IN2),
  Motor(Config::RIGHT_PWM, Config::RIGHT_IN1, Config::RIGHT_IN2)
);

SawWeapon weapon(Config::WEAPON_PIN, Config::WEAPON_POWER);

Safety safety(Config::SIGNAL_TIMEOUT_MS);

Robot robot(input, drive, weapon, safety);

void setup() {
  robot.begin();
}

void loop() {
  robot.update();
}
