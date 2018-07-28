/**
 * @file qei_pic24e_dspic33e.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018
 *
 * @date April 18, 2016, 22:33 PM
 *
 * @brief Quadrature Encoder Interface support driver for dsPIC33EP,
 * dsPIC33EV, PIC24EP, dsPIC33CH and dsPIC33CK
 * 
 * Implementation based on Microchip document DS70601B :
 *   http://ww1.microchip.com/downloads/en/DeviceDoc/S15.pdf
 */

#ifndef QEI_PIC24E_DSPIC33E_H
#define QEI_PIC24E_DSPIC33E_H

// calculate QEI count and version on the device
#if defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) \
 || defined(DEVICE_33CH128MP203S1) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) \
 || defined(DEVICE_33CH128MP206) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) \
 || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) \
 || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) \
 || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) \
 || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) \
 || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) \
 || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) \
 || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) \
 || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) \
 || defined(DEVICE_33CH512MP205S1) || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) \
 || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) \
 || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) \
 || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CH64MP202) \
 || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP203S1) \
 || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206) \
 || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208) || defined(DEVICE_33CH64MP208S1) \
 || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503) \
 || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP505S1) \
 || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508) \
 || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33EDV64MC205) || defined(DEVICE_33EP128MC202) \
 || defined(DEVICE_33EP128MC204) || defined(DEVICE_33EP128MC206) || defined(DEVICE_33EP128MC502) \
 || defined(DEVICE_33EP128MC504) || defined(DEVICE_33EP128MC506) || defined(DEVICE_33EP256MC202) \
 || defined(DEVICE_33EP256MC204) || defined(DEVICE_33EP256MC206) || defined(DEVICE_33EP256MC502) \
 || defined(DEVICE_33EP256MC504) || defined(DEVICE_33EP256MC506) || defined(DEVICE_33EP32MC202) \
 || defined(DEVICE_33EP32MC203) || defined(DEVICE_33EP32MC204) || defined(DEVICE_33EP32MC502) \
 || defined(DEVICE_33EP32MC503) || defined(DEVICE_33EP32MC504) || defined(DEVICE_33EP512MC202) \
 || defined(DEVICE_33EP512MC204) || defined(DEVICE_33EP512MC206) || defined(DEVICE_33EP512MC502) \
 || defined(DEVICE_33EP512MC504) || defined(DEVICE_33EP512MC506) || defined(DEVICE_33EP64MC202) \
 || defined(DEVICE_33EP64MC203) || defined(DEVICE_33EP64MC204) || defined(DEVICE_33EP64MC206) \
 || defined(DEVICE_33EP64MC502) || defined(DEVICE_33EP64MC503) || defined(DEVICE_33EP64MC504) \
 || defined(DEVICE_33EP64MC506) || defined(DEVICE_24EP128MC202) || defined(DEVICE_24EP128MC204) \
 || defined(DEVICE_24EP128MC206) || defined(DEVICE_24EP256MC202) || defined(DEVICE_24EP256MC204) \
 || defined(DEVICE_24EP256MC206) || defined(DEVICE_24EP32MC202) || defined(DEVICE_24EP32MC203) \
 || defined(DEVICE_24EP32MC204) || defined(DEVICE_24EP512MC202) || defined(DEVICE_24EP512MC204) \
 || defined(DEVICE_24EP512MC206) || defined(DEVICE_24EP64MC202) || defined(DEVICE_24EP64MC203) \
 || defined(DEVICE_24EP64MC204) || defined(DEVICE_24EP64MC206)
 #define QEI_COUNT 1
#elif defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205) \
 || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502) \
 || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) \
 || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203) \
 || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) \
 || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505) \
 || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK32MP102) \
 || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) \
 || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) \
 || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) \
 || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) \
 || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) \
 || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) \
 || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) \
 || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33EP128GM304) \
 || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310) || defined(DEVICE_33EP128GM604) \
 || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) || defined(DEVICE_33EP256GM304) \
 || defined(DEVICE_33EP256GM306) || defined(DEVICE_33EP256GM310) || defined(DEVICE_33EP256GM604) \
 || defined(DEVICE_33EP256GM706) || defined(DEVICE_33EP256GM710) || defined(DEVICE_33EP256MU806) \
 || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814) || defined(DEVICE_33EP512GM304) \
 || defined(DEVICE_33EP512GM306) || defined(DEVICE_33EP512GM310) || defined(DEVICE_33EP512GM604) \
 || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710) || defined(DEVICE_33EP512MC806) \
 || defined(DEVICE_33EP512MU810) || defined(DEVICE_33EP512MU814)
 #define QEI_COUNT 2
#else
 #define QEI_COUNT 0
#endif

#define QEI_32B

#endif // QEI_PIC24E_DSPIC33E_H
