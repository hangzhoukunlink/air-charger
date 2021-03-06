#pragma once

#include <Arduino.h>

#include "conf.h"

#ifdef BLE_ENABLED
#include "./connecting/BLERemoteDevice.h"
#include "./pairing/BLEPairingServer.h"
#include "./scanning/BLEScanner.h"
#include <BLEDevice.h>
#endif

#include "../timing/DateTime.h"
#include "ble_address_t.h"

enum class BLEPeripheralState {
  INITIALIZING,
  IDLE,
  PAIRING,
  PAIRED,
  SCANNING,
  REMOTE_DEVICE_READY_TO_CONNECT,
  REMOTE_DEVICE_CONNECTING,
  REMOTE_DEVICE_CONNECTED,
  REMOTE_DEVICE_DISCONNECTED
};

class BLEPeripheralCallbacks {
public:
  virtual void onBLEStateChanged() = 0;
  virtual void onRemoteDeviceConnect() = 0;
  virtual void onRemoteDeviceDisconnect() = 0;
  virtual void onRemoteDeviceTime(DateTime time) = 0;
  virtual void onRemoteDeviceBatteryLevelChanged() = 0;
};

class BLEPeripheralClass : BLERemoteDeviceCallbacks, BLEPairingCallbacks {
public:
  void begin(String deviceName);

  BLEPeripheralState state();
  void state(BLEPeripheralState newState);
  BLERemoteDevice *remoteDevice();
  void setCallbacks(BLEPeripheralCallbacks *callbacks);

  void startPairingMode();
  void startScanningMode(ble_address_t addressLookingFor);
  void connectRemoteDevice(ble_address_t remoteAddress);
  void continueSearching();

  // Implements `BLEPairingCallbacks`.
  void onPaired();

  // Implements `BLERemoteDeviceCallbacks`.
  void onConnect();
  void onDisconnect();
  void onBatteryLevelChanged();
  void onTime(DateTime time);
private:
  String _deviceName;
  BLEPeripheralState _state = BLEPeripheralState::INITIALIZING;
  BLEPeripheralCallbacks *_callbacks;

#ifdef BLE_ENABLED
  BLEPairingServer *_pairingServer = nullptr;
  BLEScanner *_scanner = nullptr;
  BLERemoteDevice *_remoteDevice = nullptr;
#endif
};

extern BLEPeripheralClass BLEPeripheral;
