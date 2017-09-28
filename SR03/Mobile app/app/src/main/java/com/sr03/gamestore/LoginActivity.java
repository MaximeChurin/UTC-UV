package com.sr03.gamestore;

import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.Toast;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class LoginActivity extends AppCompatActivity {

    ProgressDialog prgDialog;
    EditText email;
    EditText password;
    String emailtxt;
    String passwordtxt;
    ProgressBar spinner;
    private static final String TAG = "LoginActivity";
    /*
    Cb de webservices ? compte du client
    Deconnexion ? Oui
    */

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        Toolbar myToolbar = (Toolbar) findViewById(R.id.my_toolbar);
        setSupportActionBar(myToolbar);

        email = (EditText)findViewById(R.id.email);
        password = (EditText)findViewById(R.id.password);
        spinner = (ProgressBar) findViewById(R.id.progressBar);
        spinner.setVisibility(View.GONE);

        prgDialog = new ProgressDialog(this);
        prgDialog.setMessage(getString(R.string.wait_dialog));
        prgDialog.setCancelable(false);

        final Button btn = (Button) findViewById(R.id.btn_login);
        btn.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                spinner.setVisibility(View.VISIBLE);
                doLogin();
            }
        });
    }

    public void doLogin(){
        emailtxt = email.getText().toString();
        passwordtxt = password.getText().toString();

        Map<String, String> map = new HashMap<>();
        map.put("email", emailtxt);
        map.put("password", passwordtxt);
        String params = RequestParams(map);
        String url = "http://10.0.2.2:8080/videoGameWS/rest/jeux/customer" + params;

        OkHttpClient okHttpClient = new OkHttpClient();
        Request myGetRequest = new Request.Builder()
                .url(url)
                .build();

        okHttpClient.newCall(myGetRequest).enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                //spinner.setVisibility(View.GONE);
                //Toast.makeText(getApplicationContext(), "Error", Toast.LENGTH_SHORT).show();
                e.printStackTrace();
            }

            @Override
            public void onResponse(Call call, final Response response) throws IOException {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if (!response.isSuccessful()) {
                            spinner.setVisibility(View.GONE);
                            Toast.makeText(getApplicationContext(), "Unknown user", Toast.LENGTH_SHORT).show();
                            Log.d(TAG, "Error"+response);
                        } else {
                            //code >= 200 && code < 300;
                            String profile_info = null;
                            try {
                                profile_info = response.body().string();
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            SharedPreferences settings = getSharedPreferences("Profile",0);
                            SharedPreferences.Editor editor = settings.edit();
                            editor.putString("profile_info", profile_info);
                            editor.apply();

                            Intent intent = new Intent(LoginActivity.this, MainActivity.class);
                            startActivity(intent);
                            spinner.setVisibility(View.GONE);
                            finish();
                        }
                    }
                });
            }
        });
    }

    public String RequestParams(Map<String, String> map){
        String params = "?";
        for (Map.Entry<String, String> entry : map.entrySet())
        {
            if (!params.equals("?")) {
                params += "&";
            }
            params += entry.getKey() + "=" + entry.getValue();
        }
        return params;
    }
}
