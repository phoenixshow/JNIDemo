package com.phoenix.ccalljava;

import android.util.Log;

/**
 * C调用Java代码
 */
public class JNI {
    static {
        System.loadLibrary("CCallJava");
    }

    //通知C调用下面的add方法
    public native void callbackAdd();
    public native void callbackHelloFromJava();
    public native void callbackPrintString();
    public native void callbackSayHello();

    public int add(int x, int y){
        Log.e("TAG", "add() x="+x+" y="+y);
        return x + y;
    }

    public void helloFromJava(){
        Log.e("TAG", "helloFromJava()");
    }

    public void printString(String s){
        Log.e("TAG", "C中输入的："+s);
    }

    public static void sayHello(String s){
        Log.e("TAG", "我是Java代码中的JNI，"+"Java中的sayHello(String s)静态方法，我被C调用了："+s);
    }
}
