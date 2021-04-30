package com.bj.gxz.jniapp.bitmap;

import android.graphics.Bitmap;

/**
 * Created by guxiuzhong on 2020/9/24.
 */
public class JNIBitmap {

    static {
        System.loadLibrary("native-lib");
    }

    public native int blackAndWhite(Bitmap bitmap);
    public native int gray(Bitmap bitmap);
    public native int negative(Bitmap bitmap);
    public native Bitmap leftRight(Bitmap bitmap);
}
