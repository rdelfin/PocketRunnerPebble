#include "mytimer.h"
    
#pragma once

void show_main_window(void);
void hide_main_window(void);
void setup_ui_actions(void);

void set_remaing_text(char* text);
void main_window_update_values(double lapLength, char* units, bool useDistanceForAlarm, double endDistance, long endTime, int lapCount);
void main_window_set_laps(int lapCount);
void add_lap();
