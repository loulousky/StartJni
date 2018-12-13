package com.example.liuhai.jnilib;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

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
        tv.setText(stringFromJNI());

        CallMethod();
      CallStaticMethod();
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


}
