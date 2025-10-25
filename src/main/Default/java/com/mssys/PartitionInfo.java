package com.mssys;

public class PartitionInfo extends MsSys {
	/*	Writes the number of heads to a partition, if iHeads == -1 an attempt is made
		to find out the correct value,
		returns true on success, otherwise false */
	public native int write_partition_number_of_heads(PartitionInfo fp, int iHeads);

	/*	Writes the start sector number to a partition (also known as
		"number of hidden sectors"), returns true on success, otherwise false */
	public native int write_partition_start_sector_number(PartitionInfo fp);

	/* Writes a physical disk drive id of 0x80 (for C:) to a FAT16 partition */
	public native int write_partition_physical_disk_drive_id_fat16(PartitionInfo fp);

	/* Writes a physical disk drive id of 0x80 (for C:) to a FAT32 partition */
	public native int write_partition_physical_disk_drive_id_fat32(PartitionInfo fp);

	/* Writes a physical disk drive id of 0x80 (for C:) to an EXFAT partition */
	public native int write_partition_physical_disk_drive_id_exfat(PartitionInfo fp);
}
