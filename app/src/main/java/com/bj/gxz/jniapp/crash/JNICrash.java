package com.bj.gxz.jniapp.crash;

/**
 * Created by guxiuzhong@baidu.com on 2020/9/28.
 */
public class JNICrash {
    static {
        System.loadLibrary("native-lib");
    }

    public native void crash();
}
