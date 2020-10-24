package com.bj.gxz.jniapp.methodfield;

/**
 * Created by guxiuzhong@baidu.com on 2020/10/24.
 */
public class JNIMethodField {

    static {
        System.loadLibrary("native-lib");
    }

    public native void getAppInfoFromJava(AppInfo appInfo);

    public native AppInfo createAppInfoFromJni();
}
