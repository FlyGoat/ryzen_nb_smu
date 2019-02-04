// SPDX-License-Identifier: GPL-2.0
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com> */
/* Ryzen NB SMU Service Request Tool */

#include <string.h>
#include "nb_smu_ops.h"
#include "argparse.h"


static const char *const usage[] = {
    "smu-tool [options] [[--] args]",
    "smu-tool [options]",
    NULL,
};

int main(int argc, const char **argv)
{
    struct pci_access *pacc;
    nb_t nb;
    uint32_t message = 0, iarg0 = 0, iarg1 = 0;
    uint32_t iarg2 = 0, iarg3 = 0, iarg4 = 0, iarg5 = 0;
    smu_service_args_t *args;
    int err = 0;

    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Arguments"),
        OPT_U32('n', "message", &message, "The reqeust message"),        
        OPT_U32('a', "arg0", &iarg0, "The first argument"),
        OPT_U32('b', "arg1", &iarg1, "The second argument"),
        OPT_U32('c', "arg2", &iarg1, "The third argument"),
        OPT_U32('d', "arg3", &iarg1, "The forth argument"),
        OPT_U32('e', "arg4", &iarg1, "The fifth argument"),
        OPT_U32('f', "arg5", &iarg1, "The sixth argument"),
        OPT_END(),
    };


    struct argparse argparse;
    argparse_init(&argparse, options, usage, 0);
    argparse_describe(&argparse, "\n Ryzen NB SMU Service Request tool.", "\nWARNING: Use at your own risk!\nBy Jiaxun Yang <jiaxun.yang@flygoat.com>, Under GPL-2.0.");
    argc = argparse_parse(&argparse, argc, argv);

    pacc = pci_alloc();
    pci_init(pacc);
    nb = pci_get_dev(pacc, 0, 0, 0, 0);
    pci_fill_info(nb, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);

    if (nb->device_id != NB_DEVICE_ID){
        printf("Not a Ryzen NB Device\n");
        err = -1;
    }
    args = malloc(sizeof(*args));
    memset(args, 0, sizeof(*args));

    args->arg0 = iarg0;
    args->arg1 = iarg1;
    args->arg2 = iarg2;
    args->arg3 = iarg3;
    args->arg4 = iarg4;
    args->arg5 = iarg5;

    switch(smu_service_req(nb, message, args)){
        case REP_MSG_OK:
            printf("Service Request OK\n");
            break;
        case REP_MSG_CmdRejectedBusy:
            printf("Command Rejected - Busy\n");
            err = -1;
            break;
        case REP_MSG_CmdRejectedPrereq:
            printf("Command Rejected - Have Pre Req\n");
            err = -1;
            break;
        case REP_MSG_Failed:
            printf("Faild to compelet service request\n");
            err = -1;
            break;
        case REP_MSG_UnknownCmd:
            printf("Unknown message\n");
            err = -1;
            break;
        default:
            printf("Unknown Error\n");
            err = -1;
    }

if(!err){
    printf("Result arg0: 0x%x, arg1:0x%x, arg2:0x%x, arg3:0x%x, arg4: 0x%x, arg5: 0x%x\n",  \
        args->arg0, args->arg1, args->arg2, args->arg3, args->arg4, args->arg5);
}

    free(args);
    pci_cleanup(pacc);
}