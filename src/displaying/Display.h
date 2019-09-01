#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "../ble/BLEPeripheral.h"

#include "scenes/ConnectScene.h"
#include "scenes/MainScene.h"

class DisplayClass {
public:
  void begin();

  TFT_eSPI canvas();

  void update(bool forceRedraw = false);
  void showMessage(String message);

private:
  TFT_eSPI _tft;
  ConnectScene *_connectScene = nullptr;
  MainScene *_mainScene = nullptr;
};

extern DisplayClass Display;