#include <pebble.h>
#include <time.h>
#include "mytimer.h"
    
static void init();
static void deinit();
static void main_window_load(Window *window);
static void main_window_unload(Window *window);

static Window *s_main_window;
static TextLayer *s_time_layer;
static GBitmap *right_bar_bitmap;
static GBitmap *top_button_bitmap;
static GBitmap *middle_button_bitmap;
static GBitmap *bottom_button_bitmap;
static BitmapLayer *right_bar_layer;
static BitmapLayer *top_button_layer;
static BitmapLayer *middle_button_layer;
static BitmapLayer *bottom_button_layer;

static GFont large_time_font;

int main(void) {
  init();
  app_event_loop();
  deinit();
}


static void init() {
    // Create main Window element and assign to pointer
    s_main_window = window_create();
    window_set_fullscreen(s_main_window, true);

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
    //Font
    large_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_VCR_OSD_NUMERIC_24));
    
    
    // Create time TextLayer
    s_time_layer = text_layer_create(GRect(0, 40, 127, 50));
    text_layer_set_background_color(s_time_layer, GColorClear);
    text_layer_set_text_color(s_time_layer, GColorBlack);
    
    
    
    //Load bitmap and layer for right bar and buttons
    //Right bar
    right_bar_bitmap = gbitmap_create_with_resource(RESOURCE_ID_RIGHT_BAR_IMG);
    right_bar_layer = bitmap_layer_create(GRect(127, 0, 17, 168));
    bitmap_layer_set_bitmap(right_bar_layer, right_bar_bitmap);
    
    //Top button
    top_button_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TOP_BUTTON_IMG);
    top_button_layer = bitmap_layer_create(GRect(129, 7, 14, 10));
    bitmap_layer_set_bitmap(top_button_layer, top_button_bitmap);
    
    //Middle button
    middle_button_bitmap = gbitmap_create_with_resource(RESOURCE_ID_MIDDLE_BUTTON_IMG);
    middle_button_layer = bitmap_layer_create(GRect(129, 79, 12, 12));
    bitmap_layer_set_bitmap(middle_button_layer, middle_button_bitmap);
    
    //Bottom button
    bottom_button_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BOTTOM_BUTTON_IMG);
    bottom_button_layer = bitmap_layer_create(GRect(130, 149, 14, 13));
    bitmap_layer_set_bitmap(bottom_button_layer, bottom_button_bitmap);
    
    
    
    //Initialize timer with the newly created layer
    mytimer_set_text_label(s_time_layer);
    mytimer_start_timer();
    
    //Display time zero
    mytimer_set_timer_text(0, 0, 0);

    // Improve the layout to be more like a watchface
    text_layer_set_font(s_time_layer, large_time_font);
    text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

    // Add it as a child layer to the Window's root layer
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(right_bar_layer));
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(top_button_layer));
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(middle_button_layer));
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bottom_button_layer));
}

static void main_window_unload(Window *window) {
    text_layer_destroy(s_time_layer);
    gbitmap_destroy(right_bar_bitmap);
    gbitmap_destroy(top_button_bitmap);
    gbitmap_destroy(middle_button_bitmap);
    gbitmap_destroy(bottom_button_bitmap);
    bitmap_layer_destroy(right_bar_layer);
    bitmap_layer_destroy(top_button_layer);
    bitmap_layer_destroy(middle_button_layer);
    bitmap_layer_destroy(bottom_button_layer);
    fonts_unload_custom_font(large_time_font);
}

static void deinit() {
    window_destroy(s_main_window);
}