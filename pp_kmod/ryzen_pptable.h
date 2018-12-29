/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (C) 2018 Jiaxun Yang <jiaxun.yang@flygoat.com> */
/* Ryzen NB SMU Powerplay Table */

#ifndef RYZEN_PPTABLE_H
#define RYZEN_PPTABLE_H
#include <linux/kernel.h>

#define TABLE_PPTABLE 0

#define BIOS_INTERFACE_VER 0x5

typedef struct {
  u32 Version;

  /* PCD infrastructure limits */
  u32 SUSTAINED_POWER_LIMIT;           //Power [mWatts] (STAPM)
  u32 FAST_PPT_LIMIT;                  //Power [mWatts] (fPPT)
  u32 SLOW_PPT_LIMIT;                  //Power [mWatts] (sPPT)
  u32 SLOW_PPT_TIME_CONSTANT;          //Time constant (seconds)
  u8  SYSTEM_TEMPERATURE_TRACKING;     //Tskin feedback from EC; 1 = enabled; 0 = disabled
  u8  STAPM_BOOST_OVERRIDE;            //1 = use value in STAPM_BOOST; 0 = use SMU FW default
  u8  STAPM_BOOST;                     //1 = enabled; 0 = disabled
  u8  AA_MODE_EN;                      //A+A power/thermal sharing algorithm; 1 = enable; 0 = disable
  u32 STAPM_TIME_CONSTANT;             //Time constant (seconds)
  u32 THERMCTL_LIMIT;                  //Tctrl (THM)
  u32 VRM_CURRENT_LIMIT;               //Current [mA] (VDDCR_VDD TDC)
  u32 VRM_MAXIMUM_CURRENT_LIMIT;       //Current [mA] (VDDCR_VDD EDC)
  u32 VRM_SOC_CURRENT_LIMIT;           //Current [mA] (VDDCR_SOC TDC)
  u32 VRM_SOC_MAXIMUM_CURRENT_LIMIT;   //Current [mA] (VDDCR_SOC EDC)
  u32 PSI0_CURRENT_LIMIT;              //Current [mA] (VDDCR_VDD PSI0)
  u32 PSI0_SOC_CURRENT_LIMIT;          //Current [mA] (VDDCR_SOC PSI0)
  u32 PROCHOT_L_DEASSERTION_RAMP_TIME; //Time [ms] (PROCHOT)
  u8  systemconfig;                   //0 = use fused default; >0 = user specified value
  u8  spare[3];

  /* PCD/CBS fan table */
  u8 FanTable_Override;     //[1 means use the full set of data specified below; 0 means use default fan table]
  u8 FanTable_Hysteresis;
  u8 FanTable_TempLow;
  u8 FanTable_TempMed;
  u8 FanTable_TempHigh;
  u8 FanTable_TempCritical;
  u8 FanTable_PwmLow;
  u8 FanTable_PwmMed;
  u8 FanTable_PwmHigh;
  u8 FanTable_PwmFreq;      //[0 = 25kHz; 1 = 100Hz]
  u8 FanTable_Polarity;     //[0 = negative; 1 = positive]
  u8 FanTable_spare;

  /* CBS debug options */
  u8  CoreDldoPsmMargin;       //[PSM count 1 ~ 1.8mV]
  u8  GfxDldoPsmMargin;        //[PSM count 1 ~ 1.8mV]
  u8  ForceFanPwmEn;           //[1 means use the ForceFanPwm value below]
  u8  ForceFanPwm;             //[% 0-100]
  u8  CoreStretchThreshEn;     //[1 means use the CoreStretchThresh value below]
  u8  CoreStretchThresh;       //[1 = 2.5%]
  u8  L3StretchThreshEn;       //[1 means use the L3StretchThresh value below]
  u8  L3StretchThresh;         //[1 = 2.5%]
  u8  GfxStretchThreshEn;      //[1 means use the GfxStretchThresh value below]
  u8  GfxStretchThresh;        //[1 = 2.5%]
  u8  GfxStretchAmountEn;
  u8  GfxStretchAmount;
  u8  CoreDldoBypass;          //[1 means bypass]
  u8  GfxDldoBypass;           //[1 means bypass]
  u8  XiSeparationEn;          //[1 means use the XiSeparation value below]
  u8  XiSeparationHigh;        //[0 = async mode; 3 = 2 cycle; 4 = 2.5 cycle; 5 = 3 cycle; 6 = 3.5 cycle; 7 = 4 cycle]
  u8  XiSeparationLow;         //[0 = async mode; 3 = 2 cycle; 4 = 2.5 cycle; 5 = 3 cycle; 6 = 3.5 cycle; 7 = 4 cycle]
  u8  AvfsCoeffTable_Override; //[1 = override; 0 = use defaults]
  u8  spare35[2];
  s32  VddcrVddVoltageMargin;   //[mV]
  s32  VddcrSocVoltageMargin;   //[mV]
  u16 FcwSlewFrac_L3FidTotalSteps;
  u8  FcwSlewFrac_L3FidTotalStepsEn;
  u8  WaitVidCompDis;          //[0 = use VOTF feedback from VR; 1 = use internal timer]
  u8  UseCcxFreqCurveFuses;
  u8  UseGfxFreqCurveFuses;
  u8  UseCacSiddFuses;
  u8  spare2;

  /* CBS debug options [AVFS coeffients - signed 2's complement with 24 fractional bits] */
  s32 CorePsfFreq2;
  s32 CorePsfFreq;
  s32 CorePsfGfxActive;
  s32 CorePsfTemp;
  s32 CorePsfSidd;
  s32 CorePsfCac;
  s32 CorePsfNumActiveCores;
  s32 CorePsfSigma;
  s32 CorePsfAcBtc;
  s32 L3PsfFreq2;
  s32 L3PsfFreq;
  s32 L3PsfGfxActive;
  s32 L3PsfTemp;
  s32 L3PsfSidd;
  s32 L3PsfCac;
  s32 L3PsfNumActiveCores;
  s32 L3PsfSigma;
  s32 L3PsfAcBtc;
  s32 GfxPsfFreq2;
  s32 GfxPsfFreq;
  s32 GfxPsfGfxActive;
  s32 GfxPsfTemp;
  s32 GfxPsfSidd;
  s32 GfxPsfCac;
  s32 GfxPsfNumActiveCores;
  s32 GfxPsfSigma;
  s32 GfxPsfAcBtc;

  /* PCD/CBS Telemetry setup */
  u32 Telemetry_VddcrVddSlope;
  s32 Telemetry_VddcrVddOffset;
  u32 Telemetry_VddcrSocSlope;
  s32 Telemetry_VddcrSocOffset;

  /* LIVmin Entry voltage */
  u8  LivMinEntryVID;
  u8  spare3[3];

} pptable_t;

#endif