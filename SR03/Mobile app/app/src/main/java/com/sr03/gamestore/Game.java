package com.sr03.gamestore;

import java.util.List;

/**
 * Created by maxime on 23/05/2017.
 */

public class Game {

    private int id;
    private float price;
    private String title;
    private transient List<String> contains;
    private List<String> isPlayedOns;

    public Game() {
    }

    public int getId() {
        return this.id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public float getPrice() {
        return this.price;
    }

    public void setPrice(float price) {
        this.price = price;
    }

    public String getTitle() {
        return this.title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public List<String> getContains() {
        return this.contains;
    }

    public void setContains(List<String> contains) {
        this.contains = contains;
    }

    public List<String> getIsPlayedOns() {
        return this.isPlayedOns;
    }

    public void setIsPlayedOns(List<String> isPlayedOns) {
        this.isPlayedOns = isPlayedOns;
    }
}
