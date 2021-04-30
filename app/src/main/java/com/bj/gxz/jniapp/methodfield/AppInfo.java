package com.bj.gxz.jniapp.methodfield;

import java.io.Serializable;

/**
 * Created by guxiuzhong on 2020/10/24.
 */
public class AppInfo implements Serializable {
    private static final String TAG = "AppInfo";
    private String versionName;
    public int versionCode;
    public long size;

    public AppInfo(String versionName) {
        this.versionName = versionName;
    }

    public AppInfo(String versionName, int versionCode) {
        this.versionName = versionName;
        this.versionCode = versionCode;
    }

    public String getVersionName() {
        return versionName;
    }

    public void setVersionName(String versionName) {
        this.versionName = versionName;
    }

    public int getVersionCode() {
        return versionCode;
    }

    public void setVersionCode(int versionCode) {
        this.versionCode = versionCode;
    }

    public void setSize(long size) {
        this.size = size;
    }

    public long getSize() {
        return size;
    }

    @Override
    public String toString() {
        return "AppInfo{" +
                "versionName='" + versionName + '\'' +
                ", versionCode=" + versionCode +
                ", size=" + size +
                '}';
    }
}
