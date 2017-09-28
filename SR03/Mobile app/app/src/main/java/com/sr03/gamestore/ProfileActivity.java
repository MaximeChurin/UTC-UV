package com.sr03.gamestore;

import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.lang.reflect.Type;
import java.util.List;

public class ProfileActivity extends AppCompatActivity {

    TextView firstname;
    TextView lastname;
    TextView email;
    TextView phonenumber;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);

        Toolbar myToolbar = (Toolbar) findViewById(R.id.my_toolbar);
        setSupportActionBar(myToolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        SharedPreferences settings = getSharedPreferences("Profile", 0);
        String profile_info = settings.getString("profile_info", "default");

        Type type = new TypeToken<Customer>() {}.getType();
        Gson gson = new Gson();
        Customer customer = gson.fromJson(profile_info, type);

        firstname = (TextView)findViewById(R.id.firstname);
        firstname.setText(customer.getFirstName());
        lastname = (TextView)findViewById(R.id.lastname);
        lastname.setText(customer.getLastName());
        email = (TextView)findViewById(R.id.email);
        email.setText(customer.getEmail());
        phonenumber = (TextView)findViewById(R.id.phonenumber);
        phonenumber.setText(customer.getPhoneNumber());
    }

    @Override
    public boolean onSupportNavigateUp() {
        onBackPressed();
        return true;
    }
}
