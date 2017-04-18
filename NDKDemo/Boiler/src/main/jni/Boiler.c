//
// Created by flashing on 2017/4/2.
//
#include <jni.h>

/**
 * 得到锅炉的压力值 0~250之间
 */
int pressure = 20;
int getPressure(){
    int increase = rand()%20;
    pressure += increase;
    return pressure;
}

/**
 * 从锅炉感应器中得到锅炉压力值
 * @param env
 * @param instance
 * @return
 */
jint Java_com_phoenix_boiler_MainActivity_getPressure(JNIEnv *env, jobject instance){
    int pressure = getPressure();
    return pressure;
}