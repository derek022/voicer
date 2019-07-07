package com.derek.voicerchange;

/**
 * 音效管理类
 * Created by J.C. on 07/07/2019.
 */

public class EffectUtil {
    static {
        System.loadLibrary("fmodL");
        System.loadLibrary("fmod");

        System.loadLibrary("voice");
    }

    public static final int FMOD_NROMAL = 0;
    public static final int FMOD_LUOLI = 1;
    public static final int FMOD_DASHU = 2;
    public static final int FMOD_KONGLING = 3;
    public static final int FMOD_GAOGUAI = 4;

    public native static void fix_sound(String path,int model);
}
