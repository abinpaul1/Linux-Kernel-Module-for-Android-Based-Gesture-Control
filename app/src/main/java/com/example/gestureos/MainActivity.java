package com.example.gestureos;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.os.Bundle;
import android.speech.RecognizerIntent;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "OSP";
    private final int REQ_CODE = 100;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ImageView speak = findViewById(R.id.speak);
        speak.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
                intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
                intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());
                intent.putExtra(RecognizerIntent.EXTRA_PROMPT,"Need to Speak");
                try{
                    startActivityForResult(intent,REQ_CODE);
                } catch (ActivityNotFoundException a){
                        Toast.makeText(getApplicationContext(),"Sorry your device is not supported",Toast.LENGTH_SHORT).show();
            }
        }
        });
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
            case R.id.volume_down:
                msg = "v";
                break;
            case R.id.volume_up:
                msg = "V";
                break;
            case R.id.mute:
                msg = "m";
                break;
            case R.id.lock_screen:
                msg = "l";
                break;
            case R.id.unlock_screen:
                msg = "u";
                break;
        }
        Log.d(MainActivity.TAG,msg);
        String t = ".";
        Log.d(MainActivity.TAG, t);
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        super.onActivityResult(requestCode,resultCode,data);

        switch (requestCode){
            case REQ_CODE: {
                if (resultCode == RESULT_OK && null != data){
                    ArrayList<String> result = data
                            .getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
//                    Toast.makeText(getApplicationContext(),result.get(0),Toast.LENGTH_SHORT).show();
                    String msg_text = result.get(0).toLowerCase();
                    String msg="-1";
                    switch (msg_text){
                        case "lock":
                            msg = "L";
                            break;
                        case "sleep":
                            msg = "S";
                            break;
                        case "turn off":
                            msg = "T";
                            break;
                    }
                    Log.d(MainActivity.TAG,msg);
                    String t = ".";
                    Log.d(MainActivity.TAG, t);
                }
                break;
            }
        }
    }
}
