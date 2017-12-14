/**
 * @file can_pic32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Uniswarm 2017
 *
 * @date December 8 2017, 09:10 AM
 *
 * @brief CAN support for rtprog for PIC32MK, PIC32MX, PIC32MZDA,
 * PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS61154C :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61154C.pdf
 */

#include "can.h"

#include <driver/sysclock.h>
#include <archi.h>

#if !defined (CAN_COUNT) || CAN_COUNT==0
  #warning "No can on the current device or unknow device"
#endif

#define CAN_FLAG_UNUSED  0x00
typedef struct {
    union {
        struct {
            unsigned used : 1;
            unsigned enabled : 1;
            unsigned : 6;
        };
        uint8_t val;
    };
} can_status;

struct can_dev
{
    CAN_MODE mode;
    uint32_t bitRate;
    uint8_t propagSeg;
    uint8_t s1Seg;
    uint8_t s2Seg;
    can_status flags;
};

struct can_dev cans[] = {
    {
        .bitRate = 0,
        .flags = {{.val = CAN_FLAG_UNUSED}}
    },
#if CAN_COUNT>=2
    {
        .bitRate = 0,
        .flags = {{.val = CAN_FLAG_UNUSED}}
    },
#endif
#if CAN_COUNT>=3
    {
        .bitRate = 0,
        .flags = {{.val = CAN_FLAG_UNUSED}}
    },
#endif
#if CAN_COUNT>=4
    {
        .bitRate = 0,
        .flags = {{.val = CAN_FLAG_UNUSED}}
    },
#endif
};

/**
 * @brief Gives a free CAN bus number and open it
 * @return CAN bus number
 */
rt_dev_t can_getFreeDevice()
{
#if CAN_COUNT>=1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < CAN_COUNT; i++)
        if (cans[i].flags.used == 0)
            break;

    if (i == CAN_COUNT)
        return NULLDEV;
    device = MKDEV(DEV_CLASS_CAN, i);

    can_open(device);

    return device;
#else
    return NULLDEV;
#endif
}

/**
 * @brief Opens a CAN bus
 * @param can CAN bus id
 * @return 0 if ok, -1 in case of error
 */
int can_open(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return -1;
    if (cans[can].flags.used == 1)
        return -1;

    cans[can].flags.used = 1;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Closes and release a CAN bus
 * @param device CAN bus number
 * @return 0 if ok, -1 in case of error
 */
int can_closeDevice(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return -1;

    can_disable(device);

    cans[can].flags.val = CAN_FLAG_UNUSED;
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Enables the specified CAN bus
 * @param device CAN bus number
 * @return 0 if ok, -1 in case of error
 */
int can_enable(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return -1;

    cans[can].flags.enabled = 1;

    switch (can)
    {
    case 0:
        // TODO
        break;
#if CAN_COUNT>=2
    case 1:
        // TODO
        break;
#endif
    }

    return 0;
}

/**
 * @brief Disables the specified CAN bus
 * @param device CAN bus number
 * @return 0 if ok, -1 in case of error
 */
int can_disable(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return -1;

    cans[can].flags.enabled = 0;

    switch (can)
    {
    case 0:
        _CAN1IE = 0;       // disable can global interrupt
        C1CONbits.REQOP = 4;
        while(C1CONbits.OPMOD != 4);
        C1CONbits.ON = 0;  // disable can
        while(C1CONbits.CANBUSY == 1);
        break;
#if CAN_COUNT>=2
    case 1:
        _CAN2IE = 0;       // disable can global interrupt
        C2CONbits.REQOP = 4;
        while(C2CONbits.OPMOD != 4);
        C2CONbits.ON = 0;  // disable can
        while(C2CONbits.CANBUSY == 1);
        break;
#endif
#if CAN_COUNT>=3
    case 2:
        _CAN3IE = 0;       // disable can global interrupt
        C3CONbits.REQOP = 4;
        while(C3CONbits.OPMOD != 4);
        C3CONbits.ON = 0;  // disable can
        while(C3CONbits.CANBUSY == 1);
        break;
#endif
#if CAN_COUNT>=4
    case 3:
        _CAN4IE = 0;       // disable can global interrupt
        C4CONbits.REQOP = 4;
        while(C4CONbits.OPMOD != 4);
        C4CONbits.ON = 0;  // disable can
        while(C4CONbits.CANBUSY == 1);
        break;
#endif
    }

    return 0;
}

/**
 * @brief Sets configuration (can version and mode) of the specified CAN bus
 * @param device CAN bus number
 * @param mode CAN mode of operation
 * @return 0 if ok, -1 in case of error
 */
int can_setConfig(rt_dev_t device, CAN_MODE mode)
{
    uint8_t can = MINOR(device);
    uint8_t modeBits;
    if (can >= CAN_COUNT)
        return 0;

    // check parameters
    switch (mode)
    {
    case CAN_MODE_NORMAL:
        modeBits = 0b000;
        break;
    case CAN_MODE_LISTENONLY:
        modeBits = 0b011;
        break;
    case CAN_MODE_LISTENALL:
        modeBits = 0b111;
        break;
    case CAN_MODE_LOOPBACK:
        modeBits = 0b010;
        break;
    case CAN_MODE_DISABLED:
        modeBits = 0b001;
        break;
    case CAN_MODE_CONFIGURATION:
        modeBits = 0b100;
        break;
    default:
        return -1;
    }
    cans[can].mode = mode;

    switch (can)
    {
    case 0:
        C1CONbits.ON = 1;
        C1CONbits.REQOP = modeBits;
        while (C1CONbits.OPMOD != modeBits);
        break;
#if CAN_COUNT>=2
    case 1:
        C2CONbits.ON = 1;
        C2CONbits.REQOP = modeBits;
        while (C2CONbits.OPMOD != modeBits);
        break;
#endif
#if CAN_COUNT>=3
    case 2:
        C3CONbits.ON = 1;
        C3CONbits.REQOP = modeBits;
        while (C3CONbits.OPMOD != modeBits);
        break;
#endif
#if CAN_COUNT>=4
    case 3:
        C4CONbits.ON = 1;
        C4CONbits.REQOP = modeBits;
        while (C4CONbits.OPMOD != modeBits);
        break;
#endif
    }

    return 0;
}

/**
 * @brief Returns the current bus mode of operation
 * @param device CAN device number
 * @return current mode of operation
 */
CAN_MODE can_mode(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    return cans[can].mode;
#else
    return 0;
#endif
}

/**
 * @brief Sets bit rate and segments timing
 *
 * Sum of all segments (propagSeg, s1Seg, s2Seg) + 1 must be contained in
 * the range of 8 to 25 quantums.
 *
 * CAN Bit Timing (8-25 Tq) segments computation
 *
 * | Sync | Propag seg | Phase seg 1 | Phase seg 2 |
 *
 * | 1 Tq |   1-8 Tq   |   1-8 Tq    |   1-8 Tq    |
 *
 *                              sample point
 *
 * @param device CAN device number
 * @param bitRate bit rate speed in bit/s
 * @param propagSeg propagation segment duration in number of quantum (1-8)
 * @param s1Seg segment 1 duration in number of quantum (1-8)
 * @param s2Seg segment 2 duration in number of quantum (1-8)
 * @return 0 if ok, -1 in case of error
 */
int can_setBitTiming(rt_dev_t device, uint32_t bitRate, uint8_t propagSeg, uint8_t s1Seg, uint8_t s2Seg)
{
    uint8_t can = MINOR(device);
    uint8_t bitRateDiv;
    uint8_t quantum;
    if (can >= CAN_COUNT)
        return 0;

    if (propagSeg > 8 || s1Seg > 8 || s2Seg > 8)
        return -1;
    quantum = propagSeg + s1Seg + s2Seg + 1;
    if (quantum < 8 || quantum > 25)
        return -1;

    cans[can].bitRate = bitRate;
    cans[can].propagSeg = propagSeg;
    cans[can].s1Seg = s1Seg;
    cans[can].s2Seg = s2Seg;

    bitRateDiv = sysclock_periphFreq(SYSCLOCK_CLOCK_CAN) / (quantum * 2);

    switch (can)
    {
    case 0:
        C1CONbits.ON = 1;
        C1CONbits.REQOP = 4;
        while (C1CONbits.OPMOD != 4);

        C1CFGbits.SJW    = 0;          // Synchronization Jump Width (1-4)
        C1CFGbits.PRSEG  = propagSeg;  // Propagation Time Segment (1-8)
        C1CFGbits.SEG1PH = s1Seg - 1;  // Phase Buffer Segment 1 (1-8)
        C1CFGbits.SEG2PHTS = 1;        // Phase Buffer Segment 2 is freely programmable
        C1CFGbits.SEG2PH = s2Seg - 1;  // Phase Buffer Segment 2 (1-8) SEG2PH ≤ SEG1PH
        C1CFGbits.BRP    = bitRateDiv; // bit rate divisor (1-64) * 2
        break;
#if CAN_COUNT>=2
    case 1:
        C2CONbits.ON = 1;
        C2CONbits.REQOP = 4;
        while (C2CONbits.OPMOD != 4);

        C2CFGbits.SJW    = 0;          // Synchronization Jump Width (1-4)
        C2CFGbits.PRSEG  = propagSeg;  // Propagation Time Segment (1-8)
        C2CFGbits.SEG1PH = s1Seg - 1;  // Phase Buffer Segment 1 (1-8)
        C2CFGbits.SEG2PHTS = 1;        // Phase Buffer Segment 2 is freely programmable
        C2CFGbits.SEG2PH = s2Seg - 1;  // Phase Buffer Segment 2 (1-8) SEG2PH ≤ SEG1PH
        C2CFGbits.BRP    = bitRateDiv; // bit rate divisor (1-64) * 2
        break;
#endif
#if CAN_COUNT>=3
    case 2:
        C3CONbits.ON = 1;
        C3CONbits.REQOP = 4;
        while (C3CONbits.OPMOD != 4);

        C3CFGbits.SJW    = 0;          // Synchronization Jump Width (1-4)
        C3CFGbits.PRSEG  = propagSeg;  // Propagation Time Segment (1-8)
        C3CFGbits.SEG1PH = s1Seg - 1;  // Phase Buffer Segment 1 (1-8)
        C3CFGbits.SEG2PHTS = 1;        // Phase Buffer Segment 2 is freely programmable
        C3CFGbits.SEG2PH = s2Seg - 1;  // Phase Buffer Segment 2 (1-8) SEG2PH ≤ SEG1PH
        C3CFGbits.BRP    = bitRateDiv; // bit rate divisor (1-64) * 2
        break;
#endif
#if CAN_COUNT>=4
    case 3:
        C4CONbits.ON = 1;
        C4CONbits.REQOP = 4;
        while (C4CONbits.OPMOD != 4);

        C4CFGbits.SJW    = 0;          // Synchronization Jump Width (1-4)
        C4CFGbits.PRSEG  = propagSeg;  // Propagation Time Segment (1-8)
        C4CFGbits.SEG1PH = s1Seg - 1;  // Phase Buffer Segment 1 (1-8)
        C4CFGbits.SEG2PHTS = 1;        // Phase Buffer Segment 2 is freely programmable
        C4CFGbits.SEG2PH = s2Seg - 1;  // Phase Buffer Segment 2 (1-8) SEG2PH ≤ SEG1PH
        C4CFGbits.BRP    = bitRateDiv; // bit rate divisor (1-64) * 2
        break;
#endif
    }

    return 0;
}

/**
 * @brief Returns the curent bit rate in bits/s
 * @param device CAN device number
 * @return bit rate in bits/s if ok, 0 in case of error
 */
uint32_t can_bitRate(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    return cans[can].bitRate;
#else
    return 0;
#endif
}

/**
 * @brief Gets the effective bit rate in hertz
 * @param device CAN device number
 * @return speed of receive and transmit in bits/s, 0 in case of error
 */
uint32_t can_effectiveBitRate(rt_dev_t device)
{
    uint32_t baudSpeed;
    uint16_t uBrg;

    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    // TODO

    return baudSpeed;
}

/**
 * @brief Gets propagation segment duration in quantums
 * @param device CAN device number
 * @return propagation segment duration in quantums, 0 in case of error
 */
uint8_t can_propagSeg(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    return cans[can].propagSeg;
#else
    return 0;
#endif
}

/**
 * @brief Gets segment 1 duration in quantums
 * @param device CAN device number
 * @return segment 1 duration in quantums, 0 in case of error
 */
uint8_t can_s1Seg(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    return cans[can].s1Seg;
#else
    return 0;
#endif
}

/**
 * @brief Gets segment 2 duration in quantums
 * @param device CAN device number
 * @return segment 2 duration in quantums, 0 in case of error
 */
uint8_t can_s2Seg(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    return cans[can].s2Seg;
#else
    return 0;
#endif
}
