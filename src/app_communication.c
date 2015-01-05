#include <pebble.h>
#include "app_communication.h"
#include "main_window.h"
#include "pebble_atof.h"
#include "mytimer.h"
#include "message_keys.h"
#include "run_sender.h"
    
//Method declaration
void send_initial_request();

static double lapLength;
static char* units;
static bool useDistanceForAlarm;
static double endDistance;
static int endTime;
static int lapCount;
static int* lapTimes = NULL;
static unsigned short checkedFlags;

static AppMessageResult results[] = {APP_MSG_OK, APP_MSG_SEND_TIMEOUT, APP_MSG_SEND_REJECTED,
                                     APP_MSG_NOT_CONNECTED, APP_MSG_APP_NOT_RUNNING, APP_MSG_INVALID_ARGS,
                                     APP_MSG_BUSY, APP_MSG_BUFFER_OVERFLOW, APP_MSG_ALREADY_RELEASED,
                                     APP_MSG_CALLBACK_ALREADY_REGISTERED, APP_MSG_CALLBACK_NOT_REGISTERED,
                                     APP_MSG_OUT_OF_MEMORY, APP_MSG_CLOSED, APP_MSG_INTERNAL_ERROR};
static char* resultsString[] = {"APP_MESSAGE_OK", "APP_MSG_SEND_TIMEOUT", "APP_MSG_SEND_REJECTED",
                                "APP_MSG_NOT_CONNECTED", "APP_MSG_APP_NOT_RUNNING", "APP_MSG_INVALID_ARGS",
                                "APP_MSG_BUSY", "APP_MSG_BUFFER_OVERFLOW", "APP_MSG_ALREADY_RELEASED",
                                "APP_MSG_CALLBACK_ALREADY_REGISTERED", "APP_MSG_CALLBACK_NOT_REGISTERED",
                                "APP_MSG_OUT_OF_MEMORY", "APP_MSG_CLOSED", "APP_MSG_INTERNAL_ERROR"};

void print_app_message_log(AppMessageResult result) {
    char message[40];
    
    unsigned int i = 0;
    bool found = false;
    for(i = 0; i < sizeof(results) / sizeof(AppMessageResult); i++) {
        if(results[i] == result) {
            found = true;
            strcpy(message, resultsString[i]);
        }
    }
    
    if(!found) {
        snprintf(message, 39, "%u", result);
    }
    
    APP_LOG(APP_LOG_LEVEL_INFO, "AppMessageResult: %s", message);
}

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
    checkedFlags = 0;
    
    send_initial_request();
}


void app_communications_inbox_received_callback(DictionaryIterator *iterator, void *context) {
    Tuple *t = dict_read_first(iterator);
    
    while(t != NULL) {
        switch(t->key) {
            case LAP_LENGTH_KEY:
                lapLength = pebble_atof(t->value->cstring);
                checkedFlags |= 1 << 0;
                break;
            case UNITS_KEY:
                units = t->value->cstring;
                checkedFlags |= 1 << 1;
                break;
            case USE_DISTANCE_ALARM_KEY:
                useDistanceForAlarm = ((t->value->int8 == 0) ? false : true);
                checkedFlags |= 1 << 2;
                break;
            case END_DISTANCE_KEY:
                endDistance = pebble_atof(t->value->cstring);
                checkedFlags |= 1 << 3;
                break;
            case END_TIME_KEY:
                endTime = t->value->int32;
                checkedFlags |= 1 << 4;
                break;
            default:
                APP_LOG(APP_LOG_LEVEL_WARNING, "UNKNOWN TUPLE KEY RECIEVED: %d", (int)t->key);
        }
        t = dict_read_next(iterator);
    }
    
    main_window_update_values(lapLength, units, useDistanceForAlarm, endDistance, endTime, lapCount);
    
    static const unsigned short fullChangeVal = 1 << 4 | 1 << 3 | 1 << 2 | 1 << 1 | 1 << 0;
    if(checkedFlags == fullChangeVal) {
        show_no_connection_message(false);
    }
    
    APP_LOG(APP_LOG_LEVEL_INFO, "Message received!");
}

void app_communications_inbox_dropped_callback(AppMessageResult reason, void *context) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
    print_app_message_log(reason);
}

void app_communications_outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
    print_app_message_log(reason);
}

void app_communications_outbox_sent_callback(DictionaryIterator *iterator, void *context) {
    APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
    
    Tuple* openTuple = dict_find(iterator, RUN_OPEN);
    Tuple* timeTuple = dict_find(iterator, RUN_TIME);
    Tuple* lapTimeTuple = dict_find(iterator, RUN_LAP_TIME);
    
    if(openTuple != NULL || timeTuple != NULL || lapTimeTuple != NULL) {
        send_run_decide_action(lapTimes, mytimer_get_mill_count(), lapCount);
    }
}

void send_initial_request() {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    Tuplet request = TupletInteger(REQUEST_INITIAL, 0);
    
    dict_write_tuplet(iter, &request);
    
    dict_write_end(iter);
    
    AppMessageResult result = app_message_outbox_send();
    APP_LOG(APP_LOG_LEVEL_INFO, "INITIAL REQUEST SENDING...");
    print_app_message_log(result);
}


void add_lap()
{
    int time = mytimer_get_mill_count();
    
    lapTimes = realloc(lapTimes, sizeof(int)*(lapCount + 1));
    
    //Add newest time
    lapTimes[lapCount] = time;
    
    lapCount++;
    main_window_update_values(lapLength, units, useDistanceForAlarm, endDistance, endTime, lapCount);
}

void send_run() {
    if(lapCount > 0 && mytimer_get_mill_count() > 0) {
        send_open_run();
    }
}
