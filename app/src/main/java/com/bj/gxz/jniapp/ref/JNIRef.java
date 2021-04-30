package com.bj.gxz.jniapp.ref;

/**
 * Created by guxiuzhong on 2020/10/13.
 */
public class JNIRef {
    static {
        System.loadLibrary("native-lib");
    }

    public native String jnilocalRef();

    public native String jniGlobalRef();

    public native void delGlobalRef();

    public native String jniWeakGlobalRef();

    public native void delWeakGlobalRef();

    public native void localRefOverflow();

    public native void refSame();
    public native String refCache();
    public native void delRefCache();

}
