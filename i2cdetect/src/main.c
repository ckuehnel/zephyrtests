/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <stdio.h>
#include <device.h>
#include <i2c.h>

#define I2C_DEV CONFIG_I2C_0_NAME

struct device *i2c_dev;

uint8_t first = 0x03;
uint8_t last  = 0x77;

static int read_byte(struct device *i2c_dev, uint8_t *data, uint8_t address)
{
	struct i2c_msg msg;

	/* Read from device. STOP after this. */
	msg.buf = data;
	msg.len = 1;
	msg.flags = I2C_MSG_READ | I2C_MSG_STOP;

	return i2c_transfer(i2c_dev, &msg, 1, address);
}


void i2c_detect(uint8_t first, uint8_t last)
{
	uint8_t i, data, address;
	int error;
	char buff[10];
	
	printk("\ni2c detect...\n\n");
	
	// table header
	printf("   ");
	for(i=0; i<16; i++)
	{
		sprintf(buff, "%3x", i);
		printf(buff);
	}
	
	// table body
	for(address = 0; address <= last; address++)
	{
		if(address % 16 == 0)
		{
			sprintf(buff, "\n%02x:", address & 0xF0);
			printf(buff);
		}
		if(address >= first && address <= last)
		{
			error = read_byte(i2c_dev, &data, address);
			if(error == 0)
			{ 
				//device found
				sprintf(buff, " %02x", address);
				printf(buff);
			}
			else printf(" --");
		}
		else printf("   ");  // address not scanned
	}
	printf("\n\nDone.\n");
}	
	

void main(void)
{
	i2c_dev = device_get_binding(I2C_DEV);
	printf("'I2C detect' scans the I2C bus for connected devices\n");
	printf("dev %p name %s\n", i2c_dev, i2c_dev->config->name);

	while (1) 
	{
		i2c_detect(first, last);
		k_sleep(5000);
	}
}
