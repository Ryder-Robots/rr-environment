/*************************************************************************
 * Header file designed for micro-processors to configure themselves.
 *************************************************************************/

#ifndef RR_MICROPROCESSORS_H
#define RR_MICROPROCESSORS_H

#include <stdint.h>
#include <list>

/*******************************************************************
 * Structures and headers that maintain registers for underlying
 * micro-processors.
 *******************************************************************/
//////////////////////////////////////////////////////////////////////////
// I2C register address
//////////////////////////////////////////////////////////////////////////

#define RR_ADDR_I2C_MC1 0x08 /* Actuators, LEDs, Battery and Motors */ 
#define RR_ADDR_I2C_MC2 0x09 /* Ultrasonic and GPS */
#define RR_ADDR_I2C_MS3 0x68 /* Gyroscope and accelometer */

#endif