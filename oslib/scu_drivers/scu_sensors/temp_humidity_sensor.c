/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>
#include <stdio.h>
#include <sys/util.h>

#include "temp_humidity_sensor.h"

struct sensor_value temp, hum;

extern void process_sample_temp_hum(const struct device *dev)
{
	static unsigned int obs;
	
	if (sensor_sample_fetch(dev) < 0) {
		printf("Sensor sample update error\n");
		return;
	}

	if (sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp) < 0) {
		printf("Cannot read HTS221 temperature channel\n");
		return;
	}

	if (sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &hum) < 0) {
		printf("Cannot read HTS221 humidity channel\n");
		return;
	}

	++obs;
	printf("Observation:%u\n", obs);

	/* display temperature */
	printf("Temperature:%.1f C\n", sensor_value_to_double(&temp));

	/* display humidity */
	printf("Relative Humidity:%.1f%%\n",
	       sensor_value_to_double(&hum));
}

extern void hts221_handler(const struct device *dev,
			   const struct sensor_trigger *trig)
{
	process_sample_temp_hum(dev);
}

void get_temp_humidity_sen(void) {
	const struct device *dev = device_get_binding("HTS221");

	if (dev == NULL) {
		printf("Could not get HTS221 device\n");
		return;
	}

	if (IS_ENABLED(CONFIG_HTS221_TRIGGER)) {
		struct sensor_trigger trig = {
			.type = SENSOR_TRIG_DATA_READY,
			.chan = SENSOR_CHAN_ALL,
		};
		if (sensor_trigger_set(dev, &trig, hts221_handler) < 0) {
			printf("Cannot configure trigger\n");
			return;
		}
	}

	while (!IS_ENABLED(CONFIG_HTS221_TRIGGER)) {
		process_sample_temp_hum(dev);
		k_sleep(K_MSEC(2000));
	}
	k_sleep(K_FOREVER);
}