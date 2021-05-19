/**
 * @file gpio_pic24_dspic30f_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2021
 *
 * @date March 20, 2017, 18:39 AM
 *
 * @brief GPIO support driver for dsPIC30F, dsPIC33CH, dsPIC33CK, dsPIC33FJ,
 * dsPIC33EP, dsPIC33EV, PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 *
 * Implementation based on Microchip document DS70058D, DS70193D and DS70000598C :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70058D.pdf (dsPIC30F)
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70193D.pdf (PIC24F/dsPIC33F)
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70000598c.pdf (PIC24E/dsPIC33E)
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-IO-Ports-with-Edge-Detect-70005322b.pdf (dsPIC33C)
 */

#ifndef GPIO_PIC24_DSPIC30_DSPIC33_H
#define GPIO_PIC24_DSPIC30_DSPIC33_H

// compute PORT count and existance on device
#if defined(DEVICE_30F2011) || defined(DEVICE_30F3012)
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_PORT_COUNT 3
#elif defined(DEVICE_30F2012) || defined(DEVICE_30F3013)
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTF
#    define GPIO_PORT_COUNT 4
#elif defined(DEVICE_30F5011) || defined(DEVICE_30F6011) || defined(DEVICE_30F6011A) || defined(DEVICE_30F6012)        \
    || defined(DEVICE_30F6012A) || defined(DEVICE_33FJ128GP206) || defined(DEVICE_33FJ128GP206A)                       \
    || defined(DEVICE_33FJ128GP306) || defined(DEVICE_33FJ128GP306A) || defined(DEVICE_33FJ128GP706)                   \
    || defined(DEVICE_33FJ128GP706A) || defined(DEVICE_33FJ256GP506) || defined(DEVICE_33FJ256GP506A)                  \
    || defined(DEVICE_33FJ64GP206) || defined(DEVICE_33FJ64GP206A) || defined(DEVICE_33FJ64GP306)                      \
    || defined(DEVICE_33FJ64GP306A) || defined(DEVICE_33FJ64GP706) || defined(DEVICE_33FJ64GP706A)                     \
    || defined(DEVICE_24HJ128GP206) || defined(DEVICE_24HJ128GP206A) || defined(DEVICE_24HJ128GP306)                   \
    || defined(DEVICE_24HJ128GP306A) || defined(DEVICE_24HJ128GP506) || defined(DEVICE_24HJ128GP506A)                  \
    || defined(DEVICE_24HJ256GP206) || defined(DEVICE_24HJ256GP206A) || defined(DEVICE_24HJ64GP206)                    \
    || defined(DEVICE_24HJ64GP206A) || defined(DEVICE_24HJ64GP506) || defined(DEVICE_24HJ64GP506A)
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_PORT_COUNT 5
#elif defined(DEVICE_30F2010) || defined(DEVICE_30F3010) || defined(DEVICE_30F3011) || defined(DEVICE_30F4011)         \
    || defined(DEVICE_30F4012)
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_PORT_COUNT 5
#elif defined(DEVICE_30F5015) || defined(DEVICE_30F6015) || defined(DEVICE_33EP256MU806)                               \
    || defined(DEVICE_33EP512GP806) || defined(DEVICE_33EP512MC806) || defined(DEVICE_33FJ128MC506)                    \
    || defined(DEVICE_33FJ128MC506A) || defined(DEVICE_33FJ128MC706) || defined(DEVICE_33FJ128MC706A)                  \
    || defined(DEVICE_33FJ32GS406) || defined(DEVICE_33FJ32GS606) || defined(DEVICE_33FJ64GS406)                       \
    || defined(DEVICE_33FJ64GS606) || defined(DEVICE_33FJ64MC506) || defined(DEVICE_33FJ64MC506A)                      \
    || defined(DEVICE_33FJ64MC706) || defined(DEVICE_33FJ64MC706A) || defined(DEVICE_24EP512GP806)                     \
    || defined(DEVICE_24FJ1024GA606) || defined(DEVICE_24FJ1024GB606) || defined(DEVICE_24FJ128DA106)                  \
    || defined(DEVICE_24FJ128DA206) || defined(DEVICE_24FJ128GA006) || defined(DEVICE_24FJ128GA106)                    \
    || defined(DEVICE_24FJ128GA306) || defined(DEVICE_24FJ128GA606) || defined(DEVICE_24FJ128GB106)                    \
    || defined(DEVICE_24FJ128GB206) || defined(DEVICE_24FJ128GB606) || defined(DEVICE_24FJ128GC006)                    \
    || defined(DEVICE_24FJ192GA106) || defined(DEVICE_24FJ192GB106) || defined(DEVICE_24FJ256DA106)                    \
    || defined(DEVICE_24FJ256DA206) || defined(DEVICE_24FJ256GA106) || defined(DEVICE_24FJ256GA606)                    \
    || defined(DEVICE_24FJ256GB106) || defined(DEVICE_24FJ256GB206) || defined(DEVICE_24FJ256GB606)                    \
    || defined(DEVICE_24FJ512GA606) || defined(DEVICE_24FJ512GB606) || defined(DEVICE_24FJ64GA006)                     \
    || defined(DEVICE_24FJ64GA106) || defined(DEVICE_24FJ64GA306) || defined(DEVICE_24FJ64GB106)                       \
    || defined(DEVICE_24FJ64GC006) || defined(DEVICE_24FJ96GA006)
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_PORT_COUNT 6
#elif defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP502)                   \
    || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1)                  \
    || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CK128MP202)                    \
    || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP502)                    \
    || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP502)                       \
    || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP502)                       \
    || defined(DEVICE_33EP128GP502) || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128MC202)                    \
    || defined(DEVICE_33EP128MC502) || defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP16GS502)                      \
    || defined(DEVICE_33EP256GP502) || defined(DEVICE_33EP256MC202) || defined(DEVICE_33EP256MC502)                    \
    || defined(DEVICE_33EP32GP502) || defined(DEVICE_33EP32GS202) || defined(DEVICE_33EP32GS502)                       \
    || defined(DEVICE_33EP32MC202) || defined(DEVICE_33EP32MC502) || defined(DEVICE_33EP512GP502)                      \
    || defined(DEVICE_33EP512MC202) || defined(DEVICE_33EP512MC502) || defined(DEVICE_33EP64GP502)                     \
    || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64MC202) || defined(DEVICE_33EP64MC502)                       \
    || defined(DEVICE_33EV128GM002) || defined(DEVICE_33EV128GM102) || defined(DEVICE_33EV256GM002)                    \
    || defined(DEVICE_33EV256GM102) || defined(DEVICE_33EV32GM002) || defined(DEVICE_33EV32GM102)                      \
    || defined(DEVICE_33EV64GM002) || defined(DEVICE_33EV64GM102) || defined(DEVICE_33FJ06GS001)                       \
    || defined(DEVICE_33FJ06GS101) || defined(DEVICE_33FJ06GS101A) || defined(DEVICE_33FJ06GS102)                      \
    || defined(DEVICE_33FJ06GS102A) || defined(DEVICE_33FJ06GS202) || defined(DEVICE_33FJ06GS202A)                     \
    || defined(DEVICE_33FJ09GS302) || defined(DEVICE_33FJ128GP202) || defined(DEVICE_33FJ128GP802)                     \
    || defined(DEVICE_33FJ128MC202) || defined(DEVICE_33FJ128MC802) || defined(DEVICE_33FJ12GP201)                     \
    || defined(DEVICE_33FJ12GP202) || defined(DEVICE_33FJ12MC201) || defined(DEVICE_33FJ12MC202)                       \
    || defined(DEVICE_33FJ16GP101) || defined(DEVICE_33FJ16GP102) || defined(DEVICE_33FJ16GS402)                       \
    || defined(DEVICE_33FJ16GS502) || defined(DEVICE_33FJ16MC101) || defined(DEVICE_33FJ16MC102)                       \
    || defined(DEVICE_33FJ32GP101) || defined(DEVICE_33FJ32GP102) || defined(DEVICE_33FJ32GP202)                       \
    || defined(DEVICE_33FJ32GP302) || defined(DEVICE_33FJ32MC101) || defined(DEVICE_33FJ32MC102)                       \
    || defined(DEVICE_33FJ32MC202) || defined(DEVICE_33FJ32MC302) || defined(DEVICE_33FJ64GP202)                       \
    || defined(DEVICE_33FJ64GP802) || defined(DEVICE_33FJ64MC202) || defined(DEVICE_33FJ64MC802)                       \
    || defined(DEVICE_24EP128GP202) || defined(DEVICE_24EP128MC202) || defined(DEVICE_24EP256GP202)                    \
    || defined(DEVICE_24EP256MC202) || defined(DEVICE_24EP32GP202) || defined(DEVICE_24EP32MC202)                      \
    || defined(DEVICE_24EP512GP202) || defined(DEVICE_24EP512MC202) || defined(DEVICE_24EP64GP202)                     \
    || defined(DEVICE_24EP64MC202) || defined(DEVICE_24F04KA200) || defined(DEVICE_24F04KA201)                         \
    || defined(DEVICE_24F04KL100) || defined(DEVICE_24F04KL101) || defined(DEVICE_24F08KA101)                          \
    || defined(DEVICE_24F08KA102) || defined(DEVICE_24F08KL200) || defined(DEVICE_24F08KL201)                          \
    || defined(DEVICE_24F08KL301) || defined(DEVICE_24F08KL302) || defined(DEVICE_24F08KL401)                          \
    || defined(DEVICE_24F08KL402) || defined(DEVICE_24F08KM101) || defined(DEVICE_24F08KM102)                          \
    || defined(DEVICE_24F08KM202) || defined(DEVICE_24F16KA101) || defined(DEVICE_24F16KA102)                          \
    || defined(DEVICE_24F16KA301) || defined(DEVICE_24F16KA302) || defined(DEVICE_24F16KL401)                          \
    || defined(DEVICE_24F16KL402) || defined(DEVICE_24F16KM102) || defined(DEVICE_24F16KM202)                          \
    || defined(DEVICE_24F32KA301) || defined(DEVICE_24F32KA302) || defined(DEVICE_24FJ128GA202)                        \
    || defined(DEVICE_24FJ128GA702) || defined(DEVICE_24FJ128GB202) || defined(DEVICE_24FJ16GA002)                     \
    || defined(DEVICE_24FJ16MC101) || defined(DEVICE_24FJ16MC102) || defined(DEVICE_24FJ256GA702)                      \
    || defined(DEVICE_24FJ32GA002) || defined(DEVICE_24FJ32GA102) || defined(DEVICE_24FJ32GB002)                       \
    || defined(DEVICE_24FJ32MC101) || defined(DEVICE_24FJ32MC102) || defined(DEVICE_24FJ48GA002)                       \
    || defined(DEVICE_24FJ64GA002) || defined(DEVICE_24FJ64GA102) || defined(DEVICE_24FJ64GA202)                       \
    || defined(DEVICE_24FJ64GA702) || defined(DEVICE_24FJ64GB002) || defined(DEVICE_24FJ64GB202)                       \
    || defined(DEVICE_24FV08KM101) || defined(DEVICE_24FV08KM102) || defined(DEVICE_24FV08KM202)                       \
    || defined(DEVICE_24FV16KA301) || defined(DEVICE_24FV16KA302) || defined(DEVICE_24FV16KM102)                       \
    || defined(DEVICE_24FV16KM202) || defined(DEVICE_24FV32KA301) || defined(DEVICE_24FV32KA302)                       \
    || defined(DEVICE_24HJ128GP202) || defined(DEVICE_24HJ128GP502) || defined(DEVICE_24HJ12GP201)                     \
    || defined(DEVICE_24HJ12GP202) || defined(DEVICE_24HJ32GP202) || defined(DEVICE_24HJ32GP302)                       \
    || defined(DEVICE_24HJ64GP202) || defined(DEVICE_24HJ64GP502)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_PORT_COUNT 2
#elif defined(DEVICE_30F1010) || defined(DEVICE_30F2020)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_PORT_COUNT 5
#elif defined(DEVICE_30F2023)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_PORT_COUNT 6
#elif defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1) || defined(DEVICE_33CH128MP503)                   \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP203S1)                  \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CK128MP203)                    \
    || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP503)                    \
    || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP503)                       \
    || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP503)                       \
    || defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM604) || defined(DEVICE_33EP128GP504)                    \
    || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128MC204)                    \
    || defined(DEVICE_33EP128MC504) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505)                      \
    || defined(DEVICE_33EP256GM304) || defined(DEVICE_33EP256GM604) || defined(DEVICE_33EP256GP504)                    \
    || defined(DEVICE_33EP256MC204) || defined(DEVICE_33EP256MC504) || defined(DEVICE_33EP32GP503)                     \
    || defined(DEVICE_33EP32GP504) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505)                       \
    || defined(DEVICE_33EP32MC203) || defined(DEVICE_33EP32MC204) || defined(DEVICE_33EP32MC503)                       \
    || defined(DEVICE_33EP32MC504) || defined(DEVICE_33EP512GM304) || defined(DEVICE_33EP512GM604)                     \
    || defined(DEVICE_33EP512GP504) || defined(DEVICE_33EP512MC204) || defined(DEVICE_33EP512MC504)                    \
    || defined(DEVICE_33EP64GP503) || defined(DEVICE_33EP64GP504) || defined(DEVICE_33EP64GS504)                       \
    || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64MC203)                       \
    || defined(DEVICE_33EP64MC204) || defined(DEVICE_33EP64MC503) || defined(DEVICE_33EP64MC504)                       \
    || defined(DEVICE_33EV128GM003) || defined(DEVICE_33EV128GM004) || defined(DEVICE_33EV128GM103)                    \
    || defined(DEVICE_33EV128GM104) || defined(DEVICE_33EV256GM003) || defined(DEVICE_33EV256GM004)                    \
    || defined(DEVICE_33EV256GM103) || defined(DEVICE_33EV256GM104) || defined(DEVICE_33EV32GM003)                     \
    || defined(DEVICE_33EV32GM004) || defined(DEVICE_33EV32GM103) || defined(DEVICE_33EV32GM104)                       \
    || defined(DEVICE_33EV64GM003) || defined(DEVICE_33EV64GM004) || defined(DEVICE_33EV64GM103)                       \
    || defined(DEVICE_33EV64GM104) || defined(DEVICE_33FJ128GP204) || defined(DEVICE_33FJ128GP804)                     \
    || defined(DEVICE_33FJ128MC204) || defined(DEVICE_33FJ128MC804) || defined(DEVICE_33FJ16GP304)                     \
    || defined(DEVICE_33FJ16GS404) || defined(DEVICE_33FJ16GS504) || defined(DEVICE_33FJ16MC304)                       \
    || defined(DEVICE_33FJ32GP104) || defined(DEVICE_33FJ32GP204) || defined(DEVICE_33FJ32GP304)                       \
    || defined(DEVICE_33FJ32MC104) || defined(DEVICE_33FJ32MC204) || defined(DEVICE_33FJ32MC304)                       \
    || defined(DEVICE_33FJ64GP204) || defined(DEVICE_33FJ64GP804) || defined(DEVICE_33FJ64MC204)                       \
    || defined(DEVICE_33FJ64MC804) || defined(DEVICE_24EP128GP204) || defined(DEVICE_24EP128MC204)                     \
    || defined(DEVICE_24EP256GP204) || defined(DEVICE_24EP256MC204) || defined(DEVICE_24EP32GP203)                     \
    || defined(DEVICE_24EP32GP204) || defined(DEVICE_24EP32MC203) || defined(DEVICE_24EP32MC204)                       \
    || defined(DEVICE_24EP512GP204) || defined(DEVICE_24EP512MC204) || defined(DEVICE_24EP64GP203)                     \
    || defined(DEVICE_24EP64GP204) || defined(DEVICE_24EP64MC203) || defined(DEVICE_24EP64MC204)                       \
    || defined(DEVICE_24F08KM204) || defined(DEVICE_24F16KA304) || defined(DEVICE_24F16KM104)                          \
    || defined(DEVICE_24F16KM204) || defined(DEVICE_24F32KA304) || defined(DEVICE_24FJ128GA204)                        \
    || defined(DEVICE_24FJ128GA704) || defined(DEVICE_24FJ128GA705) || defined(DEVICE_24FJ128GB204)                    \
    || defined(DEVICE_24FJ16GA004) || defined(DEVICE_24FJ256GA704) || defined(DEVICE_24FJ256GA705)                     \
    || defined(DEVICE_24FJ32GA004) || defined(DEVICE_24FJ32GA104) || defined(DEVICE_24FJ32GB004)                       \
    || defined(DEVICE_24FJ32MC104) || defined(DEVICE_24FJ48GA004) || defined(DEVICE_24FJ64GA004)                       \
    || defined(DEVICE_24FJ64GA104) || defined(DEVICE_24FJ64GA204) || defined(DEVICE_24FJ64GA704)                       \
    || defined(DEVICE_24FJ64GA705) || defined(DEVICE_24FJ64GB004) || defined(DEVICE_24FJ64GB204)                       \
    || defined(DEVICE_24FV08KM204) || defined(DEVICE_24FV16KA304) || defined(DEVICE_24FV16KM104)                       \
    || defined(DEVICE_24FV16KM204) || defined(DEVICE_24FV32KA304) || defined(DEVICE_24HJ128GP204)                      \
    || defined(DEVICE_24HJ128GP504) || defined(DEVICE_24HJ16GP304) || defined(DEVICE_24HJ32GP204)                      \
    || defined(DEVICE_24HJ32GP304) || defined(DEVICE_24HJ64GP204) || defined(DEVICE_24HJ64GP504)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_PORT_COUNT 3
#elif defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                   \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH256MP205)                  \
    || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1)                \
    || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506)                  \
    || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP505)                  \
    || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1)                \
    || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206)                     \
    || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP505S1)                   \
    || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CK128MP205)                    \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506)                    \
    || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP505)                    \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP205)                      \
    || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506)                       \
    || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206)                       \
    || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33EP128GS705)                      \
    || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806)                    \
    || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS506)                       \
    || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_PORT_COUNT 4
#elif defined(DEVICE_30F3014) || defined(DEVICE_30F4013)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTF
#    define GPIO_PORT_COUNT 5
#elif defined(DEVICE_30F5013) || defined(DEVICE_30F6013) || defined(DEVICE_30F6013A) || defined(DEVICE_30F6014)        \
    || defined(DEVICE_30F6014A) || defined(DEVICE_33FJ128GP708) || defined(DEVICE_33FJ128GP708A)                       \
    || defined(DEVICE_33FJ64GP708) || defined(DEVICE_33FJ64GP708A)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_PORT_COUNT 6
#elif defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP508)                   \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP208S1)                \
    || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CH512MP508S1)                \
    || defined(DEVICE_33CH64MP208) || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP508)                     \
    || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP508)                   \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK64MP208)                     \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS808)                     \
    || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS808)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_PORT_COUNT 5
#elif defined(DEVICE_30F5016) || defined(DEVICE_30F6010) || defined(DEVICE_30F6010A) || defined(DEVICE_33EDV64MC205)   \
    || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310) || defined(DEVICE_33EP128GM706)                    \
    || defined(DEVICE_33EP128GM710) || defined(DEVICE_33EP128GP506) || defined(DEVICE_33EP128MC206)                    \
    || defined(DEVICE_33EP128MC506) || defined(DEVICE_33EP256GM306) || defined(DEVICE_33EP256GM310)                    \
    || defined(DEVICE_33EP256GM706) || defined(DEVICE_33EP256GM710) || defined(DEVICE_33EP256GP506)                    \
    || defined(DEVICE_33EP256MC206) || defined(DEVICE_33EP256MC506) || defined(DEVICE_33EP256MU810)                    \
    || defined(DEVICE_33EP512GM306) || defined(DEVICE_33EP512GM310) || defined(DEVICE_33EP512GM706)                    \
    || defined(DEVICE_33EP512GM710) || defined(DEVICE_33EP512GP506) || defined(DEVICE_33EP512MC206)                    \
    || defined(DEVICE_33EP512MC506) || defined(DEVICE_33EP512MU810) || defined(DEVICE_33EP64GP506)                     \
    || defined(DEVICE_33EP64MC206) || defined(DEVICE_33EP64MC506) || defined(DEVICE_33EV128GM006)                      \
    || defined(DEVICE_33EV128GM106) || defined(DEVICE_33EV256GM006) || defined(DEVICE_33EV256GM106)                    \
    || defined(DEVICE_33EV32GM006) || defined(DEVICE_33EV32GM106) || defined(DEVICE_33EV64GM006)                       \
    || defined(DEVICE_33EV64GM106) || defined(DEVICE_33FJ128GP310) || defined(DEVICE_33FJ128GP310A)                    \
    || defined(DEVICE_33FJ128GP710) || defined(DEVICE_33FJ128GP710A) || defined(DEVICE_33FJ128MC510)                   \
    || defined(DEVICE_33FJ128MC510A) || defined(DEVICE_33FJ128MC708) || defined(DEVICE_33FJ128MC708A)                  \
    || defined(DEVICE_33FJ128MC710) || defined(DEVICE_33FJ128MC710A) || defined(DEVICE_33FJ256GP510)                   \
    || defined(DEVICE_33FJ256GP510A) || defined(DEVICE_33FJ256GP710) || defined(DEVICE_33FJ256GP710A)                  \
    || defined(DEVICE_33FJ256MC510) || defined(DEVICE_33FJ256MC510A) || defined(DEVICE_33FJ256MC710)                   \
    || defined(DEVICE_33FJ256MC710A) || defined(DEVICE_33FJ32GS608) || defined(DEVICE_33FJ32GS610)                     \
    || defined(DEVICE_33FJ64GP310) || defined(DEVICE_33FJ64GP310A) || defined(DEVICE_33FJ64GP710)                      \
    || defined(DEVICE_33FJ64GP710A) || defined(DEVICE_33FJ64GS608) || defined(DEVICE_33FJ64GS610)                      \
    || defined(DEVICE_33FJ64MC508) || defined(DEVICE_33FJ64MC508A) || defined(DEVICE_33FJ64MC510)                      \
    || defined(DEVICE_33FJ64MC510A) || defined(DEVICE_33FJ64MC710) || defined(DEVICE_33FJ64MC710A)                     \
    || defined(DEVICE_24EP128GP206) || defined(DEVICE_24EP128MC206) || defined(DEVICE_24EP256GP206)                    \
    || defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256MC206) || defined(DEVICE_24EP512GP206)                    \
    || defined(DEVICE_24EP512GU810) || defined(DEVICE_24EP512MC206) || defined(DEVICE_24EP64GP206)                     \
    || defined(DEVICE_24EP64MC206) || defined(DEVICE_24FJ1024GA610) || defined(DEVICE_24FJ1024GB610)                   \
    || defined(DEVICE_24FJ128DA110) || defined(DEVICE_24FJ128DA210) || defined(DEVICE_24FJ128GA008)                    \
    || defined(DEVICE_24FJ128GA010) || defined(DEVICE_24FJ128GA108) || defined(DEVICE_24FJ128GA110)                    \
    || defined(DEVICE_24FJ128GA308) || defined(DEVICE_24FJ128GA310) || defined(DEVICE_24FJ128GA610)                    \
    || defined(DEVICE_24FJ128GB108) || defined(DEVICE_24FJ128GB110) || defined(DEVICE_24FJ128GB210)                    \
    || defined(DEVICE_24FJ128GB610) || defined(DEVICE_24FJ128GC010) || defined(DEVICE_24FJ192GA108)                    \
    || defined(DEVICE_24FJ192GA110) || defined(DEVICE_24FJ192GB108) || defined(DEVICE_24FJ192GB110)                    \
    || defined(DEVICE_24FJ256DA110) || defined(DEVICE_24FJ256DA210) || defined(DEVICE_24FJ256GA108)                    \
    || defined(DEVICE_24FJ256GA110) || defined(DEVICE_24FJ256GA610) || defined(DEVICE_24FJ256GB108)                    \
    || defined(DEVICE_24FJ256GB110) || defined(DEVICE_24FJ256GB210) || defined(DEVICE_24FJ256GB610)                    \
    || defined(DEVICE_24FJ512GA610) || defined(DEVICE_24FJ512GB610) || defined(DEVICE_24FJ64GA008)                     \
    || defined(DEVICE_24FJ64GA010) || defined(DEVICE_24FJ64GA108) || defined(DEVICE_24FJ64GA110)                       \
    || defined(DEVICE_24FJ64GA308) || defined(DEVICE_24FJ64GA310) || defined(DEVICE_24FJ64GB108)                       \
    || defined(DEVICE_24FJ64GB110) || defined(DEVICE_24FJ64GC010) || defined(DEVICE_24FJ96GA008)                       \
    || defined(DEVICE_24FJ96GA010) || defined(DEVICE_24HJ128GP210) || defined(DEVICE_24HJ128GP210A)                    \
    || defined(DEVICE_24HJ128GP310) || defined(DEVICE_24HJ128GP310A) || defined(DEVICE_24HJ128GP510)                   \
    || defined(DEVICE_24HJ128GP510A) || defined(DEVICE_24HJ256GP210) || defined(DEVICE_24HJ256GP210A)                  \
    || defined(DEVICE_24HJ256GP610) || defined(DEVICE_24HJ256GP610A) || defined(DEVICE_24HJ64GP210)                    \
    || defined(DEVICE_24HJ64GP210A) || defined(DEVICE_24HJ64GP510) || defined(DEVICE_24HJ64GP510A)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_PORT_COUNT 7
#elif defined(DEVICE_24FJ128GA406) || defined(DEVICE_24FJ128GA410) || defined(DEVICE_24FJ128GA412)                     \
    || defined(DEVICE_24FJ128GB406) || defined(DEVICE_24FJ128GB410) || defined(DEVICE_24FJ128GB412)                    \
    || defined(DEVICE_24FJ256GA406) || defined(DEVICE_24FJ256GA410) || defined(DEVICE_24FJ256GA412)                    \
    || defined(DEVICE_24FJ256GB406) || defined(DEVICE_24FJ256GB410) || defined(DEVICE_24FJ256GB412)                    \
    || defined(DEVICE_24FJ64GA406) || defined(DEVICE_24FJ64GA410) || defined(DEVICE_24FJ64GA412)                       \
    || defined(DEVICE_24FJ64GB406) || defined(DEVICE_24FJ64GB410) || defined(DEVICE_24FJ64GB412)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_HAVE_PORTH
#    define GPIO_HAVE_PORTJ
#    define GPIO_PORT_COUNT 9
#elif defined(DEVICE_33EP256MU814) || defined(DEVICE_33EP512MU814) || defined(DEVICE_24EP256GU814)                     \
    || defined(DEVICE_24EP512GU814)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_HAVE_PORTH
#    define GPIO_HAVE_PORTJ
#    define GPIO_HAVE_PORTK
#    define GPIO_PORT_COUNT 10
#else
#    define GPIO_PORT_COUNT 0
#endif

#define GPIO_MAX_PORTWIDTH     16
#define GPIO_MAX_PORTWIDTHU    4
#define GPIO_MAX_PORTWIDTHMASK 0x0F

#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
#    define GPIO_HAVE_CHANGENOTIFICATION  // have change notification on pins
#    define GPIO_HAVE_OPENDRAIN           // have open drain output config

#elif defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    define GPIO_HAVE_ENCHANGENOTIFICATION  // have enhanced change notification on pins
#    define GPIO_HAVE_OPENDRAIN             // have open drain output config

#elif defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33fj)            \
    || defined(ARCHI_dspic30f)
#    define GPIO_HAVE_OPENDRAIN  // have open drain output config
#endif

#endif  // GPIO_PIC24_DSPIC30_DSPIC33_H
