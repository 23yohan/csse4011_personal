/* temp_humidity_sensor.h
 * Created: 19/03/2021
 * Updated:
 * Author: Matthew Kumar
 */

#ifndef TEMP_PRESSURE_SENSOR_H
#define TEMP_PRESSURE_SENSOR_H

extern void process_sample_temp_pres(const struct device *dev);
extern void get_temp_pres_values(void);

#endif