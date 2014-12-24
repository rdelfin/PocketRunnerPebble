#include <pebble.h>
#include "app_communication.h"
#include "main_window.h"
#include "pebble_atof.h"
#include "mytimer.h"

//DEFINES FOR MESSAGES    
#define LAP_LENGTH_KEY 0
#define UNITS_KEY 1
#define USE_DISTANCE_ALARM_KEY 2
#define END_DISTANCE_KEY 3
#define END_TIME_KEY 4

    
#define LAP_ADD_TIME_PEBBLE_KEY 5
#define LAP_ADD_MSG_PHONE_KEY 6
#define PAUSE_TIME_PEBBLE_KEY 7
#define PAUSE_TIME_PHONE_KEY 8

static double lapLength;
static char* units;
static bool useDistanceForAlarm;
static double endDistance;
static int endTime;
static int lapCount;


void setup_app_communications() {
    app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
    app_message_register_inbox_received(app_communications_inbox_received_callback);
    app_message_register_inbox_dropped(app_communications_inbox_dropped_callback);
    app_message_register_outbox_failed(app_communications_outbox_failed_callback);
    app_message_register_outbox_sent(app_communications_outbox_sent_callback);
    lapCount = 0;
    lapLength = 0;
    units = "";
    useDistanceForAlarm = false;
    endDistance = 0;
    endTime = 0;
    lapCount = 0;
}

//Methods to be used by buttons/click handlers
void send_pause(int32_t time)
{
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    Tuplet timeVal = TupletInteger(LAP_ADD_TIME_PEBBLE_KEY, (int32_t)time);
    dict_write_tuplet(iter, &timeVal);
    
    dict_write_end(iter);
    
    app_message_outbox_send();
}

void send_lap(int32_t time)
{
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    Tuplet timeVal = TupletInteger(PAUSE_TIME_PEBBLE_KEY, (int32_t)time);
    dict_write_tuplet(iter, &timeVal);
    
    dict_write_end(iter);
    
    app_message_outbox_send();
}


void app_communications_inbox_received_callback(DictionaryIterator *iterator, void *context) {
    Tuple *t = dict_read_first(iterator);
    
    while(t != NULL) {
        switch(t->key) {
            case LAP_LENGTH_KEY:
                lapLength = pebble_atof(t->value->cstring);
                break;
            case UNITS_KEY:
                units = t->value->cstring;
                break;
            case USE_DISTANCE_ALARM_KEY:
                useDistanceForAlarm = ((t->value->int8 == 0) ? false : true);
                break;
            case END_DISTANCE_KEY:
                endDistance = pebble_atof(t->value->cstring);
                break;
            case END_TIME_KEY:
                endTime = t->value->int32;
                break;
            case LAP_ADD_MSG_PHONE_KEY:
                add_lap();
                break;
            case PAUSE_TIME_PEBBLE_KEY:
                mytimer_stop_timer();
                mytimer_set_time(t->value->int32);
                break;
            default:
                APP_LOG(APP_LOG_LEVEL_DEBUG, "UNKNOWN TUPLE KEY RECIEVED: %d", (int)t->key);
        }
        t = dict_read_next(iterator);
    }
    
    main_window_update_values(lapLength, units, useDistanceForAlarm, endDistance, endTime, lapCount);
    
    APP_LOG(APP_LOG_LEVEL_INFO, "Message received!");
}

void app_communications_inbox_dropped_callback(AppMessageResult reason, void *context) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

void app_communications_outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

void app_communications_outbox_sent_callback(DictionaryIterator *iterator, void *context) {
    APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}


void add_lap()
{
    lapCount++;
    main_window_update_values(lapLength, units, useDistanceForAlarm, endDistance, endTime, lapCount);
}