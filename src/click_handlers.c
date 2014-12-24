#include <pebble.h>
#include "click_handlers.h"
#include "mytimer.h"
#include "app_communication.h"

//Done button
void up_click_handler(ClickRecognizerRef recognizer, void *context)
{
    //Do nothing (for now...)
}

//Pause button
void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
    if(mytimer_running()) {
        mytimer_stop_timer();
    } else {
        mytimer_resume_timer();
    }
    
    int32_t time = mytimer_get_mill_count();
    
    send_pause(time);
    
    vibes_short_pulse();
}

//Lap button
void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
    int32_t time = mytimer_get_mill_count();
    
    add_lap();
    send_lap(time);
    
    vibes_short_pulse();
}

void click_config_provider(void *context)
{
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}