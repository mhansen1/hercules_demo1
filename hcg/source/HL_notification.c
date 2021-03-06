/** @file HL_notification.c 
*   @brief User Notification Definition File
*   @date 03.Apr.2015
*   @version 04.04.00
*
*   This file  defines  empty  notification  routines to avoid
*   linker errors, Driver expects user to define the notification. 
*   The user needs to either remove this file and use their custom 
*   notification function or place their code sequence in this file 
*   between the provided USER CODE BEGIN and USER CODE END.
*
*/

/* 
* Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* Include Files */

#include "HL_esm.h"
#include "HL_adc.h"
#include "HL_gio.h"
#include "HL_sci.h"
#include "HL_rti.h"
#include "HL_epc.h"
#include "HL_sys_dma.h"

/* USER CODE BEGIN (0) */
#include "Application_Types.h"
#include <stdio.h>
#include <string.h>
extern button USER1,USER2;
extern uint32 g_PotReading;
extern void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length);
/* USER CODE END */
#pragma WEAK(esmGroup1Notification)
void esmGroup1Notification(esmBASE_t *esm, uint32 channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (1) */
/* USER CODE END */
}

/* USER CODE BEGIN (2) */
/* USER CODE END */
#pragma WEAK(esmGroup2Notification)
void esmGroup2Notification(esmBASE_t *esm, uint32 channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (3) */
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
#pragma WEAK(esmGroup3Notification)
void esmGroup3Notification(esmBASE_t *esm, uint32 channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (5) */
/* USER CODE END */
    for(;;)
    { 
    }/* Wait */  
/* USER CODE BEGIN (6) */
/* USER CODE END */
}

/* USER CODE BEGIN (7) */
/* USER CODE END */

#pragma WEAK(dmaGroupANotification)
void dmaGroupANotification(dmaInterrupt_t inttype, uint32 channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (8) */
/* USER CODE END */
}

/* USER CODE BEGIN (9) */
/* USER CODE END */

/* USER CODE BEGIN (10) */
/* USER CODE END */

/* USER CODE BEGIN (11) */
uint32 button_pressed_counter = 0;
uint32 button2_pressed_counter = 0;
boolean blUSER1_now_pressed = FALSE;
boolean blUSER1_was_pressed = FALSE;
boolean blUSER2_now_pressed = FALSE;
boolean blUSER2_was_pressed = FALSE;
uint32 debounce_counter_1 = 4;
uint32 debounce_counter_0 = 4;
uint8 u8PotStringBuf[100];
#define SHORT_PRESS_COUNT 10
#define LONG_PRESS_COUNT  15

/* USER CODE END */
#pragma WEAK(rtiNotification)
void rtiNotification(rtiBASE_t *rtiREG, uint32 notification)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (12) */
	if(rtiNOTIFICATION_COMPARE0 == notification)
	{
		/*check whether switch USER1 has been pressed and do a flash ecc 1 bit selftest using diagnostic library*/
		if (0 == gioGetBit(USER1_BUTTON_GPIOPORT, USER1_BUTTON_GPIOPIN))
		{
			blUSER1_now_pressed = TRUE;
			if(debounce_counter_0 == 0)
			{
			   ++button_pressed_counter;
		       if (blUSER1_now_pressed && !blUSER1_was_pressed)
		       {
			      debounce_counter_0 = 3;
	           }
	           if ((button_pressed_counter > SHORT_PRESS_COUNT) && (button_pressed_counter < LONG_PRESS_COUNT))
	           {
	    	      USER1 = SHORT_PRESS;
	           }
	           blUSER1_was_pressed = blUSER1_now_pressed;
			}
			else
			{
				--debounce_counter_0;
				USER1 = NONE;
			}
		}
	    else
	    {
	    	if(debounce_counter_0 == 0)
	    	{
              USER1 = NONE;
              blUSER1_now_pressed = FALSE;
              blUSER1_was_pressed = FALSE;
              button_pressed_counter = 0;
	    	}
	    	else
	    	{
	    		--debounce_counter_0;
	    	}
	    }
		/*check whether switch USER2 has been pressed and do a CCMR4F error forcing fault inject using the diagnostic library API*/
		if (0 == gioGetBit(USER2_BUTTON_GPIOPORT,USER2_BUTTON_GPIOPIN))
		{
			blUSER2_now_pressed = TRUE;
			if(debounce_counter_1 == 0)
			{
			   ++button2_pressed_counter;
		       if (blUSER2_now_pressed && !blUSER2_was_pressed)
		       {
		    	   debounce_counter_1 = 3;
	           }
	           if ((button2_pressed_counter > SHORT_PRESS_COUNT) && (button2_pressed_counter < LONG_PRESS_COUNT))
	           {
	    	      USER2 = SHORT_PRESS;
	           }
	           blUSER2_was_pressed = blUSER2_now_pressed;
			}
			else
			{
				--debounce_counter_1;
				USER2 = NONE;
			}
		}
	    else
	    {
	    	if(debounce_counter_1 == 0)
	    	{
              USER2 = NONE;
              blUSER2_now_pressed = FALSE;
              blUSER2_was_pressed = FALSE;
              button2_pressed_counter = 0;
	    	}
	    	else
	    	{
	    		--debounce_counter_1;
	    	}
	    }
	}
	else if(rtiNOTIFICATION_COMPARE1 == notification)
	{
		gioSetBit(LED1_GPIOPORT,LED1_GPIOPIN,gioGetBit(LED1_GPIOPORT,LED1_GPIOPIN) ^ 0x00000001);
	}
	else if(rtiNOTIFICATION_COMPARE2 == notification)
	{
		gioSetBit(LED2_GPIOPORT,LED2_GPIOPIN,gioGetBit(LED2_GPIOPORT,LED2_GPIOPIN) ^ 0x00000001);
	}
	else if(rtiNOTIFICATION_COMPARE3 == notification)
	{
		sprintf((char*)u8PotStringBuf, "Potentiometer Reading: %d\r\n", g_PotReading);
		sciDisplayText(sciREG1,u8PotStringBuf,strlen((char*)u8PotStringBuf));
	}
/* USER CODE END */
}

/* USER CODE BEGIN (13) */
/* USER CODE END */
#pragma WEAK(adcNotification)
void adcNotification(adcBASE_t *adc, uint32 group)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (14) */
/* USER CODE END */
}

/* USER CODE BEGIN (15) */
/* USER CODE END */
#pragma WEAK(gioNotification)
void gioNotification(gioPORT_t *port, uint32 bit)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (22) */
/* USER CODE END */
}

/* USER CODE BEGIN (23) */
/* USER CODE END */

#pragma WEAK(sciNotification)
void sciNotification(sciBASE_t *sci, uint32 flags)     
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (32) */
/* USER CODE END */
}

/* USER CODE BEGIN (33) */
/* USER CODE END */



/* USER CODE BEGIN (46) */
/* USER CODE END */


/* USER CODE BEGIN (50) */
/* USER CODE END */


/* USER CODE BEGIN (53) */
/* USER CODE END */


/* USER CODE BEGIN (56) */
/* USER CODE END */

#pragma WEAK(epcCAMFullNotification)
void epcCAMFullNotification(void)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (57) */
/* USER CODE END */
}
#pragma WEAK(epcFIFOFullNotification)
void epcFIFOFullNotification(uint32 epcFIFOStatus)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (58) */
/* USER CODE END */
}

/* USER CODE BEGIN (59) */
/* USER CODE END */


/* USER CODE BEGIN (61) */
/* USER CODE END */

/* USER CODE BEGIN (63) */
/* USER CODE END */
