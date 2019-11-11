package com.example.gestureos;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.ActivityNotFoundException;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.speech.RecognizerIntent;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
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

        /* Set event listener to microphone icon */
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

    /* Function to log the input */
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
                msg = "L";
                break;
            case R.id.unlock_screen:
                msg = "U";
                break;
        }
        Log.d(MainActivity.TAG,msg);
        String t = ".";
        Log.d(MainActivity.TAG, t);
        if (msg=="U"){
            unlock();
        }
    }


    /* Function to log the output of speech */
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
                        case "unlock":
                            msg="U";
                            break;
                        case "volume up":
                            msg="V";
                            break;
                        case "volume down":
                            msg="v";
                            break;
                        case "brightness up":
                            msg="B";
                            break;
                        case "brightness down":
                            msg="b";
                            break;
                    }
                    Log.d(MainActivity.TAG,msg);
                    String t = ".";
                    Log.d(MainActivity.TAG, t);
                    if (msg=="U"){
                        unlock();
                    }
                }
                break;
            }
        }
    }

    /* Function to unlock */

    public void unlock(){
        final EditText taskEditText = new EditText(this);
        AlertDialog dialog = new AlertDialog.Builder(this)
                .setTitle("Unlock prompt")
                .setMessage("Enter your password")
                .setView(taskEditText)
                .setPositiveButton("Enter", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        String task = String.valueOf(taskEditText.getText());
                        // convert String to char[] array
                        char[] chars = task.toCharArray();

                        // iterate over char[] array using enhanced for loop
                        for (char ch : chars) {
                            Log.d(MainActivity.TAG,Character.toString(ch));
                            String t = ".";
                            Log.d(MainActivity.TAG, t);
                        }
                        Log.d(MainActivity.TAG,"e");
                        String t = ".";
                        Log.d(MainActivity.TAG, t);
                    }
                })
                .setNegativeButton("Cancel", null)
                .create();
        dialog.show();
    }
}
