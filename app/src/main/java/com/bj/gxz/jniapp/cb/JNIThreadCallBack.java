package com.bj.gxz.jniapp.cb;


/**
 * Created by guxiuzhong@baidu.com on 2020/9/18.
 */
public class JNIThreadCallBack {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public native void nativeCallBack(INativeListener callBack);

    public native void nativeInThreadCallBack(INativeThreadListener listener);

}