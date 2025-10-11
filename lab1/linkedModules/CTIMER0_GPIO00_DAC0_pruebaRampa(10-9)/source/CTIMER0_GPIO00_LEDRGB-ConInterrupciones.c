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
#include "fsl_lpadc.h"
#include "fsl_vref.h"
#include "fsl_inputmux.h"
#include "fsl_inputmux_connections.h"


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

uint16_t valueADC = 0; //PARA ALMACENAR LA LECTURA DEL ADC
uint16_t valueDAC = 0; //PARA VER SALIDA DE DAC EN DEBUUGER

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */

//void confTimer0(uint32_t valueT0);
void genWaveForm();
void confADC();
void confDAC();
void confGPIO();

int main(void)
{

	BOARD_InitHardware();//INICIALIZACION DE PINES Y HARDWARE EN GENERAL
    PRINTF("SE INCIALIZO EL HARDWARE : TIMER GPIOS Y DAC \r\n");

    genWaveForm(); //GENERAMOS LA FROMA DE ONDA
    PRINTF("FORMA DE ONDA GENERADA \r\n");

    confGPIO();
    confDAC();
    confADC();

    EnableIRQ(CTIMER0_IRQn);

    matchNewValue = CTIMER_CLK_FREQ; //INICIALIZACION CON FREC DE 1SEGUNDO
    //confTimer0(matchNewValue);


    uint32_t f_clk = CLOCK_GetCTimerClkFreq(0U); //PARA IMPRIMIR LA FREC DE LA FUENTE DE CLOCK DEL TIMER0
    PRINTF("CTIMER0 clock = %d Hz\r\n", f_clk);

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

/*
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
*/

void setNewMatch(uint32_t newMatch)
{

    // Limpiar cualquier flag pendiente
    CTIMER_ClearStatusFlags(CTIMER0, kCTIMER_Match3Flag);

    CTIMER0->TC = 0;  // reiniciar contador

    // Cambiar directamente el registro MR[3]
    CTIMER0->MR[3] = newMatch;
}

void confADC()
{
	//INPUTMUX->ADC0_TRIG = 0;

	INPUTMUX_Init(INPUTMUX); //PARA INCIAR LA CONEXION DE PERIFERICOS O PINES
	INPUTMUX_AttachSignal(INPUTMUX, 0, kINPUTMUX_Ctimer0M3ToAdc0Trigger); //CONECTA LA SALIDA DEL TIMER0 MATCH3 AL TRIGER0 DEL ADC0.0
	//INPUTMUX_Deinit(INPUTMUX); // FINALIZO CONEXION DE PERIFERICOS O PINES

    LPADC_EnableInterrupts(ADC0, kLPADC_Trigger0CompletionInterruptEnable);

	EnableIRQ(ADC0_IRQn); //HABILITO INT ADC0
}

void confDAC()
{

	DAC_Enable(DAC0, true); //HABILITO DAC0

}

void confGPIO()
{
    EnableIRQ(GPIO00_IRQn);   // HABILITA GPIO00 LA IRQ DE PIO0_6 (SW3)
}

void  CTIMER0_IRQHandler()
{
    //PRINTF("FLAG GPIO0_6 = %d \r\n", GPIO_PinGetInterruptFlag(GPIO0, 6));

	valueDAC = waveForm[index]; //VEMOS EL VALOR ACTUAL DEL DAC
	DAC_SetData(DAC0, waveForm[index]);
	index = (index+1)% SIZE_WAVE_FORM;		//INDICE CIRCULAR

	PRINTF("PASO POR MATCH3 T0: \r\n");

	LED_GREEN_TOGGLE();		//TOGGLEO DE UN LED VERDE DE INTERRUPCION POR EL CORE

	CTIMER_ClearStatusFlags(CTIMER0, kCTIMER_Match3Flag);//LIMPIO FLAG DE TIMER 0

}




void GPIO00_IRQHandler(void)  // SE MODIFICA LA FRECUENCIA DE TIMER0
{
	PRINTF("PASO POR INTER GPIO0: \r\n");

	SW3 = GPIO_PinGetInterruptFlag(GPIO0, 6); //FLAG DE INTERRUPCION SI PRESIONE PULSADOR SW3 FLANCO DE SUBIDA
	SW2 = GPIO_PinGetInterruptFlag(GPIO0, 23); //FLAG DE INTERRUPCION SI PRESIONE PULSADOR SW2 FLANCO DE BAJADA

	  if(SW3)	//SI SW3 INTERRUMPIO
	  {
		 matchNewValue = matchNewValue/2; //DISMINUIMOS EL TIEMPO EN LA MITAD
		 //confTimer0(matchNewValue);		//CARGAMOS EL NUEVO MATCH A TIMER0
		 setNewMatch(matchNewValue);

	  }
	  if(SW2)
	  {
		  matchNewValue = matchNewValue*2; //AUMENTAMOS EL TIEMPO AL DOBLE
		  //confTimer0(matchNewValue);		//CARGAMOS EL NUEVO MATCH A TIMER0
		  setNewMatch(matchNewValue);
	  }

	//LED_RED1_INIT(LOGIC_LED_OFF); //PARA QUE LED_GREEN Y LED_RED TOGGLEN DE FORMA OPUESTA
	//LED_GREEN_ON();//

	GPIO_PinClearInterruptFlag(GPIO0, 6); //LIMPIO FLAG DE SW3 (GPIO0 PIN 6)
	GPIO_PinClearInterruptFlag(GPIO0, 23); //LIMPIO FLAG DE SW2 (GPIO0 PIN 23)


}


/* ADC0_IRQn interrupt handler */
void ADC0_IRQHandler(void) {

  PRINTF("PASO POR INTER ADC0: \r\n");
  uint32_t trigger_status_flag;
  uint32_t status_flag;
  /* Trigger interrupt flags */
  trigger_status_flag = LPADC_GetTriggerStatusFlags(ADC0);
  /* Interrupt flags */
  status_flag = LPADC_GetStatusFlags(ADC0);
  /* Clears trigger interrupt flags */
  LPADC_ClearTriggerStatusFlags(ADC0, trigger_status_flag);
  /* Clears interrupt flags */
  LPADC_ClearStatusFlags(ADC0, status_flag);

  /* Place your code here */

  lpadc_conv_result_t result;

          LPADC_GetConvResult(ADC0, &result, 0);
          valueADC = result.convValue;
          PRINTF("ADC value: %u\r\n", (unsigned int)valueADC);
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
 *
 * 					*AL USAR ADC, SI QUERES QUE DISPARE POR TIMER HAY QUE USAR LOS
 * 					 TIGGER 0 Y ESE TIGGER0 HAY QUE CONECTARLO CON LA SALIDA DEL
 * 					 MATCH 3 DE TIMER 0 , LO PRIMERO POR CFGTOOL LO SEGUNDO POR
 * 					 INPUTMUX PARA INTERCONECTAR AMBOS PERIFERICOS.
 * 					 ESTO SOLO HACE QUE INICIE LA CONVERSION DEL ADC, SI QUERES
 * 					 ACTUALIZAR SU VALOR CUANDO ACABE LA CONVERSION DEBE HABILITAR
 * 					 LA INTERRRUPCION Y ADEMAS ASEGURATE QUE EL FIFO0 WATERMARK ESTE
 * 					 HABILITADO O MARCADO, DE MODO QUE AL LLENARSE ESTE MANDE UNA
 * 					 INTERRUPCION AL HANDLER DE ADC, AHI LEEREMOS EL VALOR Y LO USAREMOS
 *
 */
