/***********************************************************
File:	���������͹�����IIC���ݣ�����PA0-7/PB2-9
			���ź������������Ӧ��������⵱PA8��͵�
			ƽʱ������PA15��ƽʱPA15���ֵ͵�ƽ
***********************************************************/
#include "tb_6601_test.h"


uint8_t BUFF[2];			//״̬���ջ�����
uint8_t RE_BUFF[1];	
uint8_t CK_BUFF[1];	
/*-----------------------------------------------------------
	�������� test_6601
	��  �룺 ��
	��  ���� ��
	˵  ���� ��ȡ������������PA0-7/PB2-9״̬,����PA0-7/PB2-9��
           ��⵱PA8����͵�ƽʱ���� PA15��ƽʱPA15���ֵ͵�
	����ֵ�� ��
 ----------------------------------------------------------*/
void test_6601(void)
{
	re_date();
	com_port();
	PA8_detec();
	Re_Port();
}


/*-----------------------------------------------------------
	�������� re_date
	��  �룺 ��
	��  ���� ��
	˵  ���� ͨ��IIC�����������͹�����PA0-7/PB2-9��״̬
	����ֵ�� ��
 -----------------------------------------------------------*/
void re_date(void)
{
	char i;
	for(i=0;i<2;i++)
	{ 
		printf("IIC test! \r\n");
		while(HAL_I2C_Slave_Receive(&hi2c2, RE_BUFF, 1, 100)!= HAL_OK) {	}
    printf("IIC OK! RE_BUFF[%d]= %x\r   \r\n",i,RE_BUFF[0]);
	  BUFF[i]= RE_BUFF[0];								//��һλ��PA����״̬���ڶ�λ��PB����״̬
	}
}



/*-----------------------------------------------------------
	�������� com_port
	��  �룺 ��
	��  ���� ��
	˵  ���� ����PA0-7/PB2-9��״̬
	����ֵ�� ��
 ----------------------------------------------------------*/
void com_port(void)
{
	/*	PA0-7״̬����	*/
	HAL_GPIO_WritePin ( GPIOA,PA0_Pin,( BUFF[0] &0x80 ));
	HAL_GPIO_WritePin ( GPIOA,PA1_Pin,( BUFF[0] &0x40 ));
	HAL_GPIO_WritePin ( GPIOA,PA2_Pin,( BUFF[0] &0x20 ));
	HAL_GPIO_WritePin ( GPIOA,PA3_Pin,( BUFF[0] &0x10 ));
	HAL_GPIO_WritePin ( GPIOA,PA4_Pin,( BUFF[0] &0x08 ));
	HAL_GPIO_WritePin ( GPIOA,PA5_Pin,( BUFF[0] &0x04 ));
	HAL_GPIO_WritePin ( GPIOA,PA6_Pin,( BUFF[0] &0x02 ));
	HAL_GPIO_WritePin ( GPIOA,PA7_Pin,( BUFF[0] &0x01));
	
	/*	PB2-9״̬����	*/
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
	�������� Re_Port
	��  �룺 ��
	��  ���� ��
	˵  ���� ���ڲ鿴PA0-PA7��PB2-PB9��״̬
	����ֵ�� ��
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
	
	
	HAL_Delay(10); //���ڵ�������ʱ

}

/*------------------------------------------------------------
	�������� PA8_detec
	��  �룺 ��
	��  ���� ��
	˵  ���� ��⵱PA8��͵�ƽʱ���� PA15��ƽʱPA15���ֵ͵�ƽ
	����ֵ�� ��
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



