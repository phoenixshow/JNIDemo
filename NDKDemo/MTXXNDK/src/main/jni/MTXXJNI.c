//
// Created by flashing on 2017/4/4.
//
#include <android/bitmap.h>
#include "ImageArgb.h"

jintArray Java_com_phoenix_mtxxndk_jni_MTXXJNI_getNDKWhiteRichBeauty
        (JNIEnv* env, jclass clz, jintArray buff, jint w, jint h){
    //定义一个亮度和对比度
    float brightnessFactor = 0.2f, contrastFactor = 0.2f;
    //定义一个int型的指针，指向我们从Android环境传递下来的图像，指向第0个元素，这样可以操作所有的图像像素
    jint *source = (*env)->GetIntArrayElements(env, buff, 0);
    //定义图像尺寸大小
    int newSize = w * h;
    //定义一个数组，用来存储新的图片
    jint dest[newSize];

    //定义三原色和透明度
    int r,g,b,a;
    //美白开始
    //增加亮度
    int bfi = (int)(brightnessFactor * 255);
    //对比度
    float cf = 1.0f + contrastFactor;
    cf *= cf;//对比度产生了1.44倍的变化
    //2的15次方——32768 2的16次方——65536——16位色 32位真彩色
    //对比度指数
    int cfi = (int)(cf * 65536)+1;
    int x = 0, y = 0;
    for (x = 0; x < w; x++){
        for (y = 0; y < h; y++) {
            int color = source[y*w+x];//第几行*每行几个+第几列
            //获取红色素
            r = red(color);
            g = green(color);
            b = blue(color);
            a = alpha(color);
            //修改亮度
            int ri = r + bfi;
            int gi = g + bfi;
            int bi = b + bfi;
            //防止 r g b 三原色超出我们的0~255的范围
            r = ri>255 ? 255 : (ri<0 ? 0 : ri);
            g = gi>255 ? 255 : (gi<0 ? 0 : gi);
            b = bi>255 ? 255 : (bi<0 ? 0 : bi);

            //修改对比度 范围-128~127
            //偏移保证在正确范围
            ri = r - 128;
            gi = g - 128;
            bi = b - 128;
            //增加对比度 图像学的专业技术，不能超过正常范围，所以用位移运算
            ri = (ri*cfi)>>16;// >>16 相当于 /65536 ，但速度较快
            gi = (gi*cfi)>>16;
            bi = (bi*cfi)>>16;
            //重新偏移到0~255这个范围
            ri = ri + 128;
            gi = gi + 128;
            bi = bi + 128;
            //再次防止 r g b 三原色超出我们的0~255的范围
            r = ri>255 ? 255 : (ri<0 ? 0 : ri);
            g = gi>255 ? 255 : (gi<0 ? 0 : gi);
            b = bi>255 ? 255 : (bi<0 ? 0 : bi);
            int destColor = ARGB(a,r,g,b);
            //设置到目标图像
            dest[y*w+x] = destColor;
        }
    }
    //新建一个Java int[]
    jintArray result = (*env)->NewIntArray(env, newSize);
    //数组赋值Copy，拷贝到result中，从0开始，到newSize为止，数据源是dest
    (*env)->SetIntArrayRegion(env, result, 0, newSize, dest);
    //释放内存操作，要释放buff和source，从0开始释放掉
    (*env)->ReleaseIntArrayElements(env, buff, source, 0);
    //将数组返回
    return result;
}