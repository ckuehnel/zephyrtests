/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <sensor.h>
#include <stdio.h>

#define  CYCLE 2500

void main(void)
{
	struct device *dev = device_get_binding("BME280");

	//printf("dev %p name %s\n", dev, dev->config->name);
	printf("Read sensor %s with %i msec cycle time\n", dev->config->name, CYCLE);

	while (1) {
		struct sensor_value temp, press, humidity;

		sensor_sample_fetch(dev);
		sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);
		sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);

		printf("temp: %d.%02d; press: %d.%01d; humidity: %d.%01d\n",
		      temp.val1, (int) temp.val2/10000, 
                      press.val1, (int) press.val2/100000, 
                      humidity.val1, (int) humidity.val2/100000);

		k_sleep(CYCLE);
	}
}
