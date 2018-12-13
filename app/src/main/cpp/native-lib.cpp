#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL

Java_com_example_liuhai_jnilib_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    using namespace std;
   string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_liuhai_jnilib_MainActivity_getField(JNIEnv *env, jobject instance) {
    //拿到对象的类
   jclass  clz=env->GetObjectClass(instance);
   //拿到属性的ID  可以通过JAVAP命令查看函数签名
    jfieldID fid= env->GetFieldID(clz,"abc","Ljava/lang/String;");
    jstring fild= static_cast<jstring>(env->GetObjectField(instance, fid));
    //把JSTRING转成C++类型的String
    const char* result=env->GetStringUTFChars(fild,NULL);
    strcat(const_cast<char *>(result), "哈哈哈哈");
    jstring  myresult=env->NewStringUTF(result);
    env->SetObjectField(instance,fid,myresult);
    return myresult;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_liuhai_jnilib_MainActivity_getStaticField(JNIEnv *env, jobject instance) {

    //获取Clazz
    jclass clz=env->GetObjectClass(instance);
    jfieldID  jfieldID1=env->GetStaticFieldID(clz,"def","Ljava/lang/String;");
    jstring  jstring1= static_cast<jstring>(env->GetStaticObjectField(clz, jfieldID1));
    //JSTRING转成C++的String 进行操作
            const  char* value=env->GetStringUTFChars(jstring1,NULL);
//            拼接字符串，
        strcat(const_cast<char *>(value), "静态啊哈哈哈");
        //C的字符串转换成Jstring设置
    jstring  result=env->NewStringUTF(value);
    env->SetStaticObjectField(clz,jfieldID1,result);

    env->Get
    return result;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_liuhai_jnilib_MainActivity_CallMethod(JNIEnv *env, jobject instance) {
     //还是获得CLASS
    jclass  jclass1=env->GetObjectClass(instance);
//    方法ID
    jmethodID jmethodID1=env->GetMethodID(jclass1,"test1","(Ljava/lang/String;)V");
    jstring  value=env->NewStringUTF("来字JNI的非静态方法调用");
//拿到对应的方法
    env->CallVoidMethod(instance,jmethodID1,value);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_liuhai_jnilib_MainActivity_CallStaticMethod(JNIEnv *env, jobject instance) {

    jclass  jclass1=env->GetObjectClass(instance);
    jmethodID  jmethodID1=env->GetStaticMethodID(jclass1,"test2","(v;)v");
    env->CallStaticVoidMethod(jclass1,jmethodID1);



}