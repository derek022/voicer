package com.derek.voicerchange;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import org.fmod.FMOD;

import java.util.logging.LogRecord;

public class MainActivity extends AppCompatActivity {

    public static String path ;
    private static Handler mHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        FMOD.init(getApplicationContext());
        path = "file:///android_asset/singing.wav";

        new VoiceThread().start();

    }


    @Override
    protected void onDestroy()
    {

        org.fmod.FMOD.close();

        super.onDestroy();
    }

    public void mClickVoice(View v){
        Message msg = new Message();
        switch (v.getId()){
            case R.id.normal:
                msg.what = EffectUtil.FMOD_NROMAL;
                break;
            case R.id.luoli:
                msg.what = EffectUtil.FMOD_LUOLI ;
                break;
            case R.id.dashu:
                msg.what = EffectUtil.FMOD_DASHU;
                break;
            case R.id.kongling:
                msg.what = EffectUtil.FMOD_KONGLING;
                break;
            case R.id.gaoguai:
                msg.what = EffectUtil.FMOD_GAOGUAI;
                break;
        }
        mHandler.dispatchMessage(msg);
    }

    class VoiceThread extends  Thread {

        @Override
        public void run() {
            super.run();
            Looper.prepare();
            mHandler = new Handler() {
                @Override
                public void handleMessage(Message msg) {
                    EffectUtil.fix_sound(path,msg.what);
                }
            };

            Looper.loop();
        }
    }


}
