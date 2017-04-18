//
// C调用Java
//
#include "com_phoenix_ccalljava_JNI.h"
#include <android/log.h>

#define TAG    "TAG" // 自定义的LOG的标识
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型日志

/**
 * 让C代码调用Java中JNI类的add方法
 */
JNIEXPORT void JNICALL Java_com_phoenix_ccalljava_JNI_callbackAdd
(JNIEnv* env, jobject jobj){
    //1、得到字节码
    //jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jclazz = (*env)->FindClass(env, "com/phoenix/ccalljava/JNI");//复制全类名，把.改为/，因为Linux的路径用/来表示
    //2、得到方法
    //jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    //参数：3方法名，4方法签名
    jmethodID jmethodIDs = (*env)->GetMethodID(env, jclazz, "add", "(II)I");
    //3、实例化该类
    //jobject     (*AllocObject)(JNIEnv*, jclass);
    jobject jobject = (*env)->AllocObject(env, jclazz);
    //4、调用方法
    //jint        (*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
    //最后是可变参数，传入两个加数
    jint value = (*env)->CallIntMethod(env, jobject, jmethodIDs, 99, 1);
    //成功调用了public int add(int x, int y)
    LOGE("value==%d", value);
}

/**
 * 让C代码调用Java中JNI类的helloFromJava方法
 */
JNIEXPORT void JNICALL Java_com_phoenix_ccalljava_JNI_callbackHelloFromJava
(JNIEnv* env, jobject jobj){
    //1、得到字节码
    //jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jclazz = (*env)->FindClass(env, "com/phoenix/ccalljava/JNI");//复制全类名，把.改为/，因为Linux的路径用/来表示
    //2、得到方法
    //jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    //参数：3方法名，4方法签名
    jmethodID jmethodIDs = (*env)->GetMethodID(env, jclazz, "helloFromJava", "()V");
    //3、实例化该类
    //jobject     (*AllocObject)(JNIEnv*, jclass);
    jobject jobject = (*env)->AllocObject(env, jclazz);
    //4、调用方法
    //void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
    (*env)->CallVoidMethod(env, jobject, jmethodIDs);
    //成功调用了public void helloFromJava()
}

/**
 * 让C代码调用Java中JNI类的printString方法
 */
JNIEXPORT void JNICALL Java_com_phoenix_ccalljava_JNI_callbackPrintString
(JNIEnv* env, jobject jobj){
    //1、得到字节码
    //jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jclazz = (*env)->FindClass(env, "com/phoenix/ccalljava/JNI");//复制全类名，把.改为/，因为Linux的路径用/来表示
    //2、得到方法
    //jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    //参数：3方法名，4方法签名
    jmethodID jmethodIDs = (*env)->GetMethodID(env, jclazz, "printString", "(Ljava/lang/String;)V");
    //3、实例化该类
    //jobject     (*AllocObject)(JNIEnv*, jclass);
    jobject jobject = (*env)->AllocObject(env, jclazz);
    //4、调用方法
    //jstring     (*NewStringUTF)(JNIEnv*, const char*);
//    jstring jst = (**env).NewStringUTF(env, "I am phoenix!!!");
    jstring jst = (*env)->NewStringUTF(env, "I am phoenix!!!");//效果同上
    //void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
    (*env)->CallVoidMethod(env, jobject, jmethodIDs, jst);
    //成功调用了public void printString(String s)
}

JNIEXPORT void JNICALL Java_com_phoenix_ccalljava_JNI_callbackSayHello
(JNIEnv* env, jobject jobj){
    //1、得到字节码
    //jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jclazz = (*env)->FindClass(env, "com/phoenix/ccalljava/JNI");//复制全类名，把.改为/，因为Linux的路径用/来表示
    //2、得到方法
    //jmethodID   (*GetStaticMethodID)(JNIEnv*, jclass, const char*, const char*);
    //参数：3方法名，4方法签名
    jmethodID jmethodIDs = (*env)->GetStaticMethodID(env, jclazz, "sayHello", "(Ljava/lang/String;)V");
    //3、调用方法
    jstring jst = (*env)->NewStringUTF(env, "I am phoenixshow.");
    //void        (*CallStaticVoidMethod)(JNIEnv*, jclass, jmethodID, ...);
    (*env)->CallStaticVoidMethod(env, jclazz, jmethodIDs, jst);
    //成功调用了public static void sayHello(String s)
}

/**
 * @param instance 谁调用了当前方法对应的Java接口（即native方法）就是谁的实例，当前是MainActivity.this
 */
void Java_com_phoenix_ccalljava_MainActivity_callbackShowToast(JNIEnv* env, jobject instance){
    //1、得到字节码
    //jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jclazz = (*env)->FindClass(env, "com/phoenix/ccalljava/MainActivity");//复制全类名，把.改为/，因为Linux的路径用/来表示
    //2、得到方法
    //jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    //参数：3方法名，4方法签名
    jmethodID jmethodIDs = (*env)->GetMethodID(env, jclazz, "showToast", "()V");
//    //3、实例化该类
//    //jobject     (*AllocObject)(JNIEnv*, jclass);
//    jobject jobj = (*env)->AllocObject(env, jclazz);
    //4、调用方法
    //void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
//    (*env)->CallVoidMethod(env, jobj, jmethodIDs);
    (*env)->CallVoidMethod(env, instance, jmethodIDs);
    //成功调用了public void showToast()
}