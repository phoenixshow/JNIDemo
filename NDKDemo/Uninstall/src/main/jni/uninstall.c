//
// Created by flashing on 2017/4/2.
//
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <unistd.h>
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

void Java_com_phoenix_uninstall_MainActivity_uninstallListener(JNIEnv *env, jobject instance, jstring packName, jint sdkVersion){
    //返回三个值，>0是父进程id，=0是子进程id，<0是出错了
    int code = fork();
    if(code == 0){
        //判断软件是否被卸载
        LOGE("--------------->child==%d", code);
        int flag = 1;
        while (flag){
            LOGE("--------------->进入循环");
            sleep(1);
            char* pName = _JString2CStr(env, packName);
            //FILE *fopen(const char *, const char *);
            FILE* file = fopen(pName,"r");//"/data/data/包名"
            if(file == NULL){
                LOGE("--------------->file == NULL");
                //应用对应的包名文件夹不存在, 说明已经被卸载了
                if(sdkVersion < 17){
                    LOGE("--------------->sdkVersion < 17");
                    execlp("am", "am", "start", "-a", "android.intent.action.VIEW", "-d", "http://www.baidu.com", NULL);
                } else {
                    LOGE("--------------->sdkVersion >= 17");
                    execlp("am", "am", "start", "--user", "0", "-a","android.intent.action.VIEW", "-d","http://www.baidu.com", (char*) NULL);
                }
                flag = 0;//停止循环
                LOGE("--------------->停止循环");
            } else{
                LOGE("--------------->file != NULL");
            }
        }
    } else if(code > 0){
        //父进程
        LOGE("--------------->father==%d", code);
    } else{
        //出错了
        LOGE("--------------->error==%d", code);
    }
}