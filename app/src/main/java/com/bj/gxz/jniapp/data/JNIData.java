package com.bj.gxz.jniapp.data;

/**
 * Created by guxiuzhong@baidu.com on 2020/10/30.
 */
public class JNIData {

    static {
        System.loadLibrary("native-lib");
    }

    public native void data(byte b, char c, boolean bool, short s, int i, float f, double d, long l, float[] floats);
}
