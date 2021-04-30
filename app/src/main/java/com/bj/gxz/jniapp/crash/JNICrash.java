package com.bj.gxz.jniapp.crash;

/**
 * Created by guxiuzhong on 2020/9/28.
 */
public class JNICrash {
    static {
        System.loadLibrary("native-lib");
    }

    public native void crash();
}
