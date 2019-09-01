#pragma once

#include <Arduino.h>
#include <time.h>

struct DateTime {
public:
  DateTime(time_t time);

  DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec);

  static void configTime(DateTime time);
  static time_t now();
  int getFullYear();
  int getMonth();
  int getDate();
  int getDay();
  int getHours();
  int getMinutes();
  int getSeconds();
  time_t gmtTime();

private:
  time_t _time;
  struct tm *_localTime;
};
