package com.bj.gxz.jniapp;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.bj.gxz.jniapp.cb.INativeListener;
import com.bj.gxz.jniapp.cb.INativeThreadListener;
import com.bj.gxz.jniapp.cb.JNIThreadCallBack;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "JNI";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onMethodDynamic(View view) {
//        JNIMethodDynamic jniMethodDynamic = new JNIMethodDynamic();
//        Log.d(TAG, "stringFromJNI:" + jniMethodDynamic.stringFromJNI());
//        Log.d(TAG, "sum:" + jniMethodDynamic.sum(1, 2));
    }

    public void onMethodCallBack(View view) {
        JNIThreadCallBack jniThreadCallBack = new JNIThreadCallBack();
        jniThreadCallBack.nativeCallBack(new INativeListener() {
            @Override
            public void onCall() {
                Log.d(TAG, "onCall invoked,threadName:" + Thread.currentThread().getName());
            }
        });
        jniThreadCallBack.nativeInThreadCallBack(new INativeThreadListener() {
            @Override
            public void onSuccess(String msg) {
                Log.d(TAG, "onSuccess invoked,msg:" + msg);
                Log.d(TAG, "onSuccess invoked,threadName:" + Thread.currentThread().getName());
            }
        });
    }
}
