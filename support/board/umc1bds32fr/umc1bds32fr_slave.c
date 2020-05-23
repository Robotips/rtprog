/**
 * @file umc1bds32fr_slave.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018
 *
 * @date March 1, 2019, 09:35 AM
 *
 * @brief Code for UMC1BDS32FR / UMC1BDS32FR-I board, slave core
 * 
 * product page:
 *  https://uniswarm.eu/uboards/umc/umc1bds32fr
 */

#include "umc1bds32fr.h"

#include "driver/sysclock.h"
#include "driver/gpio.h"

rt_dev_t board_leds[LED_COUNT];

int board_init_io()
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x001F;         // all analog inputs of port A as analog
    ANSELB = 0x0006;         // all analog inputs of port B as digital buffer
    ANSELC = 0x00CF;         // all analog inputs of port C as digital buffer
    ANSELD = 0xF000;         // all analog inputs of port D as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

    _QEIA1R = 47;
    _QEIB1R = 46;
    _QEINDX1R = 60;

    // Lock configuration pin
    lockIoConfig();
#endif

    board_leds[0] = gpio_pin(GPIO_PORTC, 14);
    gpio_setBitConfig(board_leds[0], GPIO_OUTPUT);
    board_leds[1] = gpio_pin(GPIO_PORTC, 13);
    gpio_setBitConfig(board_leds[1], GPIO_OUTPUT);

    return 0;
}

int board_init()
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, SYSCLOCK_POSC);
    archi_init();

    board_init_io();

    return 0;
}

int board_setLed(uint8_t led, uint8_t state)
{
    if(led >= LED_COUNT)
        return -1;

    if (state & 1)
        gpio_setBit(board_leds[led]);
    else
        gpio_clearBit(board_leds[led]);
    return 0;
}

int board_toggleLed(uint8_t led)
{
    if(led >= LED_COUNT)
        return -1;

    gpio_toggleBit(board_leds[led]);
    return 0;
}

int8_t board_getLed(uint8_t led)
{
    if(led >= LED_COUNT)
        return -1;

    return gpio_readBit(board_leds[led]);
}

int8_t board_getButton(uint8_t button)
{
    return -1;
}
