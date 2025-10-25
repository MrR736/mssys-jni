package com.mssys;

public class Br extends MsSys {
	/* Sets custom number of bytes per sector, default value is 512 */
	public native void set_bytes_per_sector(long ulValue);

	/* Gets Windows Disk Signature from MBR */
	public native int read_windows_disk_signature(Br fp);

	/* Sets a new Windows Disk Signature to MBR */
	public native int write_windows_disk_signature(Br fp, int tWDS);

	/* Reads copy protect bytes after Windows Disk Signature from MBR */
	public native short read_mbr_copy_protect_bytes(Br fp);
	public native String read_mbr_copy_protect_bytes_explained(Br fp);

	/*	returns true if the file has a boot record, otherwise false.
		The file position will change when this function is called! */
	public native int is_br(Br fp);

	/*	returns true if the file has a LILO boot record, otherwise false.
		The file position will change when this function is called! */
	public native int is_lilo_br(Br fp);

	/* returns true if the file has a Microsoft dos master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_dos_mbr(Br fp);

	/*	returns true if the file has a Microsoft dos master boot record with the
		undocumented F2 instruction, otherwise false. The file position will change
		when this function is called! */
	public native int is_dos_f2_mbr(Br fp);

	/* returns true if the file has a Microsoft 95b master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_95b_mbr(Br fp);

	/* returns true if the file has a Microsoft 2000 master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_2000_mbr(Br fp);

	/*	returns true if the file has a Microsoft Vista master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_vista_mbr(Br fp);

	/*	returns true if the file has a Microsoft 7 master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_win7_mbr(Br fp);

	/* returns true if the file has a Rufus master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_rufus_mbr(Br fp);

	/*	returns true if the file has a ReactOS master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_reactos_mbr(Br fp);

	/*	returns true if the file has a Grub4DOS master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_grub4dos_mbr(Br fp);

	/*	returns true if the file has a Grub 2.0 master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_grub2_mbr(Br fp);

	/*	returns true if the file has a KolibriOS master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_kolibrios_mbr(Br fp);

	/*	returns true if the file has a syslinux master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_syslinux_mbr(Br fp);

	/*	returns true if the file has a syslinux GPT master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_syslinux_gpt_mbr(Br fp);

	/*	returns true if the file has a zeroed master boot record, otherwise
		false.The file position will change when this function is called! */
	public native int is_zero_mbr(Br fp);
	public native int is_zero_mbr_not_including_disk_signature_or_copy_protect(Br fp);

	/*	Writes a dos master boot record to a file, returns true on success, otherwise false */
	public native int write_dos_mbr(Br fp);

	/*	Writes a 95b master boot record to a file, returns true on success, otherwise false */
	public native int write_95b_mbr(Br fp);

	/*	Writes a 2000 master boot record to a file, returns true on success, otherwise false */
	public native int write_2000_mbr(Br fp);

	/*	Writes a Vista master boot record to a file, returns true on success, otherwise false */
	public native int write_vista_mbr(Br fp);

	/*	Writes a Windows 7 master boot record to a file, returns true on success, otherwise false */
	public native int write_win7_mbr(Br fp);

	/*	Writes a Rufus master boot record to a file, returns true on success, otherwise false */
	public native int writeRufusMbr(Br fp);

	/*	Writes a ReactOS master boot record to a file, returns true on success, otherwise false */
	public native int write_reactos_mbr(Br fp);

	/*	Writes a Grub4DOS master boot record to a file, returns true on success, otherwise false */
	public native int write_grub4dos_mbr(Br fp);

	/*	Writes a Grub 2.0 master boot record to a file, returns true on success, otherwise false */
	public native int write_grub2_mbr(Br fp);

	/*	Writes a KolibriOS master boot record to a file, returns true on success, otherwise false */
	public native int write_kolibrios_mbr(Br fp);

	/*	Writes a syslinux master boot record to a file, returns true on success, otherwise false */
	public native int write_syslinux_mbr(Br fp);

	/*	Writes a syslinux GPT master boot record to a file, returns true on success, otherwise false */
	public native int write_syslinux_gpt_mbr(Br fp);

	/*	Writes an empty (zeroed) master boot record to a file, returns true on success, otherwise
		false */
	public native int write_zero_mbr(Br fp);
}
