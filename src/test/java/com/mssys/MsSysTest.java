package com.mssys;

import com.mssys.MsSys;
import com.mssys.Br;
import com.mssys.Fat12;
import com.mssys.Fat16;
import com.mssys.Fat32;
import com.mssys.Ntfs;
import com.mssys.Exfat;

public class MsSysTest {

	public static void main(String[] args) {
		MsSys ms = new MsSys();
		MsSysTest tester = new MsSysTest();
		System.out.println(
			"=== MsSys: " + ms.mssys_version() +
			", MsSys JNI: " + ms.mssys_jni_version() +
			", Major: " + ms.mssys_jni_major() +
			", Minor: " + ms.mssys_jni_minor() +
			", Patch: " + ms.mssys_jni_patch() + " Test ===");
		tester.testBr();
		tester.testExfat();
		tester.testFat12();
		tester.testFat16();
		tester.testFat32();
		tester.testNtfs();
	}

	private void testBr() {
		Br br = new Br();
		br.fopen("./br.img", "rb+");
		if (br.write_dos_mbr(br) == 0) {
			System.out.println("ERROR: write ./br.img dos master boot record");
			br.fclose(br);
			return;
		} else System.out.println("INFO: write ./br.img dos master boot record");
		if (br.is_dos_mbr(br) == 0) {
			System.out.println("ERROR: ./br.img dos master boot record");
			br.fclose(br);
			return;
		} else System.out.println("INFO: ./br.img dos master boot record");
		br.fclose(br);
	}

	private void testExfat() {
		Exfat exf = new Exfat();
		exf.fopen("./exfat.img", "rb+");
		if (exf.is_exfat_fs(exf) == 0) {
			System.out.println("ERROR: ./exfat.img is not Exfat Filesystem");
			exf.fclose(exf);
			return;
		} else System.out.println("INFO: ./exfat.img is Exfat Filesystem");

		if (exf.is_exfat_br(exf) == 0) {
			System.out.println("ERROR: ./exfat.img EXFAT boot record");
			exf.fclose(exf);
			return;
		} else System.out.println("INFO: ./exfat.img EXFAT boot record");
		exf.fclose(exf);
	}

	private void testFat12() {
		Fat12 vfat = new Fat12();
		vfat.fopen("./fat12.img", "rb+");
		if (vfat.is_fat_12_fs(vfat) == 0) {
			System.out.println("ERROR: ./fat12.img is not Fat12 Filesystem");
			vfat.fclose(vfat);
			return;
		} else System.out.println("INFO: ./fat12.img is Fat12 Filesystem");

		if (vfat.write_fat_12_br(vfat, 0) == 0) {
			System.out.println("ERROR: write Fat12 boot record to ./fat12.img");
			vfat.fclose(vfat);
			return;
		} else System.out.println("INFO: write Fat12 boot record to ./fat12.img");
		vfat.fclose(vfat);
	}

	private void testFat16() {
		Fat16 vfat = new Fat16();
		vfat.fopen("./fat16.img", "rb+");
		if (vfat.is_fat_16_fs(vfat) == 0) {
			System.out.println("ERROR: ./fat16.img is not Fat16 Filesystem");
			vfat.fclose(vfat);
			return;
		} else System.out.println("INFO: ./fat16.img is Fat16 Filesystem");

		if (vfat.write_fat_16_br(vfat, 0) == 0) {
			System.out.println("ERROR: write Fat16 boot record to ./fat16.img");
			vfat.fclose(vfat);
			return;
		} else System.out.println("INFO: write Fat16 boot record to ./fat16.img");
		vfat.fclose(vfat);
	}

	private void testFat32() {
		Fat32 vfat = new Fat32();
		vfat.fopen("./fat32.img", "rb+");
		if (vfat.is_fat_32_fs(vfat) == 0) {
			System.out.println("ERROR: ./fat32.img is not Fat32 Filesystem");
			vfat.fclose(vfat);
			return;
		} else System.out.println("INFO: ./fat32.img is Fat32 Filesystem");

		if (vfat.write_fat_32_br(vfat, 0) == 0) {
			System.out.println("ERROR: write Fat32 boot record to ./fat32.img");
			vfat.fclose(vfat);
			return;
		} else System.out.println("INFO: write Fat32 boot record to ./fat32.img");
		vfat.fclose(vfat);
	}

	private void testNtfs() {
		Ntfs ntfs = new Ntfs();
		ntfs.fopen("./ntfs.img", "rb+");
		if (ntfs.is_ntfs_fs(ntfs) == 0) {
			System.out.println("ERROR: ./ntfs.img is not Ntfs Filesystem");
			ntfs.fclose(ntfs);
			return;
		} else System.out.println("INFO: ./ntfs.img is Ntfs Filesystem");

		if (ntfs.write_ntfs_br(ntfs, 0) == 0) {
			System.out.println("ERROR: write Ntfs boot record to ./ntfs.img");
			ntfs.fclose(ntfs);
			return;
		} else System.out.println("INFO: write Ntfs boot record to ./ntfs.img");
		ntfs.fclose(ntfs);
	}
}
