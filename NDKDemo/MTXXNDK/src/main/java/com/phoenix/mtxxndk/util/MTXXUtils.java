package com.phoenix.mtxxndk.util;

import android.graphics.Bitmap;
import android.graphics.Color;

import com.phoenix.mtxxndk.jni.MTXXJNI;

/**
 * 美图秀秀的核心处理功能类
 * Java进行处理图像，如何美白
 * NDK如何进行美白处理
 */
public final class MTXXUtils {
    //调配亮度和对比度
    //需要定义两个参数，一是代表的亮度，二是对比度
    private static float brightnessFactor = 0.2f, contrastFactor = 0.2f;

    //获得Java版本的白富美
    public static Bitmap getJavaWhiteRichBeauty(Bitmap bitmap){
        //进入图像处理，所有的图像其实都是一系列的像素组成
        //图像的宽和高
        int width = 0, height = 0;
        width = bitmap.getWidth();
        height = bitmap.getHeight();
        //定义一个处理后的图像//基于三原色来创建一个图像
        Bitmap dest = Bitmap.createBitmap(width, height, Bitmap.Config.RGB_565);
        //定义三原色
        int r,g,b;
        //美白开始
        //增加亮度
        int bfi = (int)(brightnessFactor * 255);
        //对比度
        float cf = 1f + contrastFactor;
        cf *= cf;//对比度产生了1.44倍的变化
        //2的15次方——32768 2的16次方——65536——16位色 32位真彩色
        //对比度指数
        int cfi = (int)(cf * 65536)+1;
        for (int x = 0; x < width; x++){
            for (int y = 0; y < height; y++) {
                int color = bitmap.getPixel(x, y);
                //获取红色素
                r = Color.red(color);
                g = Color.green(color);
                b = Color.blue(color);
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
                //设置到目标图像
                dest.setPixel(x, y, Color.rgb(r, g, b));
            }
        }
        return dest;
    }

    public static Bitmap getNDKWhiteRichBeauty(Bitmap bitmap) {
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();
        int[] buff = new int[width*height];
        //成功地将bitmap复制到了result
        //bitmap把像素拿出来放到buff中，从0开始，间距是width（必须> = bitmap的宽度），(1,1)是左上角的点，(width-1,height-1)是右下角的点，这里留了边框的1像素
//        bitmap.getPixels(buff, 0, width, 1, 1, width-1, height-1);
        bitmap.getPixels(buff, 0, width, 0, 0, width, height);
        int[] result = MTXXJNI.getNDKWhiteRichBeauty(buff, width, height);
        Bitmap dealBitmap = Bitmap.createBitmap(result, width, height, Bitmap.Config.RGB_565);
        return dealBitmap;
    }
}
