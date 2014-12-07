#include <pebble.h>

#pragma once

static TextLayer* mytimer_text_layer;

//Call this BEFORE using the timer to set up the TextLayer to use for display
void mytimer_set_text_label(TextLayer*);

//All these methods may be called at will. It is not recommended that the timer_callback method is called
void mytimer_timer_callback(void* data);
void mytimer_set_timer_text(int seconds, int minutes, int hours);
void mytimer_start_timer();
void mytimer_stop_timer();


static AppTimer *mytimer_timer;
static int mytimer_count;
static bool mytimer_runTimer;