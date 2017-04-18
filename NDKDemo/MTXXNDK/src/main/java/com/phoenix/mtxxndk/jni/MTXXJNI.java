package com.phoenix.mtxxndk.jni;

/**
 * Created by flashing on 2017/4/3.
 */

public class MTXXJNI {
    static {
        System.loadLibrary("Mtxx");
    }

    /**
     *
     * @param buff 图像的整型数组
     * @param width 宽
     * @param height 高
     * @return
     */
    public native static int[] getNDKWhiteRichBeauty(int[] buff, int width, int height);
}
