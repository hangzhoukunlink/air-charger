#pragma once

#include <Arduino.h>

#include "ble/BLEPeripheral.h"
#include "charging/Charger.h"
#include "displaying/Screen.h"
#include "settings/Settings.h"

#include "scenes/ConnectScene.h"
#include "scenes/MainScene.h"

class AirChargerClass : BLEPeripheralCallbacks {
public:
  // Initializes the `AirCharger` with given device name.
  void begin(String deviceName);

  // Event loop.
  uint16_t update();

  Scene *currentScene();
  void currentScene(Scene *scene);

  // Implements `BLEPeripheralCallbacks`.
  void onBLEStateChanged();
  void onRemoteDeviceConnect();
  void onRemoteDeviceDisconnect();
  void onRemoteDeviceBatteryLevelChanged();
  void onRemoteDeviceTime(DateTime time);

private:
  unsigned long _lastUpdate = 0;
  Scene *_currentScene = nullptr;
  ConnectScene *_connectScene = nullptr;
  MainScene *_mainScene = nullptr;

  void _updateScene(bool forceRedraw = false);
  void _updateConnection();
};

extern AirChargerClass AirCharger;
