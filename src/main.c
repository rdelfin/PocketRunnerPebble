#include <pebble.h>
#include <time.h>
#include "mytimer.h"
#include "main_window.h"

int main(void) {
  show_main_window();
  app_event_loop();
}