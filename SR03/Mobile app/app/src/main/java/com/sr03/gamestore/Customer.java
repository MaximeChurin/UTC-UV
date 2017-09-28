package com.sr03.gamestore;

import java.util.List;

/**
 * Created by maxime on 08/06/2017.
 */

public class Customer {
    private int id;
    private String email;
    private String firstName;
    private String lastName;
    private String password;
    private String phoneNumber;
    private transient List<String> liveIns;
    private List<String> purchases;

    public Customer() {
    }

    public String getEmail() {
        return this.email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getFirstName() {
        return this.firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return this.lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getPassword() {
        return this.password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getPhoneNumber() {
        return this.phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public List<String> getLiveIns() {
        return this.liveIns;
    }

    public void setLiveIns(List<String> liveIns) {
        this.liveIns = liveIns;
    }

    public List<String> getPurchases() {
        return this.purchases;
    }

    public void setPurchases(List<String> purchases) {
        this.purchases = purchases;
    }
}
