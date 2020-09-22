/*�������� � DAC*/

/* Includes ------------------------------------------------------------------*/
	#include "initialisation.h"
	
	#define k 		4.983 			//�����. �������� �������  V-A	
	
uint8_t sin[16] = {127, 176, 218, 245, 255, 245, 218, 176, 127, 79, 37, 10, 0,10, 37, 79};
	uint8_t i=0,flag_LED=0;
	uint16_t	RMS=0,U_dac=0;;


main (void)
{
	GPIO_init ();
	DAC_init ();
	ADC_init ();
	TIM6_init();
	IWDG_init();
	//InitRCC_HSI ();	
		

	while (1)
	{
		//GPIO_SetBits (GPIOB,GPIO_Pin_12);  //����� �����
		
		RMS = ADC_RMS ();	//RMS
		
		/*���� RMS > 55mV �� ������ ��� ����*/
		if (RMS > 55 )
		{
		/*������� ���������� DAC*/
		/*�������� �� �������� ���� � ������� �����,mA*/
		/*Udac = Ima * R�*/
		/*Ima = Iin*3.2 + 4*/
		/*Iin = RMS * k*/

		U_dac = ((RMS*k/1000)*3.2+4)*150;		//�������� DAC mV
		}
		
		/*���� RMS < 50mV �� �������, ��� ���� ��� � ������ � ����� 4mA*/
		else
		{
			U_dac = 600;
		}

		
		DAC_go (U_dac);
	
	/* ������������ IWDG*/
  IWDG_ReloadCounter();
		
		//GPIO_ResetBits (GPIOB,GPIO_Pin_12);	//����� �����


	}

}

	
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name										   
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
 
  /* Infinite loop */
  while (1)
  {
  }
}
#endif
