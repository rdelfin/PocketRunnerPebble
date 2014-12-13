#include <pebble.h>
#include "main_window.h"
#include "app_communication.h"

int main(void) {
    //Setup
    show_main_window();
    setup_app_communications();
    
    //App loop
    app_event_loop();
}