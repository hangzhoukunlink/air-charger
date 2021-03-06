#pragma once

#include <Arduino.h>

#include "../ble/ble_address_t.h"

enum class AirChargerRebootReason { UNKNOWN = 1, REPAIR = 10, PAIRED = 11, REMOTE_DEVICE_DISCONNECT = 20 };

class AirChargerSettingsClass {
public:
  // Initializes `AirChargerSettingsClass`.
  void begin();

  AirChargerRebootReason rebootReason();
  void rebootReason(AirChargerRebootReason reason);

  bool hasClientAddress();
  ble_address_t clientAddress();
  void clientAddress(ble_address_t value);

  void save();
  void erase();

private:
  AirChargerRebootReason _rebootReason = AirChargerRebootReason::UNKNOWN;
  bool _hasClientAddress = false;
  uint8_t _clientAddress[6];

  void _touch();
};

extern AirChargerSettingsClass AirChargerSettings;
