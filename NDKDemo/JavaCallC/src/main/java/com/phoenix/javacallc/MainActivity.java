package com.phoenix.javacallc;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private TextView tv;
    private JNI jni;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tv = (TextView) findViewById(R.id.tv);
        jni = new JNI();
    }

    public void add(View view) {
        int result = jni.add(99, 1);
        tv.append(result+"\n");
    }

    public void string(View view) {
        String result = jni.sayHello("I am from java");
        tv.append(result+"\n");
    }

    public void array(View view) {
        int[] array = {1, 2, 3, 4, 5};
        //直接修改内存中的值，不需要返回值
        jni.increaseArrayEles(array);
        for (int i=0; i<array.length; i++){
            tv.append("array["+i+"]"+"="+array[i]+"\n");
        }
    }

    public void checkpw(View view) {
        int result = jni.checkPwd("123456");
        tv.append(result+"\n");
    }
}
