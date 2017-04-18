//
// Created by flashing on 2017/3/26.
//
#include <stdio.h>
#include <jni.h>

/**
 * Java_全类名_方法名
 * @param env JNIEnv*是结构体JNINativeInterface的二级指针，相当于环境变量，里面有很多方法可供调用
 * @param jobj 谁调用了这个方法就是谁的实例，当前就是Java类的JNI.this
 * @return jstring
 */
jstring Java_com_phoenix_ndk_JNI_sayHello(JNIEnv* env, jobject jobj){
    //jstring     (*NewStringUTF)(JNIEnv*, const char*);
    char* text = "I am from C";
    return (*env)->NewStringUTF(env, text);
}