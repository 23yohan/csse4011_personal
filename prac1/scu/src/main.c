#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>
#include <stdio.h>
#include <sys/util.h>

#include "temp_humidity_sensor.h"
#include "temp_pressure_sensor.h"
#include "motion_sensor.h"
#include "air_quality_sensor.h"

#define STACK_SIZE 1024
#define PRIORITY 3

struct k_mutex sensor_mutex;

void init_mutex() {
	k_mutex_init(&sensor_mutex);
}

void thread_get_temp(void *a, void *b, void *c) {

	k_mutex_lock(&sensor_mutex, K_FOREVER);

	while(1) {
		k_mutex_unlock(&sensor_mutex);
		get_temp_humidity_sen();
		k_msleep(1000);
		printf("Temp is :%.1f C\n", sensor_value_to_double(&temp));
		k_mutex_lock(&sensor_mutex, K_FOREVER);
	} 
	
	
}

int main(void) {
	//get_temp_pres_values();
	//get_temp_humidity_sen();
	//get_motion_values();
	//get_air_quality_val();
	
    return 0;
}

K_THREAD_DEFINE(sensor_id, STACK_SIZE,
                thread_get_temp, NULL, NULL, NULL,
                PRIORITY, 0, 0);

