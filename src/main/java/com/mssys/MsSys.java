package com.mssys;

public class MsSys {
    protected long file_ptr;

    static { System.loadLibrary("mssys-jni"); }

    /** @brief Get ms-sys JNI version. */
    public native String mssys_version();
    public native String mssys_jni_version();
    public native int mssys_jni_major();
    public native int mssys_jni_minor();
    public native int mssys_jni_patch();

    /* Open a file and create a new stream for it. */
    public native void fopen(MsSys fp,String path, String mode);

    public void fopen(String path, String mode) {
	fopen(this, path, mode);
    }

    /* Close STREAM. */
    public native void fclose(MsSys ptr);
}
