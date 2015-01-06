#include <pebble.h>
#include "run_sender.h"
#include "app_communication.h"
#include "message_keys.h"
    
static int lapCounter;
static bool initialDataSent;
static bool runClosed;
static uint8_t uuid[16];
    
void send_open_run() {
    lapCounter = 0;
    initialDataSent = false;
    runClosed = false;
    
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    Tuplet openMsg = TupletInteger(RUN_OPEN, 0);
    
    dict_write_tuplet(iter, &openMsg);
    
    dict_write_end(iter);
    
    AppMessageResult result = app_message_outbox_send();
    APP_LOG(APP_LOG_LEVEL_INFO, "OPEN RUN SENDING...");
    print_app_message_log(result);
}

void send_initial_run_data(int time, int laps) {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    Tuplet timeVal = TupletInteger(RUN_TIME, time);
    Tuplet lapsVal = TupletInteger(RUN_LAPS, laps);
    Tuplet uuidVal = TupletBytes(RUN_UUID_ACK, uuid, sizeof(uuid));
     
    dict_write_tuplet(iter, &timeVal);
    dict_write_tuplet(iter, &lapsVal);
    dict_write_tuplet(iter, &uuidVal);
    
    dict_write_end(iter);
    
    AppMessageResult result = app_message_outbox_send();
    APP_LOG(APP_LOG_LEVEL_INFO, "RUN INITIAL DATA SENDING...");
    print_app_message_log(result);
}

void send_lap_time(int lapIndex, int times[]) {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    Tuplet timeVal = TupletInteger(RUN_LAP_TIME, times[lapIndex]);
    Tuplet uuidVal = TupletBytes(RUN_UUID_ACK, uuid, sizeof(uuid));
    
    dict_write_tuplet(iter, &timeVal);
    dict_write_tuplet(iter, &uuidVal);
    
    dict_write_end(iter);
    
    AppMessageResult result = app_message_outbox_send();
    APP_LOG(APP_LOG_LEVEL_INFO, "RUN LAP TIME SENDING...");
    print_app_message_log(result);
}

void send_close_run() {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    Tuplet closeMsg = TupletBytes(RUN_CLOSE, uuid, sizeof(uuid));
    
    dict_write_tuplet(iter, &closeMsg);
    
    dict_write_end(iter);
    
    AppMessageResult result = app_message_outbox_send();
    APP_LOG(APP_LOG_LEVEL_INFO, "CLOSE RUN SENDING...");
    print_app_message_log(result);
}



void send_run_decide_action(int times[], int time, int laps) {
    if(!initialDataSent) {
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Sending initial data");
        send_initial_run_data(time, laps);
        initialDataSent = true;
    } else if(lapCounter < laps) {
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Sending lap number %d", lapCounter);
        send_lap_time(lapCounter, times);
        lapCounter++;
    } else if(!runClosed) {
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Sending close");
        send_close_run();
    }
}

void setuuid(uint8_t bytes[]) {
    //UUID is always 16 bytes long (128 bits)
    for(int i= 0; i < 16; i++) {
        uuid[i] = bytes[i];
    }
}
