//
// Created by Gu,Xiuzhong on 2020/9/24.
//

#ifndef JNIAPP_BITMAPUTIL_H
#define JNIAPP_BITMAPUTIL_H

#include "common.h"
#include <android/bitmap.h>

class BitmapUtil {
public:
    int gray(JNIEnv *env, jobject bitmap);
    int blackAndWhite(JNIEnv *env, jobject bitmap);
    int negative(JNIEnv *env, jobject bitmap);
    jobject leftRight(JNIEnv *env, jobject bitmap);
};


#endif //JNIAPP_BITMAPUTIL_H
