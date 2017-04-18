package com.phoenix.mtxxndk;

import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;

import com.phoenix.mtxxndk.jni.MTXXJNI;
import com.phoenix.mtxxndk.util.MTXXUtils;

public class MainActivity extends AppCompatActivity {
    private ImageView ivPicture;
    private Bitmap bitmap;
    private static final String TAG = "MTXX";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();
    }

    private void initView(){
        ivPicture = (ImageView) findViewById(R.id.iv_picture);
        //将原图存储起来
        BitmapDrawable drawable = (BitmapDrawable)ivPicture.getDrawable();
        bitmap = drawable.getBitmap();
    }

    public void reset(View view) {
        ivPicture.setImageBitmap(bitmap);
    }

    public void java(View view) {
        long startTime = System.currentTimeMillis();
        Bitmap jBitmap = MTXXUtils.getJavaWhiteRichBeauty(bitmap);
        ivPicture.setImageBitmap(jBitmap);
        long endTime = System.currentTimeMillis();
        Log.e(TAG, "Java操作耗时"+(endTime-startTime));
    }

    public void ndk(View view) {
        long startTime = System.currentTimeMillis();
        Bitmap jBitmap = MTXXUtils.getNDKWhiteRichBeauty(bitmap);
        ivPicture.setImageBitmap(jBitmap);
        long endTime = System.currentTimeMillis();
        Log.e(TAG, "NDK操作耗时"+(endTime-startTime));
    }
}
