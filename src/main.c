#include <pebble.h>
#include <time.h>
#include "mytimer.h"
    
static void init();
static void deinit();
static void main_window_load(Window *window);
static void main_window_unload(Window *window);

static Window *s_main_window;
static TextLayer *s_time_layer;

int main(void) {
  init();
  app_event_loop();
  deinit();
}


static void init() {
    // Create main Window element and assign to pointer
    s_main_window = window_create();

    // Set handlers to manage the elements inside the Window
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = main_window_load,
        .unload = main_window_unload
    });

    // Show the Window on the watch, with animated=true
    window_stack_push(s_main_window, true);
    
    //Reset count and register tick counter
    
    //Call timer every second
}

static void main_window_load(Window *window) {
    // Create time TextLayer
    s_time_layer = text_layer_create(GRect(0, 55, 144, 50));
    text_layer_set_background_color(s_time_layer, GColorClear);
    text_layer_set_text_color(s_time_layer, GColorBlack);
    
    //Initialize timer with the newly created layer
    mytimer_set_text_label(s_time_layer);
    mytimer_start_timer();
    
    //Display time zero
    mytimer_set_timer_text(0, 0, 0);

    // Improve the layout to be more like a watchface
    text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
    text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

    // Add it as a child layer to the Window's root layer
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
}

static void main_window_unload(Window *window) {
    text_layer_destroy(s_time_layer);
}

static void deinit() {
    window_destroy(s_main_window);
}