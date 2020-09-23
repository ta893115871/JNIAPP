//
// Created by Gu,Xiuzhong on 2020/9/21.
//

#ifndef JNIAPP_COMMON_H
#define JNIAPP_COMMON_H

#include <jni.h>
#include <string>
#include <android/log.h>
#include <pthread.h>
#include <stdio.h>

#define LOG_TAG "JNI"
#define LOG_D(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOG_E(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#endif //JNIAPP_COMMON_H
