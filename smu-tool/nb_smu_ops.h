/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com> */
/* Ryzen NB SMU Service Request Opreations */

#ifndef NB_SMU_OPS_H
#define NB_SMU_OPS_H

#include <pci/pci.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct pci_dev *nb_t;

#define DBG(...)

#define NB_DEVICE_ID 0x15d0

#define NB_PCI_REG_ADDR_ADDR 0xB8
#define NB_PCI_REG_DATA_ADDR 0xBC

#define MP1_C2PMSG_MESSAGE_ADDR          0x3B10528
#define MP1_C2PMSG_RESPONSE_ADDR         0x3B10564
#define MP1_C2PMSG_ARG_BASE              0x3B10998
#define MP1_C2PMSG_ARGx_ADDR(x)          (MP1_C2PMSG_ARG_BASE + 4 * x)


#define REP_MSG_OK                    0x1
#define REP_MSG_Failed                0xFF
#define REP_MSG_UnknownCmd            0xFE
#define REP_MSG_CmdRejectedPrereq     0xFD
#define REP_MSG_CmdRejectedBusy       0xFC

typedef struct {
    u32 arg0;
    u32 arg1;
    u32 arg2;
    u32 arg3;
    u32 arg4;
    u32 arg5;
} smu_service_args_t;

u32 smu_service_req(struct pci_dev *nb ,u32 id ,smu_service_args_t *args);


#endif