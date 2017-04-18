package com.phoenix.uninstall;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.View;

/**
 * Created by flashing on 2017/4/2.
 */

public class PressureView extends View {
    //锅炉压力值
    private int pressure;
    private Paint paint;

    public PressureView(Context context) {
        super(context);
        paint = new Paint();
        paint.setAntiAlias(true);//设置抗锯齿
        paint.setTextSize(25);
    }

    public void setPressure(int pressure) {
        this.pressure = pressure;
//        invalidate();//在主线程中调用//由于在MainActivity开了子线程，所以不能使用这种方式
        postInvalidate();//onDraw()执行
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        int x = (getWidth()-50)/2;
        int y = (getHeight()-250)/2;
        if (pressure > 220){
            //1、如果压力值大于220，就绘制文本，显示锅炉爆炸了
            String str = "老铁快跑！！！要爆了！~";
            float strwidth = paint.measureText(str);
            canvas.drawText(str, (getWidth()-strwidth)/2, getHeight()/2, paint);
        }else {
            //2、正常和提示的情况
            //设置背景颜色为灰色
            paint.setColor(Color.GRAY);
            canvas.drawRect(x, y, x+50, y+250, paint);
            //  2、1 如果是小于200正常显示，并且设置画笔颜色——绿色
            if (pressure < 200){
                paint.setColor(Color.GREEN);
            }
            //  2、2 如果是大于200警示给看护者，并且设置画笔颜色——红色
            else if (pressure >= 200){
                paint.setColor(Color.RED);
            }
            canvas.drawRect(x, y+250-pressure, x+50, y+250, paint);
        }
    }
}
