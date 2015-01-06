#include <pebble.h>
    
#pragma once

void up_click_handler(ClickRecognizerRef recognizer, void *context);
void select_click_handler(ClickRecognizerRef recognizer, void *context);
void down_click_handler(ClickRecognizerRef recognizer, void *context);

void click_config_provider(void *context);

void activate_buttons();
void deactivate_buttons();
bool buttons_active();