/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "fsl_debug_console.h"
#include "board.h"
#include "app.h"
#include "fsl_ctimer.h"
#include "fsl_dac.h" //HACER UPDATE CODE DESDE EL CONGITOOL O AGREGAR LIBRERIA EN PROJECT Y MANAGMENT SDK



/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SIZE_WAVE_FORM 4095 //MAXIMA SALIDA PARA 12 BITS 2^12 -1
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint32_t contador=0;
uint32_t matchNewValue; //PARA ACTUALIZAR EL DESBORDAMIENTO DEL TIMER0
uint8_t SW3;
uint8_t SW2;

uint16_t waveForm[SIZE_WAVE_FORM];
uint16_t index = 0; //INDICE DE CADA DATO DE LA ONDA

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */

void confTimer0(uint32_t valueT0);
void genWaveForm();

int main(void)
{

    BOARD_InitHardware();//INICIALIZACION DE PINES Y HARDWARE EN GENERAL
    PRINTF("SE INCIALIZO EL HARDWARE : TIMER GPIOS Y DAC \r\n");

    genWaveForm(); //GENERAMOS LA FROMA DE ONDA
    PRINTF("FORMA DE ONDA GENERADA \r\n");

    matchNewValue = CTIMER_CLK_FREQ; //INICIALIZACION CON FREC DE 1SEGUNDO

    confTimer0(matchNewValue);
    DAC_Enable(DAC0, true); //HABILITO DAC0
    EnableIRQ(GPIO00_IRQn);   // HABILITA GPIO00 LA IRQ DE PIO0_6 (SW3)

    uint32_t f_clk = CLOCK_GetCTimerClkFreq(0U);
    PRINTF("CTIMER0 clock = %d Hz\r\n", f_clk);
    PRINTF("FLAG GPIO0_6 = %d \r\n", GPIO_PinGetInterruptFlag(GPIO0, 6));

    while (1)
    {

    }
    return 0;
}

void genWaveForm()
{
	for(uint16_t i=0; i<SIZE_WAVE_FORM; i++)
	{
		waveForm[i] = i;
	}
}


void confTimer0(uint32_t valueT0)		//CONFIGURAMOS EL TIMER0, POR DEFECTO INICIA EL MATCH EN 1SEGUNDO, valueT0 ES PARA CAMBIAR SU TIEMPO DE MATCH
 {
	  	ctimer_config_t config; //PARA OBTENER LAS CONFIGURACIONES POR DEFECTODE TIMER0 (LAS QUE HCIMOS EN EL CONFIGTOOL)->PRESCALER, DIVISOR ETC..
	  	ctimer_match_config_t matchConfig; //PARA TERMIANR DE CONFIGURAR EL MATCH, TOGGLEO Y DEMAS.
	  	CTIMER_GetDefaultConfig(&config);	//DEVUELVE VALORE POR DEFECTO DEL TIMER0 CARAGDO EN CONFIFTOOL

	    CTIMER_Init(CTIMER, &config);	//INCIALIZA EL TIMER CON LOS VALORES QUE CARGAMOS AL CONFIG TOOL, LUEGO ACABAMOS NOSOTROS.

	    matchConfig.enableCounterReset = true;
	    matchConfig.enableCounterStop  = false;
	    matchConfig.matchValue         = valueT0 ;	//TIEMPO DE MATCH
	    matchConfig.outControl         = kCTIMER_Output_Toggle;	//SALIDA TOGGLEADA CADA VEZ QUE LLEGA AL MATCH
	    matchConfig.outPinInitState    = true;
	    matchConfig.enableInterrupt    = true;	//HABILITO INTERRUPCION TIMER0
	    CTIMER_SetupMatch(CTIMER, CTIMER_MAT_OUT, &matchConfig);	//CARGAMOS LA CONFIGURACION DE LOS MIEMBROS QUE CARGAMOS HASTA AHORA
	    CTIMER_StartTimer(CTIMER); //REINCIA LA CUENTA PARA QUE COMIENCE DESDE EL INICIO
 }


void  CTIMER0_IRQHandler()
{
    //PRINTF("FLAG GPIO0_6 = %d \r\n", GPIO_PinGetInterruptFlag(GPIO0, 6));

	DAC_SetData(DAC0, waveForm[index]);
	index = (index+1)% SIZE_WAVE_FORM;		//INDICE CIRCULAR

	LED_GREEN_TOGGLE();		//TOGGLEO DE UN LED VERDE DE INTERRUPCION POR EL CORE
	CTIMER_ClearStatusFlags(CTIMER0, kCTIMER_Match0Flag);//LIMPIO FLAG DE TIMER 0
}




void GPIO00_IRQHandler(void)  // SE MODIFICA LA FRECUENCIA DE TIMER0
{
	PRINTF("PASO POR INTER GPIO0 \r\n");

	SW3 = GPIO_PinGetInterruptFlag(GPIO0, 6); //FLAG DE INTERRUPCION SI PRESIONE PULSADOR SW3 FLANCO DE SUBIDA
	SW2 = GPIO_PinGetInterruptFlag(GPIO0, 23); //FLAG DE INTERRUPCION SI PRESIONE PULSADOR SW2 FLANCO DE BAJADA

	  if(SW3)	//SI SW3 INTERRUMPIO
	  {
		 matchNewValue = matchNewValue/2; //DISMINUIMOS EL TIEMPO EN LA MITAD
		 confTimer0(matchNewValue);		//CARGAMOS EL NUEVO MATCH A TIMER0
		 CTIMER_StartTimer(CTIMER);		//REINCIAMOS LA CUENTA

	  }
	  if(SW2)
	  {
		  matchNewValue = matchNewValue*2; //AUMENTAMOS EL TIEMPO AL DOBLE
		  confTimer0(matchNewValue);		//CARGAMOS EL NUEVO MATCH A TIMER0
		  CTIMER_StartTimer(CTIMER);		//REINCIAMOS LA CUENTA
	  }

	LED_RED1_INIT(LOGIC_LED_OFF); //PARA QUE LED_GREEN Y LED_RED TOGGLEN DE FORMA OPUESTA
	LED_GREEN_ON();//

	GPIO_PinClearInterruptFlag(GPIO0, 6); //LIMPIO FLAG DE SW3 (GPIO0 PIN 6)
	GPIO_PinClearInterruptFlag(GPIO0, 23); //LIMPIO FLAG DE SW2 (GPIO0 PIN 23)


}


/*
 * RESUMEN:
 * 			*CONGIGURAR EN CONFIG TOOL TIMER0 (EN PERIFERICOS Y CLOCKS)
 * 			*CONFIGURAR LOS PINES ->SW2 Y SW3
 * 			*CONFIGURAR TIMER0 CON VALORES DE MATCH EN EL MAIN , NO OLVIDAR DE PRECARGAR LOS VALORES DE CONFIG TOOL CON:
 * 						ctimer_config_t config; //PARA OBTENER LAS CONFIGURACIONES POR DEFECTODE TIMER0 (LAS QUE HCIMOS EN EL CONFIGTOOL)->PRESCALER, DIVISOR ETC..
	  					ctimer_match_config_t matchConfig; //PARA TERMIANR DE CONFIGURAR EL MATCH, TOGGLEO Y DEMAS.
	  				    CTIMER_Init(CTIMER, &config);	//INCIALIZA EL TIMER CON LOS VALORES QUE CARGAMOS AL CONFIG TOOL, LUEGO ACABAMOS NOSOTROS.
	  		*HABILITAR LA INTERRUPCION PARA GPIO (NOTAR QUE HAY CANALES DE GPIO)
	  		    		EnableIRQ(GPIO00_IRQn);   // HABILITA GPIO00 LA IRQ DE PIO0_6 (SW3)


 */

/*
 * NOTAS IMPORTANTES:
 * 					*AL USAR CONFITOOLS SIEMPRE VERIFICAR  QUE EN HardwareInit()
 * 					 ESTE LLAMADA LA FUNCION BOARD_InitBootPeripherals(); YA QUE
 * 					 ESTA ES LA QUE INCIIALIZA LOS PERIFERICOS CON LOS PARAMTEROS
 * 					 CARGADOS EN EL CONFIGTOOL, SI DA UN ERROR, NO HAY QUE OLVIDAR
 * 					 DE INCLUIR EL "#include "peripherals.h"" QUE HACE REFERNCIA A
 * 					 AL ARCHIVO DONDE SE CARGARON ESTOS PARAMTEROS.
 */
