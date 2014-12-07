#include "main_window.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_right_bar_img;
static GBitmap *s_res_top_button_img;
static GBitmap *s_res_middle_button_img;
static GBitmap *s_res_bottom_button_img;
static GFont s_res_vcr_osd_numeric_24;
static GFont s_res_vcr_osd_alphanumeric_20;
static BitmapLayer *s_right_bar_layer;
static BitmapLayer *s_top_button_layer;
static BitmapLayer *s_middle_button_layer;
static BitmapLayer *s_bottom_button_layer;
static TextLayer *s_timer_text_layer;
static TextLayer *s_lap_text_layer;
static TextLayer *s_completed_text_layer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, true);
  
  s_res_right_bar_img = gbitmap_create_with_resource(RESOURCE_ID_RIGHT_BAR_IMG);
  s_res_top_button_img = gbitmap_create_with_resource(RESOURCE_ID_TOP_BUTTON_IMG);
  s_res_middle_button_img = gbitmap_create_with_resource(RESOURCE_ID_MIDDLE_BUTTON_IMG);
  s_res_bottom_button_img = gbitmap_create_with_resource(RESOURCE_ID_BOTTOM_BUTTON_IMG);
  s_res_vcr_osd_numeric_24 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_VCR_OSD_NUMERIC_24));
  s_res_vcr_osd_alphanumeric_20 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_VCR_OSD_ALPHANUMERIC_20));
  // s_right_bar_layer
  s_right_bar_layer = bitmap_layer_create(GRect(127, 0, 17, 168));
  bitmap_layer_set_bitmap(s_right_bar_layer, s_res_right_bar_img);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_right_bar_layer);
  
  // s_top_button_layer
  s_top_button_layer = bitmap_layer_create(GRect(129, 7, 14, 10));
  bitmap_layer_set_bitmap(s_top_button_layer, s_res_top_button_img);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_top_button_layer);
  
  // s_middle_button_layer
  s_middle_button_layer = bitmap_layer_create(GRect(129, 79, 12, 12));
  bitmap_layer_set_bitmap(s_middle_button_layer, s_res_middle_button_img);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_middle_button_layer);
  
  // s_bottom_button_layer
  s_bottom_button_layer = bitmap_layer_create(GRect(130, 149, 14, 13));
  bitmap_layer_set_bitmap(s_bottom_button_layer, s_res_bottom_button_img);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bottom_button_layer);
  
  // s_timer_text_layer
  s_timer_text_layer = text_layer_create(GRect(0, 20, 127, 30));
  text_layer_set_text(s_timer_text_layer, "0:00:00");
  text_layer_set_text_alignment(s_timer_text_layer, GTextAlignmentCenter);
  text_layer_set_font(s_timer_text_layer, s_res_vcr_osd_numeric_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_timer_text_layer);
  
  // s_lap_text_layer
  s_lap_text_layer = text_layer_create(GRect(0, 60, 127, 20));
  text_layer_set_text(s_lap_text_layer, "0 laps");
  text_layer_set_text_alignment(s_lap_text_layer, GTextAlignmentCenter);
  text_layer_set_font(s_lap_text_layer, s_res_vcr_osd_alphanumeric_20);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_lap_text_layer);
  
  // s_completed_text_layer
  s_completed_text_layer = text_layer_create(GRect(0, 110, 127, 20));
  text_layer_set_text(s_completed_text_layer, "00km/00km");
  text_layer_set_text_alignment(s_completed_text_layer, GTextAlignmentCenter);
  text_layer_set_font(s_completed_text_layer, s_res_vcr_osd_alphanumeric_20);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_completed_text_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_right_bar_layer);
  bitmap_layer_destroy(s_top_button_layer);
  bitmap_layer_destroy(s_middle_button_layer);
  bitmap_layer_destroy(s_bottom_button_layer);
  text_layer_destroy(s_timer_text_layer);
  text_layer_destroy(s_lap_text_layer);
  text_layer_destroy(s_completed_text_layer);
  gbitmap_destroy(s_res_right_bar_img);
  gbitmap_destroy(s_res_top_button_img);
  gbitmap_destroy(s_res_middle_button_img);
  gbitmap_destroy(s_res_bottom_button_img);
  fonts_unload_custom_font(s_res_vcr_osd_numeric_24);
  fonts_unload_custom_font(s_res_vcr_osd_alphanumeric_20);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_main_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
    
    setup_ui_actions();
}

void hide_main_window(void) {
  window_stack_remove(s_window, true);
}

void setup_ui_actions(void) {
    mytimer_set_text_label(s_timer_text_layer);
    mytimer_start_timer();
}
