/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (C) 2018 Jiaxun Yang <jiaxun.yang@flygoat.com> */
/* Ryzen NB SMU Powerplay Driver */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include "nb_smu_ops.h"
#include "ryzen_pptable.h"
#include <linux/errno.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <linux/types.h>

#define DEV_NAME "ryzen_nb_smu"
#define NB_DEVICE_ID 0x15d0
#define AMD_VENDOR_ID 0x1022

smu_service_args_t args = {0, 0, 0, 0, 0, 0};

static DEFINE_SPINLOCK(smu_lock);

static struct pci_device_id id_table[] = {
	{ PCI_DEVICE(AMD_VENDOR_ID, NB_DEVICE_ID), },
	{ 0, }
};
MODULE_DEVICE_TABLE(pci, id_table);
static struct pci_dev *nb;
pptable_t *pptable;

phys_addr_t pptable_phy_addr;

static void clear_args(smu_service_args_t *args){
	args->arg0 = 0;
	args->arg1 = 0;
	args->arg2 = 0;
	args->arg3 = 0;
	args->arg4 = 0;
	args->arg5 = 0;
}


static int pp_pci_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
    u32 smu_biosif_ver;

	pr_warn("ryzen_nb_pp: Probe\n");
	nb = dev;
	if (pci_enable_device(dev) < 0) {
		return -ENODEV;
	}

    spin_lock(&smu_lock);
    smu_service_req(nb, MSG_GetBiosIfVersion, &args);
    smu_biosif_ver = args.arg0;
    spin_unlock(&smu_lock);

    pr_warn("SMU BIOS Interface Ver: 0x%x\n", smu_biosif_ver);
    if(smu_biosif_ver != BIOS_INTERFACE_VER){
        pr_warn("SMU BIOS Interface Ver not match\n");
        return -ENODEV;
    }
	clear_args(&args);

	pptable = (pptable_t*)kzalloc(sizeof(pptable_t), __GFP_DMA);
	pptable_phy_addr = virt_to_phys((void*)pptable);

	DBG("pptable_phy_addr: 0x%llx",pptable_phy_addr);

	/* Set pptable phys addr in smu */
	spin_lock(&smu_lock);
	args.arg0 = lower_32_bits(pptable_phy_addr);
	smu_service_req(nb, MSG_SetPPTABLEADDRLow, &args);
	clear_args(&args);
	args.arg0 = upper_32_bits(pptable_phy_addr);
	smu_service_req(nb, MSG_SetPPTABLEAddrHigh, &args);
	clear_args(&args);
	spin_unlock(&smu_lock);

	/* Dump pptable to memory */
	spin_lock(&smu_lock);
	args.arg0 = TABLE_PPTABLE;
	smu_service_req(nb, MSG_GetPPTABLE, &args);
	spin_unlock(&smu_lock);

	pr_warn("PPTable Ver: %x, Current cTDP Configure: %x", pptable->Version, pptable->systemconfig);
	return 0;
    
}

static void pp_pci_remove(struct pci_dev *dev)
{
	pr_info("ryzen_nb_pp: remove\n");
	kfree(pptable);
}

static struct pci_driver pci_driver = {
	.name     = DEV_NAME,
	.id_table = id_table,
	.probe    = pp_pci_probe,
	.remove   = pp_pci_remove,
};

static int pp_driver_init(void)
{
	if (pci_register_driver(&pci_driver) < 0) {
		return 1;
	}
	return 0;
}

static void pp_driver_exit(void)
{
	pci_unregister_driver(&pci_driver);
}

module_init(pp_driver_init);
module_exit(pp_driver_exit);
MODULE_LICENSE("GPL");