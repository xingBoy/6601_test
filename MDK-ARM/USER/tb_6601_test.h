#ifndef _TB_6601_TEST_H
#define _TB_6601_TEST_H

#include "stdio.h"	
#include "stm32f0xx_hal.h"

extern I2C_HandleTypeDef hi2c2;

#define main_add 0xA0

void test_6601(void);
void re_date(void);
void PA8_detec(void);
void com_port(void);
void Re_Port(void);

#endif 
