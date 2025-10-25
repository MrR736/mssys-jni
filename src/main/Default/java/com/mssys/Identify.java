package com.mssys;

public class Identify extends MsSys {
	public static final int NO_WRITING = 0;
	public static final int AUTO_BR = 1;
	public static final int MBR_DOS = 2;
	public static final int FAT12_BR = 3;
	public static final int FAT16_BR = 4;
	public static final int FAT32_BR = 5;
	public static final int FAT32NT5_BR = 6;
	public static final int FAT32NT6_BR = 7;
	public static final int EXFATNT6_BR = 8;
	public static final int MBR_95B = 9;
	public static final int MBR_2000 = 10;
	public static final int MBR_VISTA = 11;
	public static final int MBR_WIN7 = 12;
	public static final int MBR_SYSLINUX = 13;
	public static final int MBR_ZERO = 14;
	public static final int FAT16FD_BR = 15;
	public static final int FAT32FD_BR = 16;
	public static final int FAT32PE_BR = 17;
	public static final int NTFS_BR = 18;
	public static final int MBR_GPT_SYSLINUX = 19;
	public static final int MBR_RUFUS = 20;
	public static final int MBR_REACTOS = 21;
	public static final int FAT16ROS_BR = 22;
	public static final int FAT32ROS_BR = 23;
	public static final int FAT32KOS_BR = 24;
	public static final int MBR_GRUB4DOS = 25;
	public static final int MBR_GRUB2 = 26;
	public static final int MBR_KOLIBRIOS = 27;
	public static final int NUMBER_OF_RECORD_TYPES = 28;

	/* Returns the number of sectors on disk before partition */
	public native long partition_start_sector(Identify fp);

	/* Returns the number of heads for the drive of a partition */
	public native short partition_number_of_heads(Identify fp);

	/* Returns true if writing a boot record of type iBr seems like a good idea,
	   otherwise false */
	public native int sanity_check(Identify fp, String szPath, int iBr, int bPrintMessages);

	/* Prints some information about a device */
	public native void diagnose(Identify fp, String szPath);

	/* Does a smart automatic selection of which boot record to write, returns
	   the kind of boot record as defined above */
	public native int smart_select(Identify fp);
}
