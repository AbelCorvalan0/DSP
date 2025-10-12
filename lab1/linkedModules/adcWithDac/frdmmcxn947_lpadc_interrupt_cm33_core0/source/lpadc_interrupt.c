/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2022, 2024-2025 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "board.h"
#include "app.h"
#include "fsl_lpadc.h"

#include "fsl_spc.h"

#include "fsl_port.h"
#include "fsl_dac.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool g_LpadcConversionCompletedFlag = false;
volatile uint32_t g_LpadcInterruptCounter    = 0U;
lpadc_conv_result_t g_LpadcResultConfigStruct;
#if (defined(DEMO_LPADC_USE_HIGH_RESOLUTION) && DEMO_LPADC_USE_HIGH_RESOLUTION)
const uint32_t g_LpadcFullRange   = 65536U;
const uint32_t g_LpadcResultShift = 0U;
#else
const uint32_t g_LpadcFullRange   = 4096U;
const uint32_t g_LpadcResultShift = 3U;
#endif /* DEMO_LPADC_USE_HIGH_RESOLUTION */


/* Build up buffer1 */
#define BUFFER_SIZE 8

// Define BUFFER1
// Buffer's data
static uint16_t buffer1[BUFFER_SIZE];
//static int ind=0;

/* DAC variables */
volatile uint16_t dacValue= 0;

/* Define test wave form for DAC */
#define SIZE_WAVE_FORM	  512
//uint16_t waveForm[SIZE_WAVE_FORM];
uint16_t indexWaveForm = 0;

// 512-sample sine wave for 12-bit DAC
uint16_t waveForm[512] = {
     2048,  2073,  2098,  2123,  2148,  2173,  2198,  2223,
     2248,  2273,  2298,  2323,  2348,  2373,  2398,  2422,
     2447,  2472,  2496,  2521,  2545,  2569,  2594,  2618,
     2642,  2666,  2690,  2714,  2737,  2761,  2784,  2808,
     2831,  2854,  2877,  2900,  2923,  2946,  2968,  2990,
     3013,  3035,  3057,  3078,  3100,  3122,  3143,  3164,
     3185,  3206,  3226,  3247,  3267,  3287,  3307,  3327,
     3346,  3366,  3385,  3404,  3423,  3441,  3459,  3477,
     3495,  3513,  3530,  3548,  3565,  3581,  3598,  3614,
     3630,  3646,  3662,  3677,  3692,  3707,  3722,  3736,
     3750,  3764,  3777,  3791,  3804,  3816,  3829,  3841,
     3853,  3865,  3876,  3888,  3898,  3909,  3919,  3929,
     3939,  3949,  3958,  3967,  3975,  3984,  3992,  3999,
     4007,  4014,  4021,  4027,  4034,  4040,  4045,  4051,
     4056,  4060,  4065,  4069,  4073,  4076,  4080,  4083,
     4085,  4087,  4089,  4091,  4093,  4094,  4094,  4095,
     4095,  4095,  4094,  4094,  4093,  4091,  4089,  4087,
     4085,  4083,  4080,  4076,  4073,  4069,  4065,  4060,
     4056,  4051,  4045,  4040,  4034,  4027,  4021,  4014,
     4007,  3999,  3992,  3984,  3975,  3967,  3958,  3949,
     3939,  3929,  3919,  3909,  3898,  3888,  3876,  3865,
     3853,  3841,  3829,  3816,  3804,  3791,  3777,  3764,
     3750,  3736,  3722,  3707,  3692,  3677,  3662,  3646,
     3630,  3614,  3598,  3581,  3565,  3548,  3530,  3513,
     3495,  3477,  3459,  3441,  3423,  3404,  3385,  3366,
     3346,  3327,  3307,  3287,  3267,  3247,  3226,  3206,
     3185,  3164,  3143,  3122,  3100,  3078,  3057,  3035,
     3013,  2990,  2968,  2946,  2923,  2900,  2877,  2854,
     2831,  2808,  2784,  2761,  2737,  2714,  2690,  2666,
     2642,  2618,  2594,  2569,  2545,  2521,  2496,  2472,
     2447,  2422,  2398,  2373,  2348,  2323,  2298,  2273,
     2248,  2223,  2198,  2173,  2148,  2123,  2098,  2073,
     2048,  2022,  1997,  1972,  1947,  1922,  1897,  1872,
     1847,  1822,  1797,  1772,  1747,  1722,  1697,  1673,
     1648,  1623,  1599,  1574,  1550,  1526,  1501,  1477,
     1453,  1429,  1405,  1381,  1358,  1334,  1311,  1287,
     1264,  1241,  1218,  1195,  1172,  1149,  1127,  1105,
     1082,  1060,  1038,  1017,   995,   973,   952,   931,
      910,   889,   869,   848,   828,   808,   788,   768,
      749,   729,   710,   691,   672,   654,   636,   618,
      600,   582,   565,   547,   530,   514,   497,   481,
      465,   449,   433,   418,   403,   388,   373,   359,
      345,   331,   318,   304,   291,   279,   266,   254,
      242,   230,   219,   207,   197,   186,   176,   166,
      156,   146,   137,   128,   120,   111,   103,    96,
       88,    81,    74,    68,    61,    55,    50,    44,
       39,    35,    30,    26,    22,    19,    15,    12,
       10,     8,     6,     4,     2,     1,     1,     0,
        0,     0,     1,     1,     2,     4,     6,     8,
       10,    12,    15,    19,    22,    26,    30,    35,
       39,    44,    50,    55,    61,    68,    74,    81,
       88,    96,   103,   111,   120,   128,   137,   146,
      156,   166,   176,   186,   197,   207,   219,   230,
      242,   254,   266,   279,   291,   304,   318,   331,
      345,   359,   373,   388,   403,   418,   433,   449,
      465,   481,   497,   514,   530,   547,   565,   582,
      600,   618,   636,   654,   672,   691,   710,   729,
      749,   768,   788,   808,   828,   848,   869,   889,
      910,   931,   952,   973,   995,  1017,  1038,  1060,
     1082,  1105,  1127,  1149,  1172,  1195,  1218,  1241,
     1264,  1287,  1311,  1334,  1358,  1381,  1405,  1429,
     1453,  1477,  1501,  1526,  1550,  1574,  1599,  1623,
     1648,  1673,  1697,  1722,  1747,  1772,  1797,  1822,
     1847,  1872,  1897,  1922,  1947,  1972,  1997,  2022
};

/* Clock configurations */
void configClocks      (void);

/* Pin configuration functions */
void configDacPin      (void);


/* Functional functions */
void configDac         (void);

/* Sample processing functions */
void showBuffer        (void);
void conv_12_q15       (void);

/* Test wave form functions */
void genWave           (void);


/* Test functions */
void delay  (uint32_t times);
void showSamplesIntoDAC(void);
/*******************************************************************************
 * Code
 ******************************************************************************/
void DEMO_LPADC_IRQ_HANDLER_FUNC(void)
{
    g_LpadcInterruptCounter++;
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
    if (LPADC_GetConvResult(DEMO_LPADC_BASE, &g_LpadcResultConfigStruct, 0U))
#else
    if (LPADC_GetConvResult(DEMO_LPADC_BASE, &g_LpadcResultConfigStruct))
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */
    {
        g_LpadcConversionCompletedFlag = true;
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    lpadc_config_t mLpadcConfigStruct;
    lpadc_conv_trigger_config_t mLpadcTriggerConfigStruct;
    lpadc_conv_command_config_t mLpadcCommandConfigStruct;

    BOARD_InitHardware();

    // Config Clocks.
    configClocks();

    PRINTF("LPADC Interrupt Example\r\n");

    LPADC_GetDefaultConfig(&mLpadcConfigStruct);
    mLpadcConfigStruct.enableAnalogPreliminary = true;

    /* Set to highest power level here, users need to properly match ADC clock and power level according 
     * to application requirements. For specific correspondence, please refer to the data sheet. */
#if defined(FSL_FEATURE_LPADC_HAS_CFG_PWRSEL) && (FSL_FEATURE_LPADC_HAS_CFG_PWRSEL == 1U)
    mLpadcConfigStruct.powerLevelMode = kLPADC_PowerLevelAlt4;
#endif /* FSL_FEATURE_LPADC_HAS_CFG_PWRSEL */
#if defined(DEMO_LPADC_VREF_SOURCE)
    mLpadcConfigStruct.referenceVoltageSource = DEMO_LPADC_VREF_SOURCE;
#endif /* DEMO_LPADC_VREF_SOURCE */
#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS
    mLpadcConfigStruct.conversionAverageMode = kLPADC_ConversionAverage128;
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS */
    LPADC_Init(DEMO_LPADC_BASE, &mLpadcConfigStruct);

    /* Request LPADC calibration. */
#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE) && FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE
    LPADC_SetOffsetCalibrationMode(DEMO_LPADC_BASE, DEMO_LPADC_OFFSET_CALIBRATION_MODE);
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE */

#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CALOFS) && FSL_FEATURE_LPADC_HAS_CTRL_CALOFS
#if defined(DEMO_LPADC_DO_OFFSET_CALIBRATION) && DEMO_LPADC_DO_OFFSET_CALIBRATION
    LPADC_DoOffsetCalibration(DEMO_LPADC_BASE); /* Request offset calibration, automatic update OFSTRIM register. */
#else                                           /* Update OFSTRIM register manually. */

#if defined(FSL_FEATURE_LPADC_HAS_OFSTRIM) && FSL_FEATURE_LPADC_HAS_OFSTRIM
#if defined(FSL_FEATURE_LPADC_OFSTRIM_COUNT) && (FSL_FEATURE_LPADC_OFSTRIM_COUNT == 2U)
    LPADC_SetOffsetValue(DEMO_LPADC_BASE, DEMO_LPADC_OFFSET_VALUE_A, DEMO_LPADC_OFFSET_VALUE_B);
#elif defined(FSL_FEATURE_LPADC_OFSTRIM_COUNT) && (FSL_FEATURE_LPADC_OFSTRIM_COUNT == 1U)
    LPADC_SetOffsetValue(DEMO_LPADC_BASE, DEMO_LPADC_OFFSET_VALUE);
#endif /* FSL_FEATURE_LPADC_OFSTRIM_COUNT */

#else  /* For other OFSTRIM register type. */
    if (DEMO_LPADC_OFFSET_CALIBRATION_MODE == kLPADC_OffsetCalibration12bitMode)
    {
        LPADC_SetOffset12BitValue(DEMO_LPADC_BASE, DEMO_LPADC_OFFSET_VALUE_A, DEMO_LPADC_OFFSET_VALUE_B);
    }
    else
    {
        LPADC_SetOffset16BitValue(DEMO_LPADC_BASE, DEMO_LPADC_OFFSET_VALUE_A, DEMO_LPADC_OFFSET_VALUE_B);
    }
#endif /* FSL_FEATURE_LPADC_HAS_OFSTRIM */

#endif /* DEMO_LPADC_DO_OFFSET_CALIBRATION */
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CALOFS */

#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ
    /* Request auto calibration (including gain error calibration and linearity error calibration). */
    LPADC_DoAutoCalibration(DEMO_LPADC_BASE);
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ */

#if (defined(FSL_FEATURE_LPADC_HAS_CFG_CALOFS) && FSL_FEATURE_LPADC_HAS_CFG_CALOFS)
    /* Do auto calibration. */
    LPADC_DoAutoCalibration(DEMO_LPADC_BASE);
#endif /* FSL_FEATURE_LPADC_HAS_CFG_CALOFS */

    /* Set conversion CMD configuration. */
    LPADC_GetDefaultConvCommandConfig(&mLpadcCommandConfigStruct);
    mLpadcCommandConfigStruct.channelNumber = DEMO_LPADC_USER_CHANNEL;
#if defined(DEMO_LPADC_USE_HIGH_RESOLUTION) && DEMO_LPADC_USE_HIGH_RESOLUTION
    mLpadcCommandConfigStruct.conversionResolutionMode = kLPADC_ConversionResolutionHigh;
#endif /* DEMO_LPADC_USE_HIGH_RESOLUTION */
    LPADC_SetConvCommandConfig(DEMO_LPADC_BASE, DEMO_LPADC_USER_CMDID, &mLpadcCommandConfigStruct);

    /* Set trigger configuration. */
    LPADC_GetDefaultConvTriggerConfig(&mLpadcTriggerConfigStruct);
    mLpadcTriggerConfigStruct.targetCommandId       = DEMO_LPADC_USER_CMDID;     /* CMD15 is executed. */
    mLpadcTriggerConfigStruct.enableHardwareTrigger = false;
    LPADC_SetConvTriggerConfig(DEMO_LPADC_BASE, 0U, &mLpadcTriggerConfigStruct); /* Configurate the trigger0. */

    /* Enable the watermark interrupt. */
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
    LPADC_EnableInterrupts(DEMO_LPADC_BASE, kLPADC_FIFO0WatermarkInterruptEnable);
#else
    LPADC_EnableInterrupts(DEMO_LPADC_BASE, kLPADC_FIFOWatermarkInterruptEnable);
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */
    EnableIRQ(DEMO_LPADC_IRQn);

    PRINTF("ADC Full Range: %d\r\n", g_LpadcFullRange);
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_CSCALE) && FSL_FEATURE_LPADC_HAS_CMDL_CSCALE
    if (kLPADC_SampleFullScale == mLpadcCommandConfigStruct.sampleScaleMode)
    {
        PRINTF("Full channel scale (Factor of 1).\r\n");
    }
    else if (kLPADC_SamplePartScale == mLpadcCommandConfigStruct.sampleScaleMode)
    {
        PRINTF("Divided input voltage signal. (Factor of 30/64).\r\n");
    }
#endif

    /* When the number of datawords stored in the ADC Result FIFO is greater
     * than watermark value(0U), LPADC watermark interrupt would be triggered.
     */
    //genWave();
    showBuffer();
    configDacPin();
    configDac();
    PRINTF("Please press any key to get user channel's ADC value.\r\n");
    while (1)
    {
    	showSamplesIntoDAC();
//        GETCHAR();
//        LPADC_DoSoftwareTrigger(DEMO_LPADC_BASE, 1U); /* 1U is trigger0 mask. */
//        while (!g_LpadcConversionCompletedFlag)
//        {
//        }
//
//        buffer1[ind]= (g_LpadcResultConfigStruct.convValue);
//        ind= (ind + 1)%BUFFER_SIZE;
//        PRINTF("ADC value: %d\r\nADC interrupt count: %d\r\n",
//               ((g_LpadcResultConfigStruct.convValue) >> g_LpadcResultShift), g_LpadcInterruptCounter);
//        g_LpadcConversionCompletedFlag = false;
//        showBuffer();
    }
}

void showBuffer(){
	for(int ind= 0; ind < BUFFER_SIZE; ind++){
		PRINTF("El valor en la posición %d es: %u\r\n", ind+1, buffer1[ind]);
	}
}

void configDacPin(){
    /* PORT4_2 (pin T1) is configured as DAC0_OUT */
    PORT_SetPinMux(PORT4, 2U, kPORT_MuxAlt0);

    PORT4->PCR[2] = ((PORT4->PCR[2] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_IBE_MASK)))

                     /* Input Buffer Enable: Disables. */
                     //| PORT_PCR_IBE(PCR_IBE_ibe0));
    				 | PORT_PCR_IBE(0x00u));
}

void configDac(){
    dac_config_t dacConfig;

    DAC_GetDefaultConfig(&dacConfig);
    dacConfig.referenceVoltageSource= kDAC_ReferenceVoltageSourceAlt1;
    DAC_Init(DAC0, &dacConfig);

	DAC_Enable(DAC0, true);
}

void configClocks(){
    /* Enables the clock for PORT4 (DAC P4.2): */
    CLOCK_EnableClock(kCLOCK_Port4);

    /* attach FRO HF to DAC0 */
    CLOCK_SetClkDiv(kCLOCK_DivDac0Clk, 1U);
    CLOCK_AttachClk(kFRO_HF_to_DAC0);

    /* enable DAC0 and VREF */
    SPC_EnableActiveModeAnalogModules(SPC0, (1UL << 0UL | 1UL << 4UL));

}

//void genWave(){
//	for(int i=0; i<SIZE_WAVE_FORM; i++)
//	{
//		waveForm[i] = i;
//	}
//	for(int ind= 0; ind < SIZE_WAVE_FORM; ind++){
//		PRINTF("El valor en la posición %d es: %u\r\n", ind+1, waveForm[ind]);
//	}
//}

void showSamplesIntoDAC(){

	static int indexWaveForm= 0;
	PRINTF("El valor en la posición %d es: %u\r\n", indexWaveForm, waveForm[indexWaveForm]);
    dacValue = waveForm[indexWaveForm]; //VEMOS EL VALOR ACTUAL DEL DAC
    //dacValue = 3000;
	DAC_SetData(DAC0, dacValue);
	delay(100);
	indexWaveForm = (indexWaveForm+1)% SIZE_WAVE_FORM;
}

void delay(uint32_t times){
	for(uint32_t i=0; i<times; i++)
		for(uint32_t j=0; j<times; j++);
}
