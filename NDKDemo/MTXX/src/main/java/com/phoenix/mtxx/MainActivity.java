package com.phoenix.mtxx;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import com.mt.mtxx.image.JNI;

public class MainActivity extends AppCompatActivity {
    private JNI jni;
    private ImageView iv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jni = new JNI();
        iv = (ImageView) findViewById(R.id.iv_icon);
    }

    //高亮
    public void lomoHDR(View view) {
        //把图片转换成数组
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.girl);
        //装图片的像素//数组长度就是图片的宽*高
        int[] pixels = new int[bitmap.getWidth()*bitmap.getHeight()];
        /**
         * 《Bitmap 之 getPixels() 的 stride》
         * http://blog.csdn.net/ithomer/article/details/7308805
         * 参数
         * pixels    接收位图颜色值的数组
         * offset    写入到pixels[]中的第一个像素索引值
         * stride    pixels[]中的行间距个数值(必须大于等于位图宽度)。可以为负数
         * x         从位图中读取的第一个像素的x坐标值。左上角为原点，所以这里是0
         * y         从位图中读取的第一个像素的y坐标值。左上角为原点，所以这里是0
         * width     从每一行中读取的像素宽度
         * height    读取的行数
         */
        bitmap.getPixels(pixels, 0, bitmap.getWidth(), 0, 0, bitmap.getWidth(), bitmap.getHeight());
        //把数组传入给C代码处理
        jni.StyleLomoHDR(pixels, bitmap.getWidth(), bitmap.getHeight());
        //把处理好的数组重新生成图片
        bitmap = Bitmap.createBitmap(pixels, bitmap.getWidth(), bitmap.getHeight(), Bitmap.Config.ARGB_8888);
        //把图片像素显示
        iv.setImageBitmap(bitmap);
    }

    //黑白
    public void lomoC(View view) {
        //把图片转换成数组
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.girl);
        //装图片的像素//数组长度就是图片的宽*高
        int[] pixels = new int[bitmap.getWidth()*bitmap.getHeight()];
        bitmap.getPixels(pixels, 0, bitmap.getWidth(), 0, 0, bitmap.getWidth(), bitmap.getHeight());
        //把数组传入给C代码处理
        jni.StyleLomoC(pixels, bitmap.getWidth(), bitmap.getHeight());
        //把处理好的数组重新生成图片
        bitmap = Bitmap.createBitmap(pixels, bitmap.getWidth(), bitmap.getHeight(), Bitmap.Config.ARGB_8888);
        //把图片像素显示
        iv.setImageBitmap(bitmap);
    }

    //怀旧
    public void lomoB(View view) {
        //把图片转换成数组
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.girl);
        //装图片的像素//数组长度就是图片的宽*高
        int[] pixels = new int[bitmap.getWidth()*bitmap.getHeight()];
        bitmap.getPixels(pixels, 0, bitmap.getWidth(), 0, 0, bitmap.getWidth(), bitmap.getHeight());
        //把数组传入给C代码处理
        jni.StyleLomoB(pixels, bitmap.getWidth(), bitmap.getHeight());
        //把处理好的数组重新生成图片
        bitmap = Bitmap.createBitmap(pixels, bitmap.getWidth(), bitmap.getHeight(), Bitmap.Config.ARGB_8888);
        //把图片像素显示
        iv.setImageBitmap(bitmap);
    }

    //还原
    public void reset(View view) {
        iv.setImageResource(R.drawable.girl);
    }
}
