//
// 加法计算
//
#include "com_phoenix_javacallc_JNI.h"
#include <string.h>
#include <android/log.h>

#define TAG    "TAG" // 自定义的LOG的标识
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型日志

/**
 * 把一个jstring转换成一个C语言的char*类型
 */
char* _JString2CStr(JNIEnv* env, jstring jstr){
    char* rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env, "GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray)(*env)->CallObjectMethod(env, jstr, mid, strencode); // String .getByte("GB2312");
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if(alen > 0){
        rtn = (char*)malloc(alen+1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen]=0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba, 0);
    return rtn;
}

//从头文件拷入函数声明，JNIEXPORT、JNICALL可以删除不要
/**
 * 加法计算
 * @return jint
 */
jint Java_com_phoenix_javacallc_JNI_add
        (JNIEnv* env, jobject jobj, jint ji, jint jj){
    int result = ji + jj;
    return result;
}

/**
 * 字符串累加
 */
JNIEXPORT jstring JNICALL Java_com_phoenix_javacallc_JNI_sayHello
        (JNIEnv* env, jobject jobj, jstring jstr){
    char* fromJava = _JString2CStr(env, jstr);
    char* fromC = " add I am from C";

    //拼接函数strcat
    strcat(fromJava, fromC);//把拼接的结果放在第一个参数里面

    //调用jstring     (*NewStringUTF)(JNIEnv*, const char*);方法
    //将char*转换为jstring并返回
    return (*env)->NewStringUTF(env, fromJava);
}

/**
 * 给每个数组元素都加10
 */
JNIEXPORT jintArray JNICALL Java_com_phoenix_javacallc_JNI_increaseArrayEles
        (JNIEnv* env, jobject jobj, jintArray jarray){
    //1、得到数组的长度
    //jsize       (*GetArrayLength)(JNIEnv*, jarray);
    jsize size = (*env)->GetArrayLength(env, jarray);
    //2、得到数组元素，获取数组指针
    //jint*       (*GetIntArrayElements)(JNIEnv*, jintArray, jboolean*);
    jint* intArray = (*env)->GetIntArrayElements(env, jarray, JNI_FALSE);
    //3、遍历数组，给每个元素加上10
    int i;
    for(i=0; i<size; i++){
//        *(intArray+i) = *(intArray+i) + 10;//可用下面方式简写
        *(intArray+i) += 10;
        LOGE("*(intArray+%d)的值----->%d", i, *(intArray+i));
    }
    //4.释放资源
    // void (*ReleaseIntArrayElements)(JNIEnv*, jintArray, jint*, jint);
    /*
    该函数与 GetIntArrayElements 函数可以说是对应的。它完成的功能是释放资源和数据更新。
    由于 Java 的垃圾收集具有可能改变内存中对象的位置，如不采取必要措施，被访问的数组指针就可能不再指向正确的存区。
    因此，对于数组，要么把它“钉”在固定的存区，要么把它拷贝至固定的存区，总之在访问它的期间要使数组元素总在原地。
    作完操作之后，再调用这个函数，解除对它的固定。另外，在调用这个函数之前，所有更新都没有作用在数组本身上。
    第三个参数就是决定更新与否的。
    取值 零(0) 时，更新数组并释放所有元素;
    取值 JNI_COMMIT 时，更新但不释放所有元素; //#define JNI_COMMIT 1 // copy content, do not free buffer
    取值 JNI_ABORT 时，不作更新但释放所有元素；//#define JNI_ABORT  2 // free buffer w/o copying back
     */
    (*env)->ReleaseIntArrayElements( env, jarray, intArray, JNI_COMMIT );
    //5、返回结果
    return jarray;
}

/**
 * 比较字符串是否相同
 */
JNIEXPORT jint JNICALL Java_com_phoenix_javacallc_JNI_checkPwd
        (JNIEnv* env, jobject jobj, jstring jstr){
    //服务器的密码是123456
    char* origin = "123456";
    char* fromUser = _JString2CStr(env, jstr);
    //函数比较字符串是否相同
    int code = strcmp(origin, fromUser);
    if(code == 0){
        return 200;
    } else {
        return 400;
    }
}