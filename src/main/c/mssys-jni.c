/**
 * mssys-jni.c: MsSys JNI in C
 *
 * Copyright (C) 2025 MrR736 <MrR736@users.github.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * The complete text of the GNU General Public License
 * can be found in /usr/share/common-licenses/GPL-3 file.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "jni.h"

#define LOG_TAG "mssys-jni"
#define FILE_JNI_PACKAGE_PATH	"com/mssys/MsSys"

#include "base-jni.h"	// Base JNI Interface
#include "file-jni.h"	// File JNI Interface

#include "br.h"
#include "exfat.h"
#include "fat12.h"
#include "fat16.h"
#include "fat32.h"
#include "file.h"
#include "identify.h"
#include "ntfs.h"
#include "oem_id.h"
#include "partition_info.h"

#include "com_mssys_Br.h"
#include "com_mssys_Exfat.h"
#include "com_mssys_Fat12.h"
#include "com_mssys_Fat16.h"
#include "com_mssys_Fat32.h"
#include "com_mssys_FileData.h"
#include "com_mssys_Identify.h"
#include "com_mssys_MsSys.h"
#include "com_mssys_OemId.h"
#include "com_mssys_PartitionInfo.h"

#define MAKE_INT_BR_INT(name, func) \
JNIEXPORT jint JNICALL name(JNIEnv *env, jobject obj, jobject ptr, jint x) { \
	FILE *fp = GetJFile(env,ptr);\
	jint ret = base_cast(jint, func(fp, x));\
	SetJFile(env,ptr,fp);\
	return ret;\
}

#define MAKE_INT_BR_LONG_BYTE_INT(name, func) \
JNIEXPORT jint JNICALL \
name(JNIEnv *env, jobject obj, jobject ptr, jlong ulPosition, jbyteArray jData, jint uiLen) {\
	FILE *fp = GetJFile(env,ptr);\
	jbyte *Data = _GetByteArrayElements(env,jData,NULL);\
	jint ret = base_cast(jint,func(fp, base_cast(unsigned long,ulPosition), ubase_cast(unsigned char *, Data),\
			base_cast(unsigned int, uiLen)));\
	SetJFile(env,ptr,fp);\
	_ReleaseByteArrayElements(env, jData, Data, JNI_ABORT); \
	return ret; \
}

#define MAKE_STRING_BR(name, func) \
JNIEXPORT jstring JNICALL name(JNIEnv *env, jobject obj, jobject ptr) { \
	FILE *fp = GetJFile(env,ptr);\
	jstring ret = _NewStringUTF(env, func(fp));\
	SetJFile(env,ptr,fp);\
	return ret;\
}

#define MAKE_TYPE_BR(type, name, func) \
JNIEXPORT type JNICALL name(JNIEnv *env, jobject obj, jobject ptr) {\
	FILE *fp = GetJFile(env,ptr);\
	type ret = base_cast(type, func(fp));\
	SetJFile(env,ptr,fp);\
	return ret; \
}

#define MAKE_TYPE_BR_STRING(type, name, func) \
JNIEXPORT type JNICALL \
name(JNIEnv *env, jobject obj, jobject ptr, jstring jx) {\
	const char *cx = _GetStringUTFChars(env, jx, NULL);\
	FILE *fp = GetJFile(env,ptr);\
	type ret = base_cast(type,func(fp, cx));\
	SetJFile(env,ptr,fp);\
	_ReleaseStringUTFChars(env, jx, cx);\
	return ret;\
}

#define MAKE_INT_BR(name, func) MAKE_TYPE_BR(jint, name, func)
#define MAKE_INT_BR_STRING(name, func) MAKE_TYPE_BR_STRING(jint, name, func)

MAKE_OBJECT_OPEN_FILE(Java_com_mssys_MsSys_fopen)
MAKE_OBJECT_CLOSE_FILE(Java_com_mssys_MsSys_fclose)

JNIEXPORT jstring JNICALL Java_com_mssys_MsSys_mssys_1version(JNIEnv *env, jobject obj) {
    return (*env)->NewStringUTF(env, MS_SYS_VERSION);
}

JNIEXPORT jstring JNICALL Java_com_mssys_MsSys_mssys_1jni_1version(JNIEnv *env, jobject obj) {
    return (*env)->NewStringUTF(env, MS_SYS_JNI_VERSION);
}

JNIEXPORT jint JNICALL Java_com_mssys_MsSys_mssys_1jni_1major(JNIEnv *env, jobject obj) {
    return base_cast(jint,MS_SYS_JNI_VERSION_MAJOR);
}

JNIEXPORT jint JNICALL Java_com_mssys_MsSys_mssys_1jni_1minor(JNIEnv *env, jobject obj) {
    return base_cast(jint,MS_SYS_JNI_VERSION_MINOR);
}

JNIEXPORT jint JNICALL Java_com_mssys_MsSys_mssys_1jni_1patch(JNIEnv *env, jobject obj) {
    return base_cast(jint,MS_SYS_JNI_VERSION_PATCH);
}

JNIEXPORT jint JNICALL
Java_com_mssys_Identify_sanity_1check(JNIEnv *env, jobject obj, jobject ptr,
    jstring jszPath, jint iBr, jint bPrintMessages) {
	const char *szPath = _GetStringUTFChars(env, jszPath, NULL);
	FILE *fp = GetJFile(env,ptr);
	jint ret = base_cast(jint,sanity_check(fp, szPath, base_cast(int,iBr), base_cast(int,bPrintMessages)));
	SetJFile(env,ptr,fp);
	_ReleaseStringUTFChars(env, jszPath, szPath);
	return ret;
}

JNIEXPORT void JNICALL
Java_com_mssys_Identify_diagnose
	 (JNIEnv *env, jobject obj, jobject ptr, jstring jszPath) {
	FILE *fp = GetJFile(env,ptr);
	const char *szPath = _GetStringUTFChars(env,jszPath,NULL);
	diagnose(fp,szPath);
	SetJFile(env,ptr,fp);
	_ReleaseStringUTFChars(env,jszPath,szPath);
}
MAKE_TYPE_BR(jshort, Java_com_mssys_Identify_partition_1number_1of_1heads,partition_number_of_heads)
#ifdef __OpenBSD__
MAKE_TYPE_BR_STRING(jlong, Java_com_mssys_Identify_partition_1start_1sector,partition_start_sector)
MAKE_INT_BR_STRING(Java_com_mssys_Identify_smart_1select,smart_select)
#else
MAKE_TYPE_BR(jlong, Java_com_mssys_Identify_partition_1start_1sector,partition_start_sector)
MAKE_INT_BR(Java_com_mssys_Identify_smart_1select, smart_select)
#endif

JNIEXPORT void JNICALL Java_com_mssys_Br_set_1bytes_1per_1sector
		(JNIEnv *env, jobject obj, jlong ulValue) {
	set_bytes_per_sector(base_cast(unsigned long,ulValue));
}
JNIEXPORT jint JNICALL
Java_com_mssys_Br_write_1windows_1disk_1signature(JNIEnv *env, jobject obj, jobject ptr, jint tWDS) {
	FILE *fp = GetJFile(env,ptr);
	jint ret = base_cast(jint,write_windows_disk_signature(fp, base_cast(uint32_t,tWDS)));
	SetJFile(env,ptr,fp);
	return ret;
}
MAKE_INT_BR(Java_com_mssys_Br_read_1windows_1disk_1signature,read_windows_disk_signature)
MAKE_TYPE_BR(jshort, Java_com_mssys_Br_read_1mbr_1copy_1protect_1bytes,read_mbr_copy_protect_bytes)
MAKE_STRING_BR(Java_com_mssys_Br_read_1mbr_1copy_1protect_1bytes_1explained,read_mbr_copy_protect_bytes_explained)
MAKE_INT_BR(Java_com_mssys_Br_is_1br,is_br)
MAKE_INT_BR(Java_com_mssys_Br_is_1lilo_1br,is_lilo_br)
MAKE_INT_BR(Java_com_mssys_Br_is_1dos_1mbr,is_dos_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_1dos_1f2_1mbr,is_dos_f2_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_195b_1mbr,is_95b_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_12000_1mbr,is_2000_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_1vista_1mbr,is_vista_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_1win7_1mbr,is_win7_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_1rufus_1mbr,is_rufus_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_1reactos_1mbr,is_reactos_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_1grub4dos_1mbr,is_grub4dos_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_1grub2_1mbr,is_grub2_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_1kolibrios_1mbr,is_kolibrios_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_1syslinux_1mbr,is_syslinux_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_1syslinux_1gpt_1mbr,is_syslinux_gpt_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_1zero_1mbr,is_zero_mbr)
MAKE_INT_BR(Java_com_mssys_Br_is_1zero_1mbr_1not_1including_1disk_1signature_1or_1copy_1protect,
	    is_zero_mbr_not_including_disk_signature_or_copy_protect)

MAKE_INT_BR(Java_com_mssys_Br_write_1dos_1mbr,write_dos_mbr)
MAKE_INT_BR(Java_com_mssys_Br_write_195b_1mbr,write_95b_mbr)
MAKE_INT_BR(Java_com_mssys_Br_write_12000_1mbr,write_2000_mbr)
MAKE_INT_BR(Java_com_mssys_Br_write_1vista_1mbr,write_vista_mbr)
MAKE_INT_BR(Java_com_mssys_Br_write_1win7_1mbr,write_win7_mbr)
MAKE_INT_BR(Java_com_mssys_Br_write_1rufus_1mbr,write_rufus_mbr)
MAKE_INT_BR(Java_com_mssys_Br_write_1reactos_1mbr,write_reactos_mbr)
MAKE_INT_BR(Java_com_mssys_Br_write_1grub4dos_1mbr,write_grub4dos_mbr)
MAKE_INT_BR(Java_com_mssys_Br_write_1grub2_1mbr,write_grub2_mbr)
MAKE_INT_BR(Java_com_mssys_Br_write_1kolibrios_1mbr,write_kolibrios_mbr)
MAKE_INT_BR(Java_com_mssys_Br_write_1syslinux_1mbr,write_syslinux_mbr)
MAKE_INT_BR(Java_com_mssys_Br_write_1syslinux_1gpt_1mbr,write_syslinux_gpt_mbr)
MAKE_INT_BR(Java_com_mssys_Br_write_1zero_1mbr,write_zero_mbr)

JNIEXPORT jint JNICALL
Java_com_mssys_OemId_ok_1to_1write_1oem_1id
    (JNIEnv *env, jobject obj, jobject ptr, jstring jszPath, jint bPrintMessages) {
	FILE *fp = GetJFile(env,ptr);
	const char *szPath = _GetStringUTFChars(env,jszPath,NULL);
	jint ret = base_cast(jint,ok_to_write_oem_id(fp,szPath,base_cast(int,bPrintMessages)));
	SetJFile(env,ptr,fp);
	_ReleaseStringUTFChars(env, jszPath, szPath);
	return ret;
}
MAKE_STRING_BR(Java_com_mssys_OemId_read_1oem_1id,read_oem_id)
MAKE_INT_BR_STRING(Java_com_mssys_OemId_write_1oem_1id,write_oem_id)

#ifdef __OpenBSD__
MAKE_INT_BR_STRING(Java_com_mssys_PartitionInfo_write_1partition_1start_1sector_1number,write_partition_start_sector_number)
#else
MAKE_INT_BR(Java_com_mssys_PartitionInfo_write_1partition_1start_1sector_1number,write_partition_start_sector_number)
#endif
MAKE_INT_BR_INT(Java_com_mssys_PartitionInfo_write_1partition_1number_1of_1heads,write_partition_number_of_heads)
MAKE_INT_BR(Java_com_mssys_PartitionInfo_write_1partition_1physical_1disk_1drive_1id_1fat16,
			write_partition_physical_disk_drive_id_fat16)
MAKE_INT_BR(Java_com_mssys_PartitionInfo_write_1partition_1physical_1disk_1drive_1id_1fat32,
			write_partition_physical_disk_drive_id_fat32)
MAKE_INT_BR(Java_com_mssys_PartitionInfo_write_1partition_1physical_1disk_1drive_1id_1exfat,
			write_partition_physical_disk_drive_id_exfat)

MAKE_INT_BR(Java_com_mssys_Fat12_is_1fat_112_1fs,is_fat_12_fs)
MAKE_INT_BR(Java_com_mssys_Fat12_entire_1fat_112_1br_1matches,entire_fat_12_br_matches)
MAKE_INT_BR_INT(Java_com_mssys_Fat12_write_1fat_112_1br,write_fat_12_br)

MAKE_INT_BR(Java_com_mssys_Fat16_is_1fat_116_1fs, is_fat_16_fs)
MAKE_INT_BR(Java_com_mssys_Fat16_is_1fat_116_1br, is_fat_16_br)
MAKE_INT_BR(Java_com_mssys_Fat16_entire_1fat_116_1br_1matches, entire_fat_16_br_matches)
MAKE_INT_BR(Java_com_mssys_Fat16_entire_1fat_116_1fd_1br_1matches, entire_fat_16_fd_br_matches)
MAKE_INT_BR(Java_com_mssys_Fat16_entire_1fat_116_1ros_1br_1matches, entire_fat_16_ros_br_matches)
MAKE_INT_BR_INT(Java_com_mssys_Fat16_write_1fat_116_1br, write_fat_16_br)
MAKE_INT_BR_INT(Java_com_mssys_Fat16_write_1fat_116_1fd_1br, write_fat_16_fd_br)
MAKE_INT_BR_INT(Java_com_mssys_Fat16_write_1fat_116_1ros_1br, write_fat_16_ros_br)

MAKE_INT_BR(Java_com_mssys_Fat32_is_1fat_132_1fs, is_fat_32_fs)
MAKE_INT_BR(Java_com_mssys_Fat32_is_1fat_132_1br, is_fat_32_br)
MAKE_INT_BR(Java_com_mssys_Fat32_entire_1fat_132_1br_1matches,entire_fat_32_br_matches)
MAKE_INT_BR(Java_com_mssys_Fat32_entire_1fat_132_1fd_1br_1matches,entire_fat_32_fd_br_matches)
MAKE_INT_BR(Java_com_mssys_Fat32_entire_1fat_132_1nt5_1br_1matches,entire_fat_32_nt5_br_matches)
MAKE_INT_BR(Java_com_mssys_Fat32_entire_1fat_132_1nt6_1br_1matches,entire_fat_32_nt6_br_matches)
MAKE_INT_BR(Java_com_mssys_Fat32_entire_1fat_132_1pe_1br_1matches,entire_fat_32_pe_br_matches)
MAKE_INT_BR(Java_com_mssys_Fat32_entire_1fat_132_1ros_1br_1matches,entire_fat_32_ros_br_matches)
MAKE_INT_BR(Java_com_mssys_Fat32_entire_1fat_132_1kos_1br_1matches,entire_fat_32_kos_br_matches)
MAKE_INT_BR_INT(Java_com_mssys_Fat32_write_1fat_132_1br,write_fat_32_br)
MAKE_INT_BR_INT(Java_com_mssys_Fat32_write_1fat_132_1fd_1br,write_fat_32_fd_br)
MAKE_INT_BR_INT(Java_com_mssys_Fat32_write_1fat_132_1nt5_1br,write_fat_32_nt5_br)
MAKE_INT_BR_INT(Java_com_mssys_Fat32_write_1fat_132_1nt6_1br,write_fat_32_nt6_br)
MAKE_INT_BR_INT(Java_com_mssys_Fat32_write_1fat_132_1pe_1br,write_fat_32_pe_br)
MAKE_INT_BR_INT(Java_com_mssys_Fat32_write_1fat_132_1ros_1br,write_fat_32_ros_br)
MAKE_INT_BR_INT(Java_com_mssys_Fat32_write_1fat_132_1kos_1br,write_fat_32_kos_br)

JNIEXPORT jint JNICALL Java_com_mssys_Exfat_exfat_1boot_1checksum
		(JNIEnv *env, jobject obj, jbyteArray jsector, jlong size) {
	jbyte *sector = _GetByteArrayElements(env,jsector,NULL);
	jint ret = base_cast(jint,exfat_boot_checksum(ubase_cast(unsigned char*,sector), base_cast(size_t,size)));
	_ReleaseByteArrayElements(env, jsector, sector, JNI_ABORT);
	return ret;
}
MAKE_INT_BR(Java_com_mssys_Exfat_is_1exfat_1fs,is_exfat_fs)
MAKE_INT_BR(Java_com_mssys_Exfat_is_1exfat_1br,is_exfat_br)
MAKE_INT_BR(Java_com_mssys_Exfat_entire_1exfat_1nt6_1br_1matches,entire_exfat_nt6_br_matches)
MAKE_INT_BR(Java_com_mssys_Exfat_write_1exfat_1nt6_1br,write_exfat_nt6_br)
MAKE_INT_BR(Java_com_mssys_Exfat_write_1exfat_1br_1checksum,write_exfat_br_checksum)
MAKE_TYPE_BR(jlong, Java_com_mssys_Exfat_get_1sector_1size,get_sector_size)

MAKE_INT_BR(Java_com_mssys_Ntfs_is_1ntfs_1fs,is_ntfs_fs)
MAKE_INT_BR(Java_com_mssys_Ntfs_is_1ntfs_1br,is_ntfs_br)
MAKE_INT_BR(Java_com_mssys_Ntfs_entire_1ntfs_1br_1matches,entire_ntfs_br_matches)
MAKE_INT_BR(Java_com_mssys_Ntfs_write_1ntfs_1br,write_ntfs_br)

MAKE_INT_BR_LONG_BYTE_INT(Java_com_mssys_FileData_contains_1data,contains_data)
MAKE_INT_BR_LONG_BYTE_INT(Java_com_mssys_FileData_read_1data,read_data)
MAKE_INT_BR_LONG_BYTE_INT(Java_com_mssys_FileData_write_1data,write_data)
