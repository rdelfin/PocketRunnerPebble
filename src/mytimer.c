#include "mytimer.h"


void mytimer_set_text_label(TextLayer* text_layer) {
    mytimer_text_layer = text_layer;
    
    //initial setup
    mytimer_runTimer = false;
}
    
void mytimer_start_timer() {
    mytimer_resume_timer();
    mytimer_set_time(0);
}

void mytimer_stop_timer() {
    mytimer_runTimer = false;    
}

void mytimer_resume_timer() {
    mytimer_timer = app_timer_register(INTERVAL_TIME, (AppTimerCallback)mytimer_timer_callback, NULL);
    mytimer_runTimer = true;
}

void mytimer_timer_callback(void* data) {
    if(mytimer_runTimer) {
        //Delay next call for INTERVAL_TIME milliseconds
        mytimer_timer = app_timer_register(INTERVAL_TIME, (AppTimerCallback)mytimer_timer_callback, NULL);
        
        //Add time and display
        mytimer_count++;
        
        //Only update every second
        if(mytimer_count % (1000 / INTERVAL_TIME) == 0) {
            mytimer_set_timer_text(counterToMyTime(mytimer_count, INTERVAL_TIME));
        }
    }
}

void mytimer_set_timer_text(MyTime myTime) {
    static char bufferSeconds[5];
    static char bufferMinutes[5];
    static char bufferHours[5];
    snprintf(bufferSeconds, 5, "%02d", myTime.seconds);
    snprintf(bufferMinutes, 5, "%02d", myTime.minutes);
    snprintf(bufferHours, 5, "%d", myTime.hours);
    
    static char buffer[] = "00000:00:00";
    snprintf(buffer, sizeof(buffer) / sizeof(char), "%s:%s:%s", bufferHours, bufferMinutes, bufferSeconds);
    
    text_layer_set_text(mytimer_text_layer, buffer);
}

MyTime counterToMyTime(int counter, int interval) {
    MyTime result;
    
    result.milliseconds = (counter * interval) % 1000;
    result.seconds = (counter * interval / 1000) % 60;
    result.minutes = (counter * interval / 60000) % 60;
    result.hours = (counter * interval / 3600000);
    
    return result;
}

int mytimer_get_mill_count()
{
    return mytimer_count;
}

bool mytimer_running() { return mytimer_runTimer; }

void mytimer_set_time(int32_t time) { mytimer_count = time; }
