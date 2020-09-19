package com.bj.gxz.jniapp;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private JNIMethodDynamic jniMethodDynamic = new JNIMethodDynamic();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.sample_text);
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.d("jni", "stringFromJNI:" + jniMethodDynamic.stringFromJNI());
                Log.d("jni", "sum:" + jniMethodDynamic.sum(1, 2));
            }
        });
    }
}
