package com.mssys;

public class Fat32 extends MsSys {
	/** returns true if the file has a FAT32 file system, otherwise false,
	    The file position will change when this function is called! */
	public native int is_fat_32_fs(Fat32 fp);

	/** returns true if the file has a FAT32 DOS/NT boot record, otherwise false,
	    The file position will change when this function is called! */
	public native int is_fat_32_br(Fat32 fp);

	/** returns true if the file has an exact match of the FAT32 DOS boot record
	    this program would create, otherwise false,
	    The file position will change when this function is called! */
	public native int entire_fat_32_br_matches(Fat32 fp);

	/** Writes a FAT32 DOS boot record to a file, returns true on success, otherwise false */
	public native int write_fat_32_br(Fat32 fp, int bKeepLabel);

	/** returns true if the file has an exact match of the FAT32 boot record this
	    program would create for FreeDOS, otherwise false,
	    The file position will change when this function is called! */
	public native int entire_fat_32_fd_br_matches(Fat32 fp);

	/** Writes a FAT32 FreeDOS boot record to a file, returns true on success, otherwise false */
	public native int write_fat_32_fd_br(Fat32 fp, int bKeepLabel);

	/** returns true if the file has an exact match of the FAT32 boot record this
	    program would create for NT5.0, otherwise false,
	    The file position will change when this function is called! */
	public native int entire_fat_32_nt5_br_matches(Fat32 fp);

	/** Writes a FAT32 NT5.0 boot record to a file, returns true on success, otherwise false */
	public native int write_fat_32_nt5_br(Fat32 fp, int bKeepLabel);

	/** returns true if the file has an exact match of the FAT32 boot record this
	    program would create for NT6.0, otherwise false,
	    The file position will change when this function is called! */
	public native int entire_fat_32_nt6_br_matches(Fat32 fp);

	/** Writes a FAT32 NT6.0 boot record to a file, returns true on success, otherwise false */
	public native int write_fat_32_nt6_br(Fat32 fp, int bKeepLabel);

	/** returns true if the file has an exact match of the FAT32 boot record this
	    program would create for NT, otherwise false,
	    The file position will change when this function is called! */
	public native int entire_fat_32_pe_br_matches(Fat32 fp);

	/** Writes a FAT32 NT boot record to a file, returns true on success, otherwise false */
	public native int write_fat_32_pe_br(Fat32 fp, int bKeepLabel);

	/** returns true if the file has an exact match of the FAT32 boot record this
	    program would create for ReactOS, otherwise false,
	    The file position will change when this function is called! */
	public native int entire_fat_32_ros_br_matches(Fat32 fp);

	/** Writes a FAT32 ReactOS boot record to a file, returns true on success, otherwise false */
	public native int write_fat_32_ros_br(Fat32 fp, int bKeepLabel);

	/** returns true if the file has an exact match of the FAT32 boot record this
	    program would create for KolibriOS, otherwise false,
	    The file position will change when this function is called! */
	public native int entire_fat_32_kos_br_matches(Fat32 fp);

	/** Writes a FAT32 KolibriOS boot record to a file, returns true on success, otherwise false */
	public native int write_fat_32_kos_br(Fat32 fp, int bKeepLabel);
}
