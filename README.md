# ryzen_nb_smu
A fight against Ryzen NorthBridge SMU

Further usage and other information is still under research.

PR and discussions are welcomed.

# Background
Some how, I deterimined the method of commiunication between processor and SMU on northbridge of Ryzen processor, so it would be possible to change some power and frequency related settings in OS. Especially for Mobile Raven Ridge platform.

# Utils
## kmod_pp
Kernel Module to dump and modify pptable.

(Not working, under research)

TODO: Determine why we can't dump pptable
## smu_test.c
A userspace tool to make smu service request

# Communication Protcol
The registers, RAM and ROM of SMU is wrapped by a couple of register in NorthBridge PCI Config Space.

To communicate with SMU, the procossor need send a service request to SMU by write values to SMU registers.

There are 8 32-bit registers related with service register, MSG, 6×ARG and REP.

MSG is the ID of service request, 6*ARGS are arguments, REP is respond of service request.

## Progress of a service request
- Clear the REP register
- Write the ARGs
- Write the MSG
- Poll the REP until it changed, means the request is proceeded
- Read back ARGs
- Check the REP if the request proceeded sucessfuly

## A table of request ID
| Name | ID | Note |
| :------| :------ | :------ |
| TestMessage | 0x1 |  |
| GetSmuVersion | 0x2 |  |
| GetBiosIfVersion | 0x3 |  |
| GetNameString | 0x4 |  |
| EnableSmuFeatures | 0x5 |  |
| DisableSmuFeatures | 0x6 |  |
| DramLogSetDramAddrHigh | 0x7 |  |
| DramLogSetDramAddrLow | 0x8 |  |
| DramLogSetDramSize | 0x9 |  |
| DxioTestMessage | 0xA |  |
| ReadCoreCacWeightRegister | 0xB |  |
| SleepEntry | 0xC |  |
| SetGbeStatus | 0xD |  |
| PowerUpGfx | 0xE |  |
| PowerUpSata | 0xF |  |
| PowerDownSata | 0x10 |  |
| DisableSataController | 0x11 |  |
| SetBiosDramAddrHigh | 0x12 |  |
| SetBiosDramAddrLow | 0x13 |  |
| SetToolsDramAddrHigh | 0x14 |  |
| SetToolsDramAddrLow | 0x15 |  |
| TransferTableSmu2Dram | 0x16 |  |
| TransferTableDram2Smu | 0x17 |  |
| PowerSourceAC | 0x18 |  |
| PowerSourceDC | 0x19 |  |
| SetSustainedPowerLimit | 0x1A |  |
| SetFastPPTLimit | 0x1B |  |
| SetSlowPPTLimit | 0x1C |  |
| SetSlowPPTTimeConstant | 0x1D |  |
| SetStapmTimeConstant | 0x1E |  |
| SetTctlMax | 0x1F |  |
| SetVrmCurrentLimit | 0x20 |  |
| SetVrmSocCurrentLimit | 0x21 |  |
| SetVrmMaximumCurrentLimit | 0x22 |  |
| SetVrmSocMaximumCurrentLimit | 0x23 |  |
| SetPSI0CurrentLimit | 0x24 |  |
| SetPSI0SocCurrentLimit | 0x25 |  |
| SetProchotDeassertionRampTime | 0x26 |  |
| UpdateSkinTempError | 0x27 |  |
| SetGpuApertureLow | 0x28 |  |
| SetGpuApertureHigh | 0x29 |  |
| StartGpuLink | 0x2A |  |
| StopGpuLink | 0x2B |  |
| UsbD3Entry | 0x2C |  |
| UsbD3Exit | 0x2D |  |
| UsbInit | 0x2E |  |
| AcBtcStartCal | 0x2F |  |
| AcBtcStopCal | 0x30 |  |
| AcBtcEndCal | 0x31 |  |
| DcBtc | 0x32 |  |
| BtcRestoreOnS3Resume | 0x33 |  |
| SetGpuDeviceId | 0x34 |  |
| SetUlvVidOffset | 0x35 |  |
| DisablePSI | 0x36 |  |
| EnablePostCode | 0x37 |  |
| UsbConfigUpdate | 0x38 |  |
| SetupUSB31ControllerTrap | 0x39 |  |
| SetVddOffVid | 0x3A |  |
| SetVminFrequency | 0x3B |  |
| SetFrequencyMax | 0x3C |  |
| SetGfxclkOverdriveByFreqVid | 0x3D |  |
| PowerGateXgbe | 0x3E |  |
| OC_Disable | 0x3F |  |
| OC_VoltageMax | 0x40 |  |
| OC_FrequencyMax | 0x41 |  |
| EnableCC6Filter | 0x42 |  |
| GetSustainedPowerAndThmLimit | 0x43 |  |
| SetSoftMaxCCLK | 0x44 |  |
| SetSoftMinCCLK | 0x45 |  |
| SetSoftMaxGfxClk | 0x46 |  |
| SetSoftMinGfxClk | 0x47 |  |
| SetSoftMaxSocclkByFreq | 0x48 |  |
| SetSoftMinSocclkByFreq | 0x49 |  |
| SetSoftMaxFclkByFreq | 0x4A |  |
| SetSoftMinFclkByFreq | 0x4B |  |
| SetSoftMaxVcn | 0x4C |  |
| SetSoftMinVcn | 0x4D |  |
| SetSoftMaxLclk | 0x4E |  |
| SetSoftMinLclk | 0x4F |  |
| Message_Count | 0x50 |  |

# A table of REP code
| Name | ID |
| :------| :------ |
| OK | 0x1 |
| Failed | 0xFF |
| UnknownCmd | 0xFE |
| CmdRejectedPrereq | 0xFD |
| CmdRejectedBusy | 0xFC |

# PPtable
PowerPlay Table

A table to storage power management information

See AMDGPU Powerplay for more information

# Firmware
Grab from BIOS, reverse engineering in progesss.(Help wanted)

# Credit
- [zamaudio/smutool](https://github.com/zamaudio/smutool)
- Linux Kernel - amdgpu
- Internet
- My ThinkPad E485 with R7-2700U