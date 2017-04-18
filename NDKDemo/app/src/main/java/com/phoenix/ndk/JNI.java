package com.phoenix.ndk;

/**
 * Created by flashing on 2017/3/26.
 */

public class JNI {
    static {
        System.loadLibrary("Hello");
    }

    /**
     * 定义native方法
     * 调用C代码对应的方法
     * @return
     */
    public native String sayHello();
}
