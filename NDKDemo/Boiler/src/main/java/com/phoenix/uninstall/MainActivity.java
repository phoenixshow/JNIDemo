package com.phoenix.uninstall;

import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("Boiler");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        final PressureView pressureView = new PressureView(this);
        setContentView(pressureView);
        new Thread(){
            @Override
            public void run() {
                super.run();
                while (true) {
                    SystemClock.sleep(500);
                    int pressure = Math.abs(getPressure());//0~250//这个值有可能为负值，所以取绝对值
                    pressureView.setPressure(pressure);
                    if (pressure > 220) {//如果压力大于220就要爆炸
                        break;
                    }
                }
            }
        }.start();
    }

    /**
     * native代码，调用C代码中对应的方法
     * @return
     */
    public native int getPressure();
}
