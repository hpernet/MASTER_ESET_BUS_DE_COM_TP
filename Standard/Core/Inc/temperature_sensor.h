/*
 * temperature_sensor.h
 *
 *  Created on: Oct 6, 2022
 *      Author: hugop
 */

#ifndef INC_TEMPERATURE_SENSOR_H_
#define INC_TEMPERATURE_SENSOR_H_

#include "main.h"
#include "one_wire_driver.h"

void temp_sensor_setup(void);

void temp_sensor_run(void);

#endif /* INC_TEMPERATURE_SENSOR_H_ */
