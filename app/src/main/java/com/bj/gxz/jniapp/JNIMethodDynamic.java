package com.bj.gxz.jniapp;


/**
 * Created by guxiuzhong on 2020/9/18.
 */
public class JNIMethodDynamic {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int sum(int x, int y);

}
