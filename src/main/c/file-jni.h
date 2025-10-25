/**
 * File JNI v1.0.0 For C/C++
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

#ifndef FILE_JNI_H
#define FILE_JNI_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "jni.h"

#ifdef __ANDROID__
#if __has_include(<android/log.h>)
#include <android/log.h>
#else
#error "<android/log.h> not found"
#endif
#endif

#define FILE_JNI_VERSION_MAJOR	1
#define FILE_JNI_VERSION_MINOR	0
#define FILE_JNI_VERSION_PATCH	0
#define FILE_JNI_VERSION	"1.0.0"

// Custom
#ifndef FILE_JNI_PACKAGE_PATH
#define FILE_JNI_PACKAGE_PATH	"com/example/CFile"
#endif

#ifndef FILE_JNI_NAME
#define FILE_JNI_NAME	"file_ptr"
#endif

#ifndef FILE_JNI_TYPE
#define FILE_JNI_TYPE 'J'
#endif

#ifdef FILE_JNI_TYPE
#if FILE_JNI_TYPE == 'I'
#define GET_FILE_JNI	GetIntField
#define SET_FILE_JNI	SetIntField
#define FILE_JNI_SIG	"I"
typedef jint file_jni_t;
#elif FILE_JNI_TYPE == 'J'
#define GET_FILE_JNI	GetLongField
#define SET_FILE_JNI	SetLongField
#define FILE_JNI_SIG	"J"
typedef jlong file_jni_t;
#elif FILE_JNI_TYPE == 'S'
#define GET_FILE_JNI	GetShortField
#define SET_FILE_JNI	SetShortField
#define FILE_JNI_SIG	"S"
typedef jshort file_jni_t;
#elif FILE_JNI_TYPE == 'F'
#define GET_FILE_JNI	GetFloatField
#define SET_FILE_JNI	SetFloatField
#define FILE_JNI_SIG	"F"
typedef jfloat file_jni_t;
#elif FILE_JNI_TYPE == 'D'
#define GET_FILE_JNI	GetDoubleField
#define SET_FILE_JNI	SetDoubleField
#define FILE_JNI_SIG	"D"
typedef jdouble file_jni_t;
#endif
#endif

#if defined(__clang__) || defined(__GNUC__)
#define FILE_JNI_UNUSED __attribute__((unused))
#else
#define FILE_JNI_UNUSED
#endif

#if defined(WIN64) || defined(_WIN64)
#define FILE_C_CAST(t,p)	((t)(unsigned long long)(p))
#elif defined(__LP64__) || defined(_LP64__) || (defined(__WORDSIZE) && __WORDSIZE == 64)
#define FILE_C_CAST(t,p)	((t)(unsigned long)(p))
#else
#define FILE_C_CAST(t,p)	((t)(unsigned int)(p))
#endif

#ifdef __cplusplus
#define FILE_JNI_EXTERN_C				extern "C"
#define FILE_BASE_CAST(type, ptr)			reinterpret_cast<type>(ptr)
#define GetFileClass(env, _f)				env->GetObjectClass(_f)
#define FindFileClass(env, _p)				env->FindClass(_p)
#define GetFileFieldID(env,clazz,name,sig)		env->GetFieldID(clazz,name,sig)
#define GetFileField(env, clazz, fieldID)		env->GET_FILE_JNI(clazz, fieldID)
#define SetFileField(env, obj, fieldID, val)		env->SET_FILE_JNI(obj, fieldID, val)
#define FILE_JNI_GetStringUTFChars(env,str,isCopy)	env->GetStringUTFChars(str,isCopy)
#define FILE_JNI_ReleaseStringUTFChars(env,str,chars)	env->ReleaseStringUTFChars(str,chars)
#define GetFileMethodID(env,ex,name,sig)		env->GetMethodID(ex,name,sig)
#define GetFileByteArrayElements(env, src, c)		env->GetByteArrayElements(src,c)
#define ReleaseFileByteArrayElements(env,a,b,m)		env->ReleaseByteArrayElements(a,b,m)
#else
#define FILE_JNI_EXTERN_C
#define FILE_BASE_CAST					FILE_C_CAST
#define GetFileClass(env, _f)				(*env)->GetObjectClass(env,_f)
#define FindFileClass(env, _p)				(*env)->FindClass(env,_p)
#define GetFileFieldID(env,clazz,name,sig)		(*env)->GetFieldID(env,clazz,name,sig)
#define GetFileField(env, clazz, fieldID)		(*env)->GET_FILE_JNI(env, clazz, fieldID)
#define SetFileField(env, obj, fieldID, val)		(*env)->SET_FILE_JNI(env, obj, fieldID, val)
#define FILE_JNI_GetStringUTFChars(env,str,isCopy)	(*env)->GetStringUTFChars(env,str,isCopy)
#define FILE_JNI_ReleaseStringUTFChars(env,str,chars)	(*env)->ReleaseStringUTFChars(env,str,chars)
#define GetFileMethodID(env,ex,name,sig)		(*env)->GetMethodID(env,ex,name,sig)
#define GetFileByteArrayElements(env,src,c)		(*env)->GetByteArrayElements(env, src, c)
#define ReleaseFileByteArrayElements(env,a,b,m)		(*env)->ReleaseByteArrayElements(env,a,b,m)
#endif

#define FILE_CAST(ptr)	FILE_BASE_CAST(FILE*, ptr)
#define file_base_cast	FILE_BASE_CAST
#define file_c_cast	FILE_C_CAST
#define file_cast(ptr) FILE_CAST(ptr)
#define CLOSE_FILE(ptr) do { if ((ptr) != NULL) { fclose(ptr); (ptr) = NULL; } } while (0)
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define basename_t(file)	strrchr(file,'\\')
#else
#define basename_t(file)	strrchr(file,'/')
#endif

#if defined(_MSC_VER) && _MSC_VER < 1900 && !defined(inline)
#define inline __inline
#endif

#ifdef __cplusplus
extern "C" {
#endif

static inline FILE *OPEN_FILE(const char *path, const char *mode) {
	if (!path || !mode) {
#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_ERROR, "File-JNI",
#else
		fprintf(stderr,"[File-JNI] [%s:%d] ", basename_t(__FILE__), __LINE__), fprintf(stderr,
#endif
			"OPEN_FILE: Invalid input: path=%s, mode=%s\n", path ? path : "(null)", mode ? mode : "(null)");
		return NULL;
	}
	FILE *fp = fopen(path, mode);
	if (!fp) {
#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_ERROR, "File-JNI",
#else
		fprintf(stderr,"[File-JNI] [%s:%d] ", basename_t(__FILE__), __LINE__), fprintf(stderr,
#endif
			"OPEN_FILE: Failed to open file %s with mode %s: %s\n",
				path ? path : "(null)", mode ? mode : "(null)", strerror(errno));
		return NULL;
	}
	return fp;
}

/**
 * Java Example Code
 *
 * package com.example;
 *
 * public class CFile {
 *   protected Type file_ptr; // replace Type with int or long or short or float or double
 *
 *   public void setFile(Type ptr) { this.file_ptr = ptr; }
 *
 *   public native void fopen(CFile fp,String path, String mode);
 *
 *   public void fopen(String path, String mode) {
 *       fopen(this, path, mode);
 *   }
 *
 *   public native void fclose(CFile ptr);
 * }
 */

static inline FILE *GetJFile(JNIEnv* env, jobject jfile) {
	jclass fcp = GetFileClass(env,jfile);
	if (!fcp) return NULL;
	jfieldID fcid = GetFileFieldID(env,fcp,FILE_JNI_NAME,FILE_JNI_SIG);
	if (!fcid) return NULL;
	file_jni_t lfp = GetFileField(env, jfile, fcid);
	return file_cast(lfp);
}

static inline void SetJFile(JNIEnv* env, jobject jfp, FILE *fp) {
    jclass fcp = GetFileClass(env, jfp);
    if (!fcp) return;
    jfieldID fcid = GetFileFieldID(env, fcp, FILE_JNI_NAME, FILE_JNI_SIG);
    if (!fcid) return;
    SetFileField(env, jfp, fcid, file_base_cast(file_jni_t,fp));
}

#define MAKE_OBJECT_OPEN_FILE(name) \
FILE_JNI_EXTERN_C JNIEXPORT void JNICALL \
    name(JNIEnv *env, FILE_JNI_UNUSED jobject obj, jobject jfp, jstring jpath, jstring jmode) { \
    const char *path = FILE_JNI_GetStringUTFChars(env, jpath, NULL); \
    const char *mode = FILE_JNI_GetStringUTFChars(env, jmode, NULL); \
    FILE *fp = OPEN_FILE(path, mode); \
    FILE_JNI_ReleaseStringUTFChars(env, jpath, path); \
    FILE_JNI_ReleaseStringUTFChars(env, jmode, mode); \
    SetJFile(env,jfp,fp); \
}

#define MAKE_OBJECT_CLOSE_FILE(name)\
FILE_JNI_EXTERN_C JNIEXPORT void JNICALL\
	 name(JNIEnv *env, FILE_JNI_UNUSED jobject obj, jobject jptr) {\
	FILE *fp = GetJFile(env,jptr);	CLOSE_FILE(fp);	SetJFile(env,jptr,fp);\
}

#define MAKE_TYPE_OPEN_FILE(name, type)\
FILE_JNI_EXTERN_C JNIEXPORT type JNICALL\
	 name(JNIEnv *env, FILE_JNI_UNUSED jobject obj, jstring jpath, jstring jmode) {\
	const char	*path = FILE_JNI_GetStringUTFChars(env, jpath, NULL),\
		*mode = FILE_JNI_GetStringUTFChars(env, jmode, NULL);\
	FILE *fp = OPEN_FILE(path, mode);\
	FILE_JNI_ReleaseStringUTFChars(env,jpath,path);\
	FILE_JNI_ReleaseStringUTFChars(env,jmode,mode);\
	return file_base_cast(type, fp);\
}

#define MAKE_TYPE_CLOSE_FILE(name, type)\
FILE_JNI_EXTERN_C JNIEXPORT void JNICALL name(JNIEnv *env, FILE_JNI_UNUSED jobject obj, type ptr) {\
	FILE *fp = file_cast(ptr);\
	CLOSE_FILE(fp);\
}

#define MAKE_TYPE_MAIN_FILE(name,type,__func)\
FILE_JNI_EXTERN_C JNIEXPORT jlong JNICALL\
	 name(JNIEnv *env, FILE_JNI_UNUSED jobject obj, jbyteArray jptr, jlong jsize,\
		  jlong jn, type jfp) {\
	FILE *fp = file_cast(jfp);\
	jbyte *ptr = GetFileByteArrayElements(env,jptr,NULL);\
	jlong ret = sfile_base_cast(jlong, __func(file_base_cast(uint8_t*,ptr),\
		sfile_base_cast(size_t,jsize), sfile_base_cast(size_t,jn), fp));\
	ReleaseFileByteArrayElements(env,jptr,ptr,JNI_ABORT);\
	return ret;\
}

#define MAKE_TYPE_WRITE_FILE(name,type)	MAKE_TYPE_MAIN_FILE(name, type, fwrite)
#define MAKE_TYPE_READ_FILE(name,type)	MAKE_TYPE_MAIN_FILE(name, type, fread)

#define MAKE_INT_OPEN_FILE(name)	MAKE_TYPE_OPEN_FILE(name,jint)
#define MAKE_INT_CLOSE_FILE(name)	MAKE_TYPE_CLOSE_FILE(name,jint)

#define MAKE_LONG_OPEN_FILE(name)	MAKE_TYPE_OPEN_FILE(name,jlong)
#define MAKE_LONG_CLOSE_FILE(name)	MAKE_TYPE_CLOSE_FILE(name,jlong)

#define MAKE_SHORT_OPEN_FILE(name)	MAKE_TYPE_OPEN_FILE(name,jshort)
#define MAKE_SHORT_CLOSE_FILE(name)	MAKE_TYPE_CLOSE_FILE(name,jshort)

#define MAKE_FLOAT_OPEN_FILE(name)	MAKE_TYPE_OPEN_FILE(name,jfloat)
#define MAKE_FLOAT_CLOSE_FILE(name)	MAKE_TYPE_CLOSE_FILE(name,jfloat)

#define MAKE_DOUBLE_OPEN_FILE(name)	MAKE_TYPE_OPEN_FILE(name,jdouble)
#define MAKE_DOUBLE_CLOSE_FILE(name)	MAKE_TYPE_CLOSE_FILE(name,jdouble)

#define MAKE_INT_WRITE_FILE(name)	MAKE_TYPE_WRITE_FILE(name,jint)
#define MAKE_LONG_WRITE_FILE(name)	MAKE_TYPE_WRITE_FILE(name,jlong)
#define MAKE_SHORT_WRITE_FILE(name)	MAKE_TYPE_WRITE_FILE(name,jshort)
#define MAKE_FLOAT_WRITE_FILE(name)	MAKE_TYPE_WRITE_FILE(name,jfloat)
#define MAKE_DOUBLE_WRITE_FILE(name)	MAKE_TYPE_WRITE_FILE(name,jdouble)

#define MAKE_INT_READ_FILE(name)	MAKE_TYPE_READ_FILE(name,jint)
#define MAKE_LONG_READ_FILE(name)	MAKE_TYPE_READ_FILE(name,jlong)
#define MAKE_SHORT_READ_FILE(name)	MAKE_TYPE_READ_FILE(name,jshort)
#define MAKE_FLOAT_READ_FILE(name)	MAKE_TYPE_READ_FILE(name,jfloat)
#define MAKE_DOUBLE_READ_FILE(name)	MAKE_TYPE_READ_FILE(name,jdouble)

#ifdef __cplusplus
}
#endif

#endif // FILE_JNI_H
