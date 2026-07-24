#include "hiker.h"
#include <string.h>

#define MAX_DISTANCE_M       10.05
#define MIN_BATTERY_PCT      5
#define LOCK_TO_START_SEC    4.0
#define START_HOLD_MIN_SEC   2.0
#define RSPA_BUTTON_MIN_SEC  3.0

/**
 * @brief 원격 시동 사전조건을 확인
 */
int can_remote_start(double distance_m, int engine_off, int gear, int battery_pct)
{
    if (distance_m >= MAX_DISTANCE_M)
        return 0;

    if (!engine_off)
        return 0;

    if (gear != GEAR_P)
        return 0;

    if (battery_pct < MIN_BATTERY_PCT)
        return 0;

    return 1;
}

/**
 * @brief 원격 시동 활성화 시도
 */
int try_remote_start(int precondition_ok, int door_locked,
                     double elapsed_after_lock_sec, double start_btn_hold_sec)
{
    if (!precondition_ok)
        return START_FAIL;

    if (!door_locked)
        return START_FAIL;

    if (elapsed_after_lock_sec > LOCK_TO_START_SEC)
        return START_FAIL;

    if (start_btn_hold_sec > START_HOLD_MIN_SEC)
        return START_SUCCESS;

    return START_FAIL;
}

/**
 * @brief 스마트키 조작에 따른 비상등 점멸 횟수를 반환
 */
int get_blink_count(const char *action, int action_success)
{
    if (strcmp(action, "door_lock") == 0)
        return BLINK_DOOR_LOCK;

    if (strcmp(action, "door_unlock") == 0)
        return BLINK_DOOR_UNLOCK;

    if (strcmp(action, "remote_start") == 0)
        return BLINK_START_OK;

    return BLINK_NONE;
}

/**
 * @brief RSPA 활성화 조건을 확인
 */
int activate_rspa(double current_speed_kmh, int gear,
                  double button_hold_sec, int has_driven_above_5)
{
    if (!has_driven_above_5)
        return RSPA_INACTIVE;

    if (current_speed_kmh != 0.0)
        return RSPA_INACTIVE;

    if (gear != GEAR_N)
        return RSPA_INACTIVE;

    if (button_hold_sec > RSPA_BUTTON_MIN_SEC)
        return RSPA_ACTIVE;

    return RSPA_INACTIVE;
}
