#include <pebble.h>
#include "click_handlers.h"
#include "mytimer.h"
#include "app_communication.h"
#include "main_window.h"
    
bool buttonsActive;

//Done button
void up_click_handler(ClickRecognizerRef recognizer, void *context)
{
    if(!mytimer_running() && buttonsActive) {
        show_no_connection_message(true, "Sending run to phone...");
        deactivate_buttons();
        send_run();
        
        vibes_short_pulse();
    }
}

//Pause button
void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
    if(buttonsActive) {
        if(mytimer_running()) {
            mytimer_stop_timer();
        } else {
            mytimer_resume_timer();
        }
        
        vibes_short_pulse();
    }
}

//Lap button
void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
    if(buttonsActive) {
        add_lap();
        
        vibes_short_pulse();
    }
}

void click_config_provider(void *context)
{
    // Register the ClickHandlers
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
    //By default, buttons have to be activated
    buttonsActive = false;
}

void activate_buttons() { buttonsActive = true; }
void deactivate_buttons() { buttonsActive = false; }
bool buttons_active() { return buttonsActive; }