package com.example.liuhai.jnilib;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Date;

public class MainActivity extends AppCompatActivity {

    String abc="1111";
    public static String def="22222";
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(getField()+getStaticField());
        CallMethod();
        CallStaticMethod();




       Date date=new Date();
        date.getTime();
       TextView date_txt= (TextView)findViewById(R.id.date);
       date_txt.setText(CallConstructMethod());


       int a[]={2,45,1,345,8};
        for (int i = 0; i < a.length; i++) {
          Log.d("JNILOG",a[i]+"排序前");
        }

        SortArray(a);
        for (int i = 0; i < a.length; i++) {
         Log.d("JNILOG",a[i]+"排序后");
        }

        int b[]=getArray();
        for (int i = 0; i < b.length; i++) {
            Log.d("JNILOG",b[i]+"JNI传过来的数组");
        }
    }

    public void test1(String a){
        Toast.makeText(getApplicationContext(),a,1).show();
    }
    public static void test2(){
        Log.d("debug","这是来自JNI的消息");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    /**
     * JNI调用JAVA/改写JAVA属性并且打印
     */
    public native String getField();

    /**
     * JNI改JAVA的静态变量
     *
     */
    public native String getStaticField();

    /**
     * JNI调JAVA的方法
     */
     public native void CallMethod();


    /**
     * JNI调用静态方法
     */
    public native void CallStaticMethod();


    /**
     * JNI调用类的构造方法
     *
     */
    public native String CallConstructMethod();


    /**
     * 传递Ini数组给JNI进行排序并返回
     */
    public native void SortArray(int[] array);


    /**
     * 从JNI层拿到一个int数组
     *
     */
     public native int[] getArray();

}
