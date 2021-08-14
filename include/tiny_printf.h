/*
 * tiny_printf.h
 *
 *  Created on: 2/06/2017
 *      Author: james
 */

#ifndef SRC_TINY_PRINTF_H_
#define SRC_TINY_PRINTF_H_

/******************************************************************************
 * Tiny Printf() for MSP430
 *
 * The codes id taken from here:
 * http://www.msp430launchpad.com/2012/06/using-printf.html
 *
 * Note: This comment was written by James Wu on 01/06/2017
 *  	 jameswu62@yahoo.co.nz
 ******************************************************************************/

/* The following are Origional comments */


/******************************************************************************
 *                          Reusable MSP430 printf()
 *
 * Description: This printf function was written by oPossum and originally
 *              posted on the 43oh.com forums. For more information on this
 *              code, please see the link below.
 *
 *              http://www.43oh.com/forum/viewtopic.php?f=10&t=1732
 *
 *              A big thanks to oPossum for sharing such great code!
 *
 * Author:  oPossum
 * Source:  http://www.43oh.com/forum/viewtopic.php?f=10&t=1732
 * Date:    10-17-11
 *
 * Note: This comment section was written by Nicholas J. Conn on 06-07-2012
 *       for use on NJC's MSP430 LaunchPad Blog.
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "stdarg.h"

void tiny_printf(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* SRC_TINY_PRINTF_H_ */
