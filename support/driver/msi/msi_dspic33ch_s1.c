/**
 * @file msi_dspic33ch.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018
 *
 * @date March 2, 10:00 AM
 *
 * @brief Master Slave Interface driver for dsPIC33CH, slave part
 *
 * Implementation based on Microchip document DS70005278B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-Master-Slave-Interface-MSI-Module-70005278b.pdf
 */

#include "msi.h"

#include <archi.h>

/**
 * @brief Gives the status of the master core
 * @return MSI_CORE_STATUS status enum
 */
 MSI_CORE_STATUS msi_master_status(void)
{
    if (SI1STATbits.MSTRST)
    {
        return MSI_CORE_STATUS_RESETED;
    }

    switch (SI1STATbits.MSTPWR)
    {
    case 0b00:
        return MSI_CORE_STATUS_LOWPOWERRUN;
    case 0b01:
        return MSI_CORE_STATUS_STARTED;
    case 0b10:
        return MSI_CORE_STATUS_SLEEPED;
    }

    return MSI_CORE_STATUS_RESETED;
}

int msi_protocol_write(const uint8_t protocol, const unsigned char *data, uint8_t size)
{
    UDK_UNUSED(protocol);
    UDK_UNUSED(size);

    if (_DTRDYB == 1)
    {
        return -1;
    }
    uint16_t *ptr = (uint16_t *)data;
    SI1MBX5D = *(ptr++);
    SI1MBX6D = *(ptr++);
    SI1MBX7D = *(ptr++);
    SI1MBX8D = *(ptr++);
    SI1MBX9D = *(ptr++);
    return 0;
}

/**
 * @brief Gets number of data that could be read (in sw buffer)
 * @param protocol protocol id
 * @return 0 if mail is full and can not be written, 1 if OK, -1 if protocol is not valid
 */
int msi_protocol_canWrite(const uint8_t protocol)
{
    UDK_UNUSED(protocol);
    if (_DTRDYB == 1)  // MailBox is full
    {
        return 0;
    }
    return 1;
}

int msi_protocol_read(const uint8_t protocol, unsigned char *data, uint8_t max_size)
{
    UDK_UNUSED(protocol);
    UDK_UNUSED(max_size);

    if (_DTRDYA == 0)
    {
        return -1;
    }
    uint16_t *ptr = (uint16_t *)data;
    *ptr = SI1MBX0D;
    ptr++;
    *ptr = SI1MBX1D;
    ptr++;
    *ptr = SI1MBX2D;
    ptr++;
    *ptr = SI1MBX3D;
    ptr++;
    *ptr = SI1MBX4D;
    return 0;
}

/**
 * @brief Gets number of data that could be read (in sw buffer)
 * @param protocol protocol id
 * @return 0 if mail is empty, 1 if OK to be read, -1 if protocol is not valid
 */
int msi_protocol_canRead(const uint8_t protocol)
{
    UDK_UNUSED(protocol);
    if (_DTRDYA == 0)  // MailBox is empty
    {
        return 0;
    }
    return 1;
}
