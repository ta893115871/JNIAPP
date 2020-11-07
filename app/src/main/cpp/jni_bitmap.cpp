//
// Created by Gu,Xiuzhong on 2020/9/24.
//

#include "BitmapUtil.h"

extern "C"
JNIEXPORT jint
JNICALL
Java_com_bj_gxz_jniapp_bitmap_JNIBitmap_gray(JNIEnv *env, jobject thiz, jobject bitmap) {
    auto *bitmapUtil = new BitmapUtil;
    int ret = bitmapUtil->gray(env, bitmap);
    delete bitmapUtil;
    return ret;
}

extern "C"
JNIEXPORT jint
JNICALL
Java_com_bj_gxz_jniapp_bitmap_JNIBitmap_blackAndWhite(JNIEnv *env, jobject thiz, jobject bitmap) {
    auto *bitmapUtil = new BitmapUtil;
    int ret = bitmapUtil->blackAndWhite(env, bitmap);
    delete bitmapUtil;
    return ret;
}

extern "C"
JNIEXPORT jint
JNICALL
Java_com_bj_gxz_jniapp_bitmap_JNIBitmap_negative(JNIEnv *env, jobject thiz, jobject bitmap) {
    auto *bitmapUtil = new BitmapUtil;
    int ret = bitmapUtil->negative(env, bitmap);
    delete bitmapUtil;
    return ret;
}

extern "C"
JNIEXPORT jobject
JNICALL
Java_com_bj_gxz_jniapp_bitmap_JNIBitmap_leftRight(JNIEnv *env, jobject thiz, jobject bitmap) {

    auto bitmapUtil = new BitmapUtil;
    jobject obj = bitmapUtil->leftRight(env, bitmap);
    delete bitmapUtil;
    return obj;
}
