package com.mssys;

public class Ntfs extends MsSys {
	/* returns true if the file has an NFTS file system, otherwise false.
	   The file position will change when this function is called! */
	public native int is_ntfs_fs(Ntfs fp);

	/* returns true if the file has a NTFS boot record, otherwise false.
	   The file position will change when this function is called! */
	public native int is_ntfs_br(Ntfs fp);

	/* returns true if the file has an exact match of the NTFS boot record
	   this program would create, otherwise false.
	   The file position will change when this function is called! */
	public native int entire_ntfs_br_matches(Ntfs fp);

	/* Writes a NTFS boot record to a file, returns true on success, otherwise false */
	public native int write_ntfs_br(Ntfs fp, int bKeepLabel);
}
