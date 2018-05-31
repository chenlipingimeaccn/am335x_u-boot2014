/*
 * am335x_evm.h
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __CONFIG_AM335X_EVM_H
#define __CONFIG_AM335X_EVM_H

#include <configs/ti_am335x_common.h>

#define MACH_TYPE_TIAM335EVM		3589	/* Until the next sync */
#define CONFIG_MACH_TYPE		MACH_TYPE_TIAM335EVM
#define CONFIG_BOARD_LATE_INIT

/* Clock Defines */
#define V_OSCK				24000000  /* Clock output from T2 */
#define V_SCLK				(V_OSCK)

/* Custom script for NOR */
#define CONFIG_SYS_LDSCRIPT		"board/ti/am335x/u-boot.lds"

/* Always 128 KiB env size */
#define CONFIG_ENV_SIZE			(128 << 10)

/* Enhance our eMMC support / experience. */
#define CONFIG_CMD_GPT
#define CONFIG_EFI_PARTITION
#define CONFIG_PARTITION_UUIDS
#define CONFIG_CMD_PART

#ifdef CONFIG_BOOTDELAY
# undef CONFIG_BOOTDELAY
# define CONFIG_BOOTDELAY 	3
#endif

#ifdef CONFIG_NAND
#define NANDARGS \
	"mtdids=" MTDIDS_DEFAULT "\0" \
	"mtdparts=" MTDPARTS_DEFAULT "\0" \
	"nandargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${nandroot} " \
		"rootfstype=${nandrootfstype}\0" \
	"nandroot=ubi0:rootfs rw ubi.mtd=7,2048\0" \
	"nandrootfstype=ubifs rootwait=1\0" \
	"nandboot=echo Booting from nand ...; " \
		"run nandargs; " \
		"nand read ${fdtaddr} u-boot-spl-os; " \
		"nand read ${loadaddr} kernel; " \
		"bootz ${loadaddr} - ${fdtaddr}\0"
#else
#define NANDARGS ""
#endif

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

#if defined(CONFIG_NOR) && !defined(CONFIG_NOR_BOOT)

#define CONFIG_EXTRA_ENV_SETTINGS \
	"bootfile=uImage\0" \
	"ramdisk=ramdisk.gz\0" \
	"loadaddr=0x82000000\0" \
	"kloadaddr=0x80007fc0\0" \
	"rdloadaddr=0x81600000\0" \
	"console=ttyO0,115200n8\0" \
	"consoleblank=0\0" \
	"mmc_dev=0\0" \
	"mmc_root=/dev/mmcblk0p2 rw \0" \
	"mmc_root_fs_type=ext3\0" \
	"dispmode=LVDS\0" \
	"rootpath=/export/rootfs\0" \
	"nfsopts=nolock\0" \
	"static_ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}" \
			"::off\0" \
	"ip_method=none\0" \
	"mmc_load_image=fatload mmc ${mmc_dev} ${kloadaddr} ${bootfile};" \
		      "fatload mmc ${mmc_dev} ${rdloadaddr} ${ramdisk}\0" \
	"optargs=\0" \
	"bootargs_defaults=setenv bootargs " \
		"console=${console} " \
		"${optargs}\0" \
	"mmc_args=run bootargs_defaults;" \
		"setenv bootargs ${bootargs} " \
		"dispmode=${dispmode} " \
		"consoleblank=${consoleblank} " \
		"root=${mmc_root} initrd=${rdloadaddr},32MB " \
		"rootfstype=${mmc_root_fs_type} ip=${ip_method}\0" \
	"net_args=run bootargs_defaults;" \
		"setenv bootargs ${bootargs} " \
		"dispmode=${dispmode} " \
		"root=/dev/nfs " \
		"nfsroot=${serverip}:${rootpath},${nfsopts} rw " \
		"ip=dhcp\0" \
	"net_boot=echo Booting from network ...; " \
		"setenv autoload no; " \
		"dhcp; " \
		"tftp ${kloadaddr} ${bootfile}; " \
		"run net_args; " \
		"bootm ${kloadaddr}\0" \
        "updatesys=mmc rescan;" \
                "fatload mmc 0 0x82000000 u-boot.bin;protect off 0x08000000 +${filesize};"\
                "erase 0x08000000 +${filesize};"\
                "cp.b 0x82000000 0x08000000 ${filesize};"\
                "protect on 0x08000000 +${filesize};" \
                "fatload mmc 0 0x82000000 uImage;protect off 0x08300000 +${filesize};"\
                "erase 0x08300000 +${filesize};"\
                "cp.b 0x82000000 0x08300000 ${filesize};"\
                "protect on 0x08300000 +${filesize};\0" \
        "clearenv=protect off 0x09fe0000 +20000;erase  0x09fe0000 +0x20000\0"



#define CONFIG_BOOTCOMMAND \
        "if mmc rescan; then " \
                "echo SD/MMC found on device ${mmc_dev};" \
                "if run mmc_load_image; then " \
                        "run mmc_args;" \
                        "bootm ${kloadaddr};" \
                "fi;"\
        "fi;" \
        "echo SD/MMC not found on device ${mmc_dev};"
#endif

#if defined(CONFIG_NOR_BOOT)

#define CONFIG_EXTRA_ENV_SETTINGS \
	"bootfile=uImage\0" \
	"loadaddr=0x82000000\0" \
	"kloadaddr=0x80007fc0\0" \
	"console=ttyO0,115200n8\0" \
	"mmc_dev=0\0" \
	"dvsdk_root=/dev/mmcblk0p2 rw \0" \
	"dispmode=4.3inch_LCD\0" \
	"dvsdk_root_fs_type=ext3 rootwait\0" \
	"rootpath=/export/rootfs\0" \
	"nfsopts=nolock\0" \
	"static_ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}" \
			"::off\0" \
	"ip_method=none\0" \
        "dvsdk_load_image=fatload mmc ${mmc_dev} ${kloadaddr} ${bootfile};\0" \
	"dvsdk_load_image_nor=cp.b 0x08300000 ${kloadaddr}  0x500000;\0" \
	"optargs=\0" \
	"bootargs_defaults=setenv bootargs " \
		"console=${console} " \
		"${optargs}\0" \
        "dvsdk_args=run bootargs_defaults;" \
                "setenv bootargs ${bootargs} " \
                "dispmode=${dispmode} " \
                "root=${dvsdk_root}  " \
                "rootfstype=${dvsdk_root_fs_type} " \
		"mtdparts=physmap-flash.0:4m(u-boot),4m(kernel),-(rootfs)"\
                "earlyprintk\0 " \
	"net_args=run bootargs_defaults;" \
		"setenv bootargs ${bootargs} " \
		"dispmode=${dispmode} " \
		"root=/dev/nfs " \
		"nfsroot=${serverip}:${rootpath},${nfsopts} rw " \
		"ip=dhcp\0" \
        "dvsdk_boot=echo Booting from dvsdk ...; " \
                "run dvsdk_args; " \
                "mmc rescan; " \
		"run dvsdk_load_image_nor;" \
                "bootm ${kloadaddr}\0" \
	"net_boot=echo Booting from network ...; " \
		"setenv autoload no; " \
		"dhcp; " \
		"tftp ${kloadaddr} ${bootfile}; " \
		"run net_args; " \
		"bootm ${kloadaddr}\0" \
        "updatesys=mmc rescan;" \
		"fatload mmc 0 0x82000000 u-boot.bin;protect off 0x08000000 +${filesize};"\
                "erase 0x08000000 +${filesize};"\
                "cp.b 0x82000000 0x08000000 ${filesize};"\
                "protect on 0x08000000 +${filesize};" \
                "fatload mmc 0 0x82000000 uImage;protect off 0x08400000 +${filesize};"\
                "erase 0x08400000 +${filesize};"\
                "cp.b 0x82000000 0x08400000 ${filesize};"\
                "protect on 0x08400000 +${filesize};" \
		"fatload mmc 0 0x82000000 jffs2.img;protect off 0x08800000 +${filesize};"\
                "erase 0x08800000 +${filesize};"\
                "cp.b 0x82000000 0x08800000 ${filesize};"\
                "protect on 0x08800000 +${filesize};\0" \
        "clearenv=protect off 0x09fe0000 +0x20000;erase  0x09fe0000 +0x20000\0"



/* dvsdk */
#define CONFIG_BOOTCOMMAND "run dvsdk_boot"

#endif


		
/* NS16550 Configuration */
#define CONFIG_SYS_NS16550_COM1		0x44e09000	/* Base EVM has UART0 */
#define CONFIG_SYS_NS16550_COM2		0x48022000	/* UART1 */
#define CONFIG_SYS_NS16550_COM3		0x48024000	/* UART2 */
#define CONFIG_SYS_NS16550_COM4		0x481a6000	/* UART3 */
#define CONFIG_SYS_NS16550_COM5		0x481a8000	/* UART4 */
#define CONFIG_SYS_NS16550_COM6		0x481aa000	/* UART5 */
#define CONFIG_BAUDRATE			115200

#define CONFIG_CMD_EEPROM
#define CONFIG_ENV_EEPROM_IS_ON_I2C
#define CONFIG_SYS_I2C_EEPROM_ADDR	0x50	/* Main EEPROM */
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	2
#define CONFIG_SYS_I2C_MULTI_EEPROMS

/* PMIC support */
#define CONFIG_POWER_TPS65217
#define CONFIG_POWER_TPS65910

/* SPL */
#ifndef CONFIG_NOR_BOOT
#define CONFIG_SPL_POWER_SUPPORT
#define CONFIG_SPL_YMODEM_SUPPORT

/* Bootcount using the RTC block */
#define CONFIG_BOOTCOUNT_LIMIT
#define CONFIG_BOOTCOUNT_AM33XX

/* USB gadget RNDIS */
#define CONFIG_SPL_MUSB_NEW_SUPPORT

/* General network SPL, both CPSW and USB gadget RNDIS */
#define CONFIG_SPL_NET_SUPPORT
#define CONFIG_SPL_ENV_SUPPORT
#define CONFIG_SPL_NET_VCI_STRING	"AM335x U-Boot SPL"

/* SPI flash. */
#define CONFIG_SPL_SPI_SUPPORT
#define CONFIG_SPL_SPI_FLASH_SUPPORT
#define CONFIG_SPL_SPI_LOAD
#define CONFIG_SPL_SPI_BUS		0
#define CONFIG_SPL_SPI_CS		0
#define CONFIG_SYS_SPI_U_BOOT_OFFS	0x20000

#define CONFIG_SPL_LDSCRIPT		"$(CPUDIR)/am33xx/u-boot-spl.lds"

#ifdef CONFIG_NAND
#define CONFIG_NAND_OMAP_GPMC
#define CONFIG_NAND_OMAP_ELM
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_PAGE_COUNT	(CONFIG_SYS_NAND_BLOCK_SIZE / \
					 CONFIG_SYS_NAND_PAGE_SIZE)
#define CONFIG_SYS_NAND_PAGE_SIZE	2048
#define CONFIG_SYS_NAND_OOBSIZE		64
#define CONFIG_SYS_NAND_BLOCK_SIZE	(128*1024)
#define CONFIG_SYS_NAND_BAD_BLOCK_POS	NAND_LARGE_BADBLOCK_POS
#define CONFIG_SYS_NAND_ECCPOS		{ 2, 3, 4, 5, 6, 7, 8, 9, \
					 10, 11, 12, 13, 14, 15, 16, 17, \
					 18, 19, 20, 21, 22, 23, 24, 25, \
					 26, 27, 28, 29, 30, 31, 32, 33, \
					 34, 35, 36, 37, 38, 39, 40, 41, \
					 42, 43, 44, 45, 46, 47, 48, 49, \
					 50, 51, 52, 53, 54, 55, 56, 57, }

#define CONFIG_SYS_NAND_ECCSIZE		512
#define CONFIG_SYS_NAND_ECCBYTES	14
#define CONFIG_SYS_NAND_ONFI_DETECTION
#define CONFIG_NAND_OMAP_ECCSCHEME	OMAP_ECC_BCH8_CODE_HW
#define CONFIG_SYS_NAND_U_BOOT_START	CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_NAND_U_BOOT_OFFS	0x80000
#endif
#endif

/*
 * For NOR boot, we must set this to the start of where NOR is mapped
 * in memory.
 */
#ifdef CONFIG_NOR_BOOT
#define CONFIG_SYS_TEXT_BASE		0x08000000
#endif

/*
 * USB configuration.  We enable MUSB support, both for host and for
 * gadget.  We set USB0 as peripheral and USB1 as host, based on the
 * board schematic and physical port wired to each.  Then for host we
 * add mass storage support and for gadget we add both RNDIS ethernet
 * and DFU.
 */
#define CONFIG_USB_MUSB_DSPS
#define CONFIG_ARCH_MISC_INIT
#define CONFIG_MUSB_GADGET
#define CONFIG_MUSB_PIO_ONLY
#define CONFIG_MUSB_DISABLE_BULK_COMBINE_SPLIT
#define CONFIG_USB_GADGET
#define CONFIG_USBDOWNLOAD_GADGET
#define CONFIG_USB_GADGET_DUALSPEED
#define CONFIG_USB_GADGET_VBUS_DRAW	2
#define CONFIG_MUSB_HOST
#define CONFIG_AM335X_USB0
#define CONFIG_AM335X_USB0_MODE	MUSB_PERIPHERAL
#define CONFIG_AM335X_USB1
#define CONFIG_AM335X_USB1_MODE MUSB_HOST

#ifdef CONFIG_MUSB_HOST
#define CONFIG_CMD_USB
#define CONFIG_USB_STORAGE
#endif

#ifdef CONFIG_MUSB_GADGET
#define CONFIG_USB_ETHER
#define CONFIG_USB_ETH_RNDIS
#define CONFIG_USBNET_HOST_ADDR	"de:ad:be:af:00:00"

/* USB TI's IDs */
#define CONFIG_G_DNL_VENDOR_NUM 0x0403
#define CONFIG_G_DNL_PRODUCT_NUM 0xBD00
#define CONFIG_G_DNL_MANUFACTURER "Texas Instruments"
#endif /* CONFIG_MUSB_GADGET */

#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_USBETH_SUPPORT)
/* disable host part of MUSB in SPL */
#undef CONFIG_MUSB_HOST
/* disable EFI partitions and partition UUID support */
#undef CONFIG_PARTITION_UUIDS
#undef CONFIG_EFI_PARTITION
/*
 * Disable CPSW SPL support so we fit within the 101KiB limit.
 */
#undef CONFIG_SPL_ETH_SUPPORT
#endif

/* USB Device Firmware Update support */
#define CONFIG_DFU_FUNCTION
#define CONFIG_DFU_MMC
#define CONFIG_CMD_DFU
#define DFU_ALT_INFO_MMC \
	"dfu_alt_info_mmc=" \
	"boot part 0 1;" \
	"rootfs part 0 2;" \
	"MLO fat 0 1;" \
	"MLO.raw mmc 100 100;" \
	"u-boot.img.raw mmc 300 400;" \
	"spl-os-args.raw mmc 80 80;" \
	"spl-os-image.raw mmc 900 2000;" \
	"spl-os-args fat 0 1;" \
	"spl-os-image fat 0 1;" \
	"u-boot.img fat 0 1;" \
	"uEnv.txt fat 0 1\0"
#ifdef CONFIG_NAND
#define CONFIG_DFU_NAND
#define DFU_ALT_INFO_NAND \
	"dfu_alt_info_nand=" \
	"SPL part 0 1;" \
	"SPL.backup1 part 0 2;" \
	"SPL.backup2 part 0 3;" \
	"SPL.backup3 part 0 4;" \
	"u-boot part 0 5;" \
	"u-boot-spl-os part 0 6;" \
	"kernel part 0 8;" \
	"rootfs part 0 9\0"
#else
#define DFU_ALT_INFO_NAND ""
#endif
#define CONFIG_DFU_RAM
#define DFU_ALT_INFO_RAM \
	"dfu_alt_info_ram=" \
	"kernel ram 0x80200000 0xD80000;" \
	"fdt ram 0x80F80000 0x80000;" \
	"ramdisk ram 0x81000000 0x4000000\0"
#define DFUARGS \
	"dfu_alt_info_emmc=rawemmc mmc 0 3751936\0" \
	DFU_ALT_INFO_MMC \
	DFU_ALT_INFO_RAM \
	DFU_ALT_INFO_NAND

/*
 * Default to using SPI for environment, etc.
 * 0x000000 - 0x020000 : SPL (128KiB)
 * 0x020000 - 0x0A0000 : U-Boot (512KiB)
 * 0x0A0000 - 0x0BFFFF : First copy of U-Boot Environment (128KiB)
 * 0x0C0000 - 0x0DFFFF : Second copy of U-Boot Environment (128KiB)
 * 0x0E0000 - 0x442000 : Linux Kernel
 * 0x442000 - 0x800000 : Userland
 */
#if defined(CONFIG_SPI_BOOT)
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#define CONFIG_ENV_SPI_MAX_HZ		CONFIG_SF_DEFAULT_SPEED
#define CONFIG_ENV_SECT_SIZE		(4 << 10) /* 4 KB sectors */
#define CONFIG_ENV_OFFSET		(768 << 10) /* 768 KiB in */
#define CONFIG_ENV_OFFSET_REDUND	(896 << 10) /* 896 KiB in */
#define MTDIDS_DEFAULT			"nor0=m25p80-flash.0"
#define MTDPARTS_DEFAULT		"mtdparts=m25p80-flash.0:128k(SPL)," \
					"512k(u-boot),128k(u-boot-env1)," \
					"128k(u-boot-env2),3464k(kernel)," \
					"-(rootfs)"
#elif defined(CONFIG_EMMC_BOOT)
#undef CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV		1
#define CONFIG_SYS_MMC_ENV_PART		2
#define CONFIG_ENV_OFFSET		0x0
#define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#endif

/* SPI flash. */
#define CONFIG_CMD_SF
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_WINBOND
#define CONFIG_SF_DEFAULT_SPEED		24000000

/* Network. */
#define CONFIG_PHY_GIGE
#define CONFIG_PHYLIB
#define CONFIG_PHY_SMSC

/* NAND support */
#ifdef CONFIG_NAND
#define CONFIG_CMD_NAND
#if !defined(CONFIG_SPI_BOOT) && !defined(CONFIG_NOR_BOOT)
#define MTDIDS_DEFAULT			"nand0=omap2-nand.0"
#define MTDPARTS_DEFAULT		"mtdparts=omap2-nand.0:128k(SPL)," \
					"128k(SPL.backup1)," \
					"128k(SPL.backup2)," \
					"128k(SPL.backup3),1792k(u-boot)," \
					"128k(u-boot-spl-os)," \
					"128k(u-boot-env),5m(kernel),-(rootfs)"
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET		0x260000 /* environment starts here */
#define CONFIG_SYS_ENV_SECT_SIZE	(128 << 10)	/* 128 KiB */
#endif
#endif

/*
 * NOR Size = 16 MiB
 * Number of Sectors/Blocks = 128
 * Sector Size = 128 KiB
 * Word length = 16 bits
 * Default layout:
 * 0x000000 - 0x07FFFF : U-Boot (512 KiB)
 * 0x080000 - 0x09FFFF : First copy of U-Boot Environment (128 KiB)
 * 0x0A0000 - 0x0BFFFF : Second copy of U-Boot Environment (128 KiB)
 * 0x0C0000 - 0x4BFFFF : Linux Kernel (4 MiB)
 * 0x4C0000 - 0xFFFFFF : Userland (11 MiB + 256 KiB)
 */
#if defined(CONFIG_NOR)
#undef CONFIG_SYS_NO_FLASH
#define CONFIG_CMD_FLASH
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE
#if 0
#define CONFIG_SYS_FLASH_PROTECTION
#endif
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_FLASH_CFI_MTD
#define CONFIG_SYS_MAX_FLASH_SECT	1024// 256
#define CONFIG_SYS_MAX_FLASH_BANKS	1//1
#define CONFIG_SYS_FLASH_SIZE		(0x08000000)//(0x02000000)
#define CONFIG_SYS_FLASH_BASE		(0x08000000)
#define CONFIG_SYS_FLASH_CFI_WIDTH	FLASH_CFI_16BIT
#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_FLASH_BASE
#ifdef CONFIG_NOR_BOOT
#define CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_SECT_SIZE		(128 << 10)	/* 128 KiB */
#define CONFIG_ENV_OFFSET		(512 << 10)	/* 512 KiB */
#define CONFIG_ENV_OFFSET_REDUND	(768 << 10)	/* 768 KiB */
#define MTDIDS_DEFAULT			"nor0=physmap-flash.0"
#define MTDPARTS_DEFAULT		"mtdparts=physmap-flash.0:" \
					"512k(u-boot)," \
					"128k(u-boot-env1)," \
					"128k(u-boot-env2)," \
					"4m(kernel),-(rootfs)"
#endif
#endif  /* NOR support */

#endif	/* ! __CONFIG_AM335X_EVM_H */
