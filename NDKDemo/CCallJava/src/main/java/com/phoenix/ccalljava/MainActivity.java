package com.phoenix.ccalljava;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private JNI jni;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jni = new JNI();
    }

    public void onClick(View view) {
//        jni.callbackAdd();
//        jni.helloFromJava();
//        jni.callbackPrintString();
//        jni.callbackSayHello();

//        jni.callbackShowToast();//通过反射的方式实例化的MainActivity是new出来的，这样它就不是上下文了，这样当我们Toast使用上下文的时候就会报空指针异常
        MainActivity.this.callbackShowToast();
    }

    public void showToast(){
        Log.e("TAG", "showToast------------->");
        Toast.makeText(this, "showToast------------->", Toast.LENGTH_LONG).show();
    }

    public native void callbackShowToast();//让C代码调用MainActivity里面的showToast()方法
}
