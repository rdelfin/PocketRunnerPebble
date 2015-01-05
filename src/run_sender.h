#pragma once

void send_open_run();

void send_initial_run_data(int time, int laps);

void send_lap_time(int lapIndex, int times[]);

void send_close_run();

void send_run_decide_action(int times[], int time, int laps);