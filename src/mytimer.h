#include <pebble.h>

#pragma once
    
#define INTERVAL_TIME 100
    
//Time struct
typedef struct  {
    int milliseconds;
    int seconds;
    int minutes;
    int hours;
} MyTime;

static TextLayer* mytimer_text_layer;

//Call this BEFORE using the timer to set up the TextLayer to use for display
void mytimer_set_text_label(TextLayer*);

//All these methods may be called at will. It is not recommended that the timer_callback method is called
void mytimer_timer_callback(void* data);
void mytimer_set_timer_text(MyTime myTime);
void mytimer_start_timer();
void mytimer_stop_timer();
void mytimer_resume_timer();
int mytimer_get_mill_count();
bool mytimer_running();
void mytimer_set_time(int32_t time);
void mytimer_update_label();

MyTime counterToMyTime(int counter, int interval);


static AppTimer *mytimer_timer;
static int mytimer_count;
static bool mytimer_runTimer;

