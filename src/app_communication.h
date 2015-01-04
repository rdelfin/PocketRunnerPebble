#include <pebble.h>
#pragma once

void setup_app_communications();
void app_communications_inbox_received_callback(DictionaryIterator *iterator, void *context);
void app_communications_inbox_dropped_callback(AppMessageResult reason, void *context);
void app_communications_outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
void app_communications_outbox_sent_callback(DictionaryIterator *iterator, void *context);

void send_run();

void add_lap();