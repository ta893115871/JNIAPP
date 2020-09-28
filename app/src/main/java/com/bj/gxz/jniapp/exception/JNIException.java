package com.bj.gxz.jniapp.exception;

/**
 * Created by guxiuzhong@baidu.com on 2020/9/23.
 */
public class JNIException {
    static {
        System.loadLibrary("native-lib");
    }

    public native void nativeInvokeJavaException();

    public native void nativeThrowException() throws Exception;

    public int getStingLen() {
        String s = null;
        return s.length();
    }
}