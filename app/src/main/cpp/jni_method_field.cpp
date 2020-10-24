//
// Created by Gu,Xiuzhong on 2020/10/24.
//

#include "common.h"

extern "C" JNIEXPORT void  JNICALL
Java_com_bj_gxz_jniapp_methodfield_JNIMethodField_getAppInfoFromJava(JNIEnv *env, jobject instance,
                                                                     jobject obj) {

    // 根据java对象获取对象对应的class
    jclass cls = env->GetObjectClass(obj);

    // 获取&调用java方法
    jmethodID getVersionName_mid = env->GetMethodID(cls, "getVersionName", "()Ljava/lang/String;");
    jstring versionName = (jstring) env->CallObjectMethod(obj, getVersionName_mid);
    char *c_string = const_cast<char *>(env->GetStringUTFChars(versionName, 0));
    LOG_D("versionName=%s", c_string);

    // 获取java对象的属性值
    jfieldID versionCode_fieldId = env->GetFieldID(cls, "versionCode", "I");
    int versionCode = env->GetIntField(obj, versionCode_fieldId);
    LOG_D("versionCode=%d", versionCode);

    // 获取java对象的属性值
    jfieldID size_fieldId = env->GetFieldID(cls, "size", "J");
    long size = env->GetLongField(obj, size_fieldId);
    LOG_D("size=%ld", size);

    // 获取java静态属性的值
    jfieldID tag_fieldId = env->GetStaticFieldID(cls, "TAG", "Ljava/lang/String;");
    jstring tag_java = (jstring) env->GetStaticObjectField(cls, tag_fieldId);
    char *tag_c_string = const_cast<char *>(env->GetStringUTFChars(tag_java, 0));
    LOG_D("TAG=%s", tag_c_string);

    // 释放局部引用
    env->DeleteLocalRef(cls);
    env->ReleaseStringUTFChars(versionName, c_string);
    env->ReleaseStringUTFChars(tag_java, tag_c_string);
}


extern "C" JNIEXPORT jobject JNICALL
Java_com_bj_gxz_jniapp_methodfield_JNIMethodField_createAppInfoFromJni(JNIEnv *env,
                                                                       jobject instance) {

    // 获取java的class
    jclass cls = env->FindClass("com/bj/gxz/jniapp/methodfield/AppInfo");

    // 创建java对象，就是调用构造方法，构造方法的方法签名固定为<init>
    jmethodID mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
    jobject obj = env->NewObject(cls, mid, env->NewStringUTF("com.gxz.com"));

    // 给定方法名字和签名，调用方法
    jmethodID setVersionCode_mid = env->GetMethodID(cls, "setVersionCode", "(I)V");
    env->CallVoidMethod(obj, setVersionCode_mid, 1);

    // 给定属性名字和签名，设置属性的值
    jfieldID size_field_id = env->GetFieldID(cls, "size", "J");
    env->SetLongField(obj, size_field_id, (jlong) 1000);

    // 释放局部引用
    env->DeleteLocalRef(cls);
    return obj;
}