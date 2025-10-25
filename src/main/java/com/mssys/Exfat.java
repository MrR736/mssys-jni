package com.mssys;

public class Exfat extends MsSys {
	/* returns true if the file has a EXFAT file system, otherwise false.
	   The file position will change when this function is called! */
	public native int is_exfat_fs(Exfat fp);

	/* returns true if the file has a EXFAT boot record, otherwise false.
	   The file position will change when this function is called! */
	public native int is_exfat_br(Exfat fp);

	/* returns true if the file has an exact match of the EXFAT boot record this
	   program would create for NT6.0, otherwise false.
	   The file position will change when this function is called! */
	public native int entire_exfat_nt6_br_matches(Exfat fp);

	/* Writes an EXFAT NT6.0 boot record to a file, returns true on success,
	   otherwise false */
	public native int write_exfat_nt6_br(Exfat fp);

	/* Calculate the new EXFAT Volume Boot Record checksum and fill the
	   twelfth sector of the main and backup VBR regions with this value. */
	public native int write_exfat_br_checksum(Exfat fp);

	/* Function to calculate the new VBR checksum value required above. */
	public native int exfat_boot_checksum(byte[] sector, long size);

	/* Function to get logical sector size of media, returns reported
	   value or 512 if unable, then is used to determine VBR byte offsets. */
	public native long get_sector_size(Exfat fp);
}
