#ifndef RPAS_INCLUDED
#define RPAS_INCLUDED

#define GEAR_P 0
#define GEAR_R 1
#define GEAR_N 2
#define GEAR_D 3

#define DOOR_UNLOCKED 0
#define DOOR_LOCKED   1

#define BLINK_NONE        0
#define BLINK_DOOR_LOCK   1
#define BLINK_DOOR_UNLOCK 2
#define BLINK_START_OK    3

#define START_SUCCESS 1
#define START_FAIL    0

#define RSPA_ACTIVE   1
#define RSPA_INACTIVE 0

int can_remote_start(double distance_m, int engine_off, int gear, int battery_pct);
int try_remote_start(int precondition_ok, int door_locked,
                     double elapsed_after_lock_sec, double start_btn_hold_sec);
int get_blink_count(const char *action, int action_success);
int activate_rspa(double current_speed_kmh, int gear,
                  double button_hold_sec, int has_driven_above_5);

#endif
