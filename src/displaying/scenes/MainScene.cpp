#include "MainScene.h"

#include "log.h"

#include "../../ble/BLEPeripheral.h"
#include "../../utils/format.h"

MainScene::MainScene() : _clockFrame(13, TFT_HEIGHT - 54 - 12, TFT_WIDTH - 13 * 2, 54) {

}

bool MainScene::update(bool forceRedraw) {
  bool redraw = false;
  if (forceRedraw) {
    redraw = true;
  } else if (millis() - _lastRedraw > 1000) {
    redraw = true;
  }
  return redraw;
}

void MainScene::redraw(TFT_eSPI *canvas) {
  _drawClock(canvas);
  _lastRedraw = millis();
}

void MainScene::_drawClock(TFT_eSPI *canvas) {
  DateTime now(DateTime::now());
  String timeString = formatTime(now);
  if (_clock == nullptr) {
    _clock = new TFT_eSprite(canvas);
    _clock->setColorDepth(8);
  }
  _clock->createSprite(_clockFrame.width, _clockFrame.height);
  _clock->fillSprite(TFT_RED);
  _clock->setTextColor(TFT_WHITE);
  _clock->setTextFont(7);
  _clock->setTextSize(1);
  _clock->setTextDatum(CC_DATUM);
  _clock->drawString(timeString, _clock->width() / 2, _clock->height() / 2);
  _clock->pushSprite(_clockFrame.left, _clockFrame.top);
  _clock->deleteSprite();
}