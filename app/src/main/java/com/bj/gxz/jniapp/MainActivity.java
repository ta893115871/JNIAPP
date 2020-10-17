package com.bj.gxz.jniapp;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.bj.gxz.jniapp.cb.INativeListener;
import com.bj.gxz.jniapp.cb.INativeThreadListener;
import com.bj.gxz.jniapp.cb.JNIThreadCallBack;
import com.bj.gxz.jniapp.crash.JNICrash;
import com.bj.gxz.jniapp.exception.JNIException;
import com.bj.gxz.jniapp.ref.JNIRef;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "JNI";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onMethodDynamic(View view) {
        JNIMethodDynamic jniMethodDynamic = new JNIMethodDynamic();
        Log.d(TAG, "stringFromJNI:" + jniMethodDynamic.stringFromJNI());
        Log.d(TAG, "sum:" + jniMethodDynamic.sum(1, 2));
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

    public void onJniException(View view) {
        JNIException jniException = new JNIException();
        jniException.nativeInvokeJavaException();
        try {
            jniException.nativeThrowException();
        } catch (Exception e) {
            e.printStackTrace();
            Log.e(TAG, "nativeThrowException Exception:", e);
        }
    }


    public void onJniCrash(View view) {
        new JNICrash().crash();
    }

    private JNIRef jniRef = new JNIRef();

    public void onJniRef(View view) {
        String s = jniRef.jnilocalRef();
        Log.e(TAG, "jnilocalRef=" + s);

        String ret1 = jniRef.jniGlobalRef();
        Log.e(TAG, "jniGlobalRef=" + ret1);
        String ret2 = jniRef.jniGlobalRef();
        Log.e(TAG, "jniGlobalRef=" + ret2);
        jniRef.delGlobalRef();

        String ret3 = jniRef.jniWeakGlobalRef();
        Log.e(TAG, "jniWeakGlobalRef=" + ret3);
        String ret4 = jniRef.jniWeakGlobalRef();
        Log.e(TAG, "jniWeakGlobalRef=" + ret4);
        jniRef.delWeakGlobalRef();

        jniRef.localRefOverflow();
        jniRef.refSame();

        String ret5 = jniRef.refCache();
        Log.e(TAG, "refCache=" + ret5);
        String ret6 = jniRef.refCache();
        Log.e(TAG, "refCache=" + ret6);
        jniRef.delRefCache();
    }


}
