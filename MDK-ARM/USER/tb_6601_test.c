/***********************************************************
File:	解码主机送过来的IIC数据，控制PA0-7/PB2-9
			的信号输出与主机对应起来；检测当PA8变低电
			平时，拉高PA15，平时PA15保持低电平
***********************************************************/
#include "tb_6601_test.h"


uint8_t BUFF[2];			//状态接收缓存区
uint8_t RE_BUFF[1];	
uint8_t CK_BUFF[1];	
/*-----------------------------------------------------------
	函数名： test_6601
	输  入： 无
	输  出： 无
	说  明： 获取主机发过来的PA0-7/PB2-9状态,控制PA0-7/PB2-9；
           检测当PA8，变低电平时拉高 PA15，平时PA15保持低电
	返回值： 无
 ----------------------------------------------------------*/
void test_6601(void)
{
	re_date();
	com_port();
	PA8_detec();
	Re_Port();
}


/*-----------------------------------------------------------
	函数名： re_date
	输  入： 无
	输  出： 无
	说  明： 通过IIC接收主机发送过来的PA0-7/PB2-9的状态
	返回值： 无
 -----------------------------------------------------------*/
void re_date(void)
{
	char i;
	for(i=0;i<2;i++)
	{ 
		printf("IIC test! \r\n");
		while(HAL_I2C_Slave_Receive(&hi2c2, RE_BUFF, 1, 100)!= HAL_OK) {	}
    printf("IIC OK! RE_BUFF[%d]= %x\r   \r\n",i,RE_BUFF[0]);
	  BUFF[i]= RE_BUFF[0];								//第一位是PA控制状态，第二位是PB控制状态
	}
}



/*-----------------------------------------------------------
	函数名： com_port
	输  入： 无
	输  出： 无
	说  明： 控制PA0-7/PB2-9的状态
	返回值： 无
 ----------------------------------------------------------*/
void com_port(void)
{
	/*	PA0-7状态控制	*/
	HAL_GPIO_WritePin ( GPIOA,PA0_Pin,( BUFF[0] &0x80 ));
	HAL_GPIO_WritePin ( GPIOA,PA1_Pin,( BUFF[0] &0x40 ));
	HAL_GPIO_WritePin ( GPIOA,PA2_Pin,( BUFF[0] &0x20 ));
	HAL_GPIO_WritePin ( GPIOA,PA3_Pin,( BUFF[0] &0x10 ));
	HAL_GPIO_WritePin ( GPIOA,PA4_Pin,( BUFF[0] &0x08 ));
	HAL_GPIO_WritePin ( GPIOA,PA5_Pin,( BUFF[0] &0x04 ));
	HAL_GPIO_WritePin ( GPIOA,PA6_Pin,( BUFF[0] &0x02 ));
	HAL_GPIO_WritePin ( GPIOA,PA7_Pin,( BUFF[0] &0x01));
	
	/*	PB2-9状态控制	*/
	HAL_GPIO_WritePin ( GPIOB,PB2_Pin,( BUFF[1] &0x80 ));
	HAL_GPIO_WritePin ( GPIOB,PB3_Pin,( BUFF[1] &0x40 ));
	HAL_GPIO_WritePin ( GPIOB,PB4_Pin,( BUFF[1] &0x20 ));
	HAL_GPIO_WritePin ( GPIOB,PB5_Pin,( BUFF[1] &0x10 ));
	HAL_GPIO_WritePin ( GPIOB,PB6_Pin,( BUFF[1] &0x08 ));
	HAL_GPIO_WritePin ( GPIOB,PB7_Pin,( BUFF[1] &0x04 ));
	HAL_GPIO_WritePin ( GPIOB,PB8_Pin,( BUFF[1] &0x02 ));
	HAL_GPIO_WritePin ( GPIOB,PB9_Pin,( BUFF[1] &0x01));
}

/*---------------------------------------------------
	函数名： Re_Port
	输  入： 无
	输  出： 无
	说  明： 串口查看PA0-PA7、PB2-PB9的状态
	返回值： 无
 --------------------------------------------------*/
void Re_Port(void)
{

	
	CK_BUFF[0] = HAL_GPIO_ReadPin(GPIOA ,PA0_Pin) << 7;
	CK_BUFF[0] = CK_BUFF[0] | ( HAL_GPIO_ReadPin(GPIOA ,PA1_Pin) << 6 );
	CK_BUFF[0] = CK_BUFF[0] | ( HAL_GPIO_ReadPin(GPIOA ,PA2_Pin) << 5 );
	CK_BUFF[0] = CK_BUFF[0] | ( HAL_GPIO_ReadPin(GPIOA ,PA3_Pin) << 4 );
	CK_BUFF[0] = CK_BUFF[0] | ( HAL_GPIO_ReadPin(GPIOA ,PA4_Pin) << 3 );
	CK_BUFF[0] = CK_BUFF[0] | ( HAL_GPIO_ReadPin(GPIOA ,PA5_Pin) << 2 );
	CK_BUFF[0] = CK_BUFF[0] | ( HAL_GPIO_ReadPin(GPIOA ,PA6_Pin) << 1 );
	CK_BUFF[0] = CK_BUFF[0] | HAL_GPIO_ReadPin(GPIOA ,PA7_Pin);
	
	printf("CK_PA = 0x%x\r\n",CK_BUFF[0]);
	
	CK_BUFF[0] = HAL_GPIO_ReadPin(GPIOB ,PB2_Pin) << 7;
	CK_BUFF[0] = CK_BUFF[0] | ( HAL_GPIO_ReadPin(GPIOB ,PB3_Pin) << 6 );
	CK_BUFF[0] = CK_BUFF[0] | ( HAL_GPIO_ReadPin(GPIOB ,PB4_Pin) << 5 );
	CK_BUFF[0] = CK_BUFF[0] | ( HAL_GPIO_ReadPin(GPIOB ,PB5_Pin) << 4 );
	CK_BUFF[0] = CK_BUFF[0] | ( HAL_GPIO_ReadPin(GPIOB ,PB6_Pin) << 3 );
	CK_BUFF[0] = CK_BUFF[0] | ( HAL_GPIO_ReadPin(GPIOB ,PB7_Pin) << 2 );
	CK_BUFF[0] = CK_BUFF[0] | ( HAL_GPIO_ReadPin(GPIOB ,PB8_Pin) << 1 );
	CK_BUFF[0] = CK_BUFF[0] | HAL_GPIO_ReadPin(GPIOB ,PB9_Pin);
	
	printf("CK_PB = 0x%x\r\n",CK_BUFF[0]);
	
	
	HAL_Delay(10); //串口调试用延时

}

/*------------------------------------------------------------
	函数名： PA8_detec
	输  入： 无
	输  出： 无
	说  明： 检测当PA8变低电平时拉高 PA15，平时PA15保持低电平
	返回值： 无
 -----------------------------------------------------------*/
void PA8_detec(void)
{
	if( HAL_GPIO_ReadPin(GPIOA ,PA8_Pin) == RESET )
	{
		HAL_GPIO_WritePin(GPIOA,PA15_Pin,GPIO_PIN_SET);
	}
	else 
	{
		HAL_GPIO_WritePin(GPIOA,PA15_Pin,GPIO_PIN_RESET);
	}
}



