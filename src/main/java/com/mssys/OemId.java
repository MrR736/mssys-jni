package com.mssys;

public class OemId extends MsSys {
	/** Returns zero terminated string with OEM ID or null at failure */
	public native String read_oem_id(OemId fp);

	/** Writes OEM ID to file system */
	public native int write_oem_id(OemId fp, String szOemId);

	/** Returns 0 if it seems like a bad idea to write OEM ID */
	public native int ok_to_write_oem_id(OemId fp, String szOemId, int bPrintMessages);
}
