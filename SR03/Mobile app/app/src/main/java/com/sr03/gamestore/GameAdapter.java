package com.sr03.gamestore;

import android.app.Activity;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class GameAdapter extends ArrayAdapter<Game>
{
    private List<Game> games;
    private ArrayList<Game> arraylist;
    private Context context;
    int layoutResourceId;

    public GameAdapter(Context context, int layoutResourceId, List<Game> games) {
        super(context, layoutResourceId, games);
        this.layoutResourceId = layoutResourceId;
        this.context = context;
        this.games = games;
        this.arraylist = new ArrayList<Game>();
        this.arraylist.addAll(games);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View row = inflater.inflate(layoutResourceId, parent, false);

        Game game = games.get(position);

        TextView titletxt = (TextView) row.findViewById(R.id.title);
        titletxt.setText(game.getTitle());
        TextView pricetxt = (TextView) row.findViewById(R.id.price);
        pricetxt.setText(Float.toString(game.getPrice())+"$");
        TextView consolestxt = (TextView) row.findViewById(R.id.consoles);

        List<String> consoles = game.getIsPlayedOns();
        String res = "";

        for (int i=0; i<consoles.size(); i++) {
            if (i != 0){
                res += ", ";
            }
            res += consoles.get(i);
        }

        consolestxt.setText(res);

        return row;
    }

    // Filter Class
    public void filter(String charText) {
        charText = charText.toLowerCase(Locale.getDefault());
        games.clear();
        if (charText.length() == 0) {
            games.addAll(arraylist);
        }
        else{
            for (Game game : arraylist){
                if (game.getTitle().toLowerCase(Locale.getDefault()).contains(charText)){
                    games.add(game);
                }
            }
        }
        notifyDataSetChanged();
    }
}
