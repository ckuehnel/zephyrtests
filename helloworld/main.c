/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <misc/printk.h>

void main(void)
{
  while(1)
  {
    printk("Hello World! This is %s\n", CONFIG_BOARD);
    k_sleep(2500);
  }
}
