package com.mssys;

public class Fat16 extends MsSys {
	/** returns true if the file has a FAT16 file system, otherwise false,
	    The file position will change when this function is called! */
	public native int is_fat_16_fs(Fat16 fp);

	/** returns true if the file has a FAT16 boot record, otherwise false,
	    The file position will change when this function is called! */
	public native int is_fat_16_br(Fat16 fp);

	/** returns true if the file has an exact match of the FAT16 boot record this
	    program would create, otherwise false,
	    The file position will change when this function is called! */
	public native int entire_fat_16_br_matches(Fat16 fp);

	/** Writes a FAT16 boot record to a file, returns true on success, otherwise false */
	public native int write_fat_16_br(Fat16 fp, int bKeepLabel);

	/** returns true if the file has an exact match of the FAT16 boot record this
	    program would create for FreeDOS, otherwise false,
	    The file position will change when this function is called! */
	public native int entire_fat_16_fd_br_matches(Fat16 fp);

	/** Writes a FAT16 FreeDOS boot record to a file, returns true on success, otherwise false */
	public native int write_fat_16_fd_br(Fat16 fp, int bKeepLabel);

	/** returns true if the file has an exact match of the FAT16 boot record this
	    program would create for ReactOS, otherwise false,
	    The file position will change when this function is called! */
	public native int entire_fat_16_ros_br_matches(Fat16 fp);

	/** Writes a FAT16 ReactOS boot record to a file, returns true on success, otherwise false */
	public native int write_fat_16_ros_br(Fat16 fp, int bKeepLabel);
}
