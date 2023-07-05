#include "waveshare_epaper.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace waveshare_epaper {

static const char *const TAG = "waveshare_epaper";

void GDEW029Z13::initialize() {
	ESP_LOGI(TAG, "GDEW029Z13::initialize");
	this->reset_();
	// Panel Setting (PSR)
	this->command(0x00);
	this->data(0x8f);

	// VCOM And Data Interval Setting (CDI)
	this->command(0x50);
	this->data(0x77);

	// Power ON (PON)
	this->command(0x04);
	this->wait_until_idle_();
	ESP_LOGI(TAG, "GDEW029Z13::initialize done");
}

void HOT GDEW029Z13::display() {
 ESP_LOGI(TAG, "GDEW029Z13::display");
  // COMMAND DATA START TRANSMISSION 1 (B/W data)
  this->command(0x10);
  this->start_data_();
  this->write_array(this->buffer_, this->get_buffer_length_());
  this->end_data_();

  // COMMAND DATA START TRANSMISSION 2 (RED data)
  this->command(0x13);
  this->start_data_();
  for (size_t i = 0; i < this->get_buffer_length_(); i++)
    this->write_byte(0xFF);
  this->end_data_();
  delay(2);

  // COMMAND DISPLAY REFRESH
  this->command(0x12);
  this->wait_until_idle_();

  // COMMAND POWER OFF
  // NOTE: power off < deep sleep
  this->command(0x02);
 ESP_LOGI(TAG, "GDEW029Z13::display done");
}

void GDEW029Z13::dump_config() {
  LOG_DISPLAY("", "Waveshare E-Paper (Good Display)", this);
  ESP_LOGCONFIG(TAG, "  Model: 2.9in B/W/R GDEW029Z13");
  LOG_PIN("  Reset Pin: ", this->reset_pin_);
  LOG_PIN("  DC Pin: ", this->dc_pin_);
  LOG_PIN("  Busy Pin: ", this->busy_pin_);
  LOG_UPDATE_INTERVAL(this);
}

void GDEW029Z13::set_full_update_every(uint32_t full_update_every) {
  this->full_update_every_ = full_update_every;
}

}  // namespace waveshare_epaper
}  // namespace esphome
