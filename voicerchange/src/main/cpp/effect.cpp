//
// Created by J.C. on 07/07/2019.
//

#include <stdlib.h>
#include "com_derek_voicerchange_EffectUtil.h"
#include "inc/fmod.hpp"
#include <unistd.h>
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,"derek",__VA_ARGS__)

#define FMOD_NROMAL 0L
#define FMOD_LUOLI 1L
#define FMOD_DASU 2L
#define FMOD_KONGLING 3L
#define FMOD_GAOGUAI 4L

using  namespace FMOD;

JNIEXPORT void JNICALL Java_com_derek_voicerchange_EffectUtil_fix_1sound
        (JNIEnv * env, jclass jcls, jstring path_jstr, jint model){
    const char* path = env->GetStringUTFChars(path_jstr,NULL);

    FMOD::System       *system        = 0;
    Channel * channel;
    Sound * sound;
    FMOD::DSP          *dsplowpass    = 0;
    float  frequency = 0;  //速度

    bool  isPlaying = true;

    System_Create(&system);

    system->init(32,FMOD_INIT_NORMAL,NULL);
    system->createSound(path,FMOD_NROMAL,NULL,&sound);


    switch (model){
        case FMOD_NROMAL:
            system->playSound(sound,0, false,&channel);
            break;
        case FMOD_LUOLI:
            //dsp digital signal process
            //dsp 音效
            //FMOD_DSP_PITCHSHIFT_PITCH dsp 提升或者降低音调用的一种音效
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsplowpass);
            dsplowpass->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,2.5);

            system->playSound(sound,0, false,&channel);
            //设置音调的参数
            channel->addDSP(0,dsplowpass);
            LOGI("fix luoji");

            break;
        case FMOD_DASU:
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsplowpass);
            dsplowpass->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,0.8);

            system->playSound(sound, 0, false, &channel);
            //添加到channel
            channel->addDSP(0,dsplowpass);
            LOGI("%s","fix dashu");
            break;
        case FMOD_KONGLING:
            system->createDSPByType(FMOD_DSP_TYPE_ECHO,&dsplowpass);
            dsplowpass->setParameterFloat(FMOD_DSP_ECHO_DELAY,300);
            dsplowpass->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK,20);
            system->playSound(sound, 0, false, &channel);
            channel->addDSP(0,dsplowpass);
            LOGI("%s","fix kongling");
            break;
        case FMOD_GAOGUAI:
            system->playSound(sound, 0, false, &channel);
            channel->getFrequency(&frequency);
            frequency = 2 * frequency;
            channel->setFrequency(frequency);

            break;
        default:
            break;
    }

    system->update();

    while (isPlaying){
        channel->isPlaying(&isPlaying);
        usleep(1000*1000);
    }

    sound->release();
    system->close();
    system->release();

    env->ReleaseStringUTFChars(path_jstr,path);
}