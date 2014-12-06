#include <pebble.h>
#include "mytimer.h"


void mytimer_set_text_label(TextLayer* text_layer) {
    mytimer_text_layer = text_layer;
}
    
void mytimer_start_timer() {
    mytimer_timer = app_timer_register(1000, (AppTimerCallback)mytimer_timer_callback, NULL);
    mytimer_runTimer = true;
    mytimer_count = 0;
}

void mytimer_stop_timer() {
    mytimer_runTimer = false;    
}

void mytimer_timer_callback(void* data) {
    //Delay next call for 1s
    mytimer_timer = app_timer_register(1000, (AppTimerCallback)mytimer_timer_callback, NULL);
    
    //Add time and display
    mytimer_count++;
    
    int seconds = mytimer_count % 60;
    int minutes  = (mytimer_count / 60) % 60;
    int hours = (mytimer_count / 3600);
    
    mytimer_set_timer_text(seconds, minutes, hours);
}

void mytimer_set_timer_text(int seconds, int minutes, int hours) {
    static char bufferSeconds[5];
    static char bufferMinutes[5];
    static char bufferHours[5];
    snprintf(bufferSeconds, 5, "%02d", seconds);
    snprintf(bufferMinutes, 5, "%02d", minutes);
    snprintf(bufferHours, 5, "%d", hours);
    
    static char buffer[] = "00000:00:00";
    snprintf(buffer, 11, "%s:%s:%s", bufferHours, bufferMinutes, bufferSeconds);
    
    text_layer_set_text(mytimer_text_layer, buffer);
}