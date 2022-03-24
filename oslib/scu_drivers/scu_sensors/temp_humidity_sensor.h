/* temp_humidity_sensor.h
 * Created: 19/03/2021
 * Updated:
 * Author: Matthew Kumar
 */

#ifndef TEMP_HUMIDITY_SENSOR_H
#define TEMP_HUMIDITY_SENSOR_H

#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>
#include <stdio.h>
#include <sys/util.h>

extern struct sensor_value temp;
extern struct sensor_value hum;

extern void hts221_handler(const struct device *dev, const struct sensor_trigger *trig);
extern void process_sample_temp_hum(const struct device *dev);
extern void get_temp_humidity_sen(void);


#endif

