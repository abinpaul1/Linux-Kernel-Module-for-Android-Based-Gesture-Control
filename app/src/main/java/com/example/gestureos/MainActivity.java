package com.example.gestureos;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "OSP";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }

    public void check_and_log(View view){
        String msg="-1";
        switch(view.getId()){
            case R.id.brightness_down:
                msg = "b";
                break;
            case R.id.brightness_up:
                msg = "B";
                break;
        }
        Log.d(MainActivity.TAG,msg);
        String t = ".";
        Log.d(MainActivity.TAG, t);
    }
}
