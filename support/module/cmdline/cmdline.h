/**
 * @file cmdline.h
 * @author Sebastien CAUX (sebcaux) \
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date October 10, 2016, 10:44 PM
 *
 * @brief Base implementation for cmdline module
 */

#ifndef CMDLINE_H
#define CMDLINE_H

#include "driver/device.h"
#include <stdint.h>

void cmdline_init(void);
void cmdline_setDevice(rt_dev_t deviceIn, rt_dev_t deviceOut);
void cmdline_task(void);

#endif  // CMDLINE_H
