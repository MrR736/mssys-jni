package com.mssys;

public class FileData extends MsSys {
	public static final int MAX_DATA_LEN = 10240;

	/* Checks if a file contains a data pattern of length uiLen at position
	   ulPositoin. The file pointer will change when calling this function! */
	public native int contains_data(FileData fp, long ulPosition, byte[] data, int uiLen);

	/* Reads data of length uiLen at position ulPositoin.
	   The file pointer will change when calling this function! */
	public native int read_data(FileData fp, long ulPosition, byte[] data, int uiLen);

	/* Writes a data pattern of length uiLen at position ulPositoin.
	   The file pointer will change when calling this function! */
	public native int write_data(FileData fp, long ulPosition, byte[] data, int uiLen);
}
