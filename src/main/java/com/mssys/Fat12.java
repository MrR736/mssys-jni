package com.mssys;

public class Fat12 extends MsSys {
	/*	returns true if the file has a FAT12 file system, otherwise false.
		The file position will change when this function is called! */
	public native int is_fat_12_fs(Fat12 fp);

	/*	returns true if the file has an exact match ot the FAT12 boot record this
		program would create, otherwise false.
		The file position will change when this function is called! */
	public native int entire_fat_12_br_matches(Fat12 fp);

	/*	Writes a FAT12 boot record to a file, returns true on success, otherwise
		false */
	public native int write_fat_12_br(Fat12 fp, int bKeepLabel);
}
