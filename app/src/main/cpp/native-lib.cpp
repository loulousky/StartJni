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
    jmethodID  jmethodID1=env->GetStaticMethodID(jclass1,"test2","()V");
    env->CallStaticVoidMethod(jclass1,jmethodID1);



}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_liuhai_jnilib_MainActivity_CallConstructMethod(JNIEnv *env, jobject instance) {
    //Jint数组，转成Jint的指针
    jclass  jclass1=env->FindClass("java/util/Date");
    //构造方法的方法名统一为<init>即可
    jmethodID conmethodi=env->GetMethodID(jclass1,"<init>","()V");
    jobject  date=env->NewObject(jclass1,conmethodi);//调用无参数的构造函数，返回一个对象
    //接下来跟开始调用流程一样了
    jmethodID timeid=env->GetMethodID(jclass1,"getTime","()J");
    //获得了时间戳
    jlong  time=env->CallLongMethod(date,timeid)/1000;
    //返回时间戳
    return env->NewStringUTF(std::to_string(time).c_str());

}
//用来进行比较的函数
int compareMyType (const void * a, const void * b)
{ if ( *(jint*)a <  *(jint *)b ) return -1;
    if ( *(jint*)a == *(jint*)b ) return 0;
    if ( *(jint*)a >  *(jint*)b ) return 1;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_liuhai_jnilib_MainActivity_SortArray(JNIEnv *env, jobject instance, jintArray array_) {
    if(array_==NULL){
        return ;
    }
    //获得数组的大小
   int length= env->GetArrayLength(array_);
    //把jintArry类型转换成C++的int数组指针
            //这里得到的数据跟传进来的数组不是同一个，地址会不一样
    jint *array = env->GetIntArrayElements(array_, NULL);
    qsort(array,length, sizeof(jint),compareMyType);
    //要想应用到JAVA中传入的数组上面，必须使用这个方法映射过去。0的意思的改变JAVA数组，并且释放C中创建数组的内存
    env->ReleaseIntArrayElements(array_, array, 0);
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_liuhai_jnilib_MainActivity_getArray(JNIEnv *env, jobject instance) {
   //创建一个10个SIZE的JNI INT数组，jni的数组场景都是NewxxxArray的类型
    jintArray  array=env->NewIntArray(10);
    //转换成C的数组指针
    jint * arrint=env->GetIntArrayElements(array,NULL);


    for (int i = 0; i <10 ; ++i) {
        //给数组每个元素赋值
        *(arrint+i)=i;
    }
    env->ReleaseIntArrayElements(array,arrint,0);

    return array;
    // TODO

}