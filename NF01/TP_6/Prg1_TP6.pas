Program fichiers;
Const
     Max_Chanson=30;
     Max_Album=20;
Type
    TABLEAU = array[1..Max_Album] of integer;
    T_chanson = record
        titre : string [63];
        duree : integer;
        end;
    Tab = array [1 .. Max_Chanson] of T_chanson;
    T_album = record
        liste : Tab ;
        nb_chansons : integer ;
        annee : integer ;
        titre : string [63] ;
        artiste : string [63] ;
        end ;
    F_albums = File of T_album ;

Var
fichier,repo : string ;
album : T_album;

Procedure saisie_album (nom_fichier : string);
Var
   f : F_albums;
   temp : T_album;
   i : integer ;
   rep : string ;
Begin
     read (nom_fichier);
     assign(f,nom_fichier);
     Reset (f);
     repeat
           with temp do
           begin
           writeln('annee ?');
           readln(annee);
           writeln('nombre chansons ?');
           readln(nb_chansons);
           writeln('titre ?');
           readln(titre);
           writeln('artiste ?');
           readln(artiste);
           For i:= 1 to temp.nb_chansons do
           Begin
                      writeln('duree chanson ', i,' ?');
                      readln(liste[i].duree);
                      writeln('titre chanson ', i,' ?');
                      readln(liste[i].titre);
           End;
           End;
           Write (f,temp);
           writeln('continuer ? oui/non');
           readln(rep);
     until (rep='non');
      close (f);
end;

function duree_totale(a : T_album) : integer;
var
   i : integer ;
   begin
     duree_totale:=0;
     for i :=1 to a.nb_chansons do
         begin
          duree_totale := duree_totale + a.liste[i].duree;
         end;
   Writeln('duree totale de album :',duree_totale);
end;

function  plus_long_album(nom_fichier: string) : integer;
          var
          tabduree : TABLEAU;
          temp : T_album;
          i,max,j:integer;
          f : F_albums;

          begin
          i:=1;
          read(nom_fichier);
          assign(f,nom_fichier);
          while not (eof(f)) do
                begin
                     read(f,temp);
                     tabduree[i]:=duree_totale(temp);
                     i:=i+1;
                end;
           max:=tabduree[1];
           For j:=2 to 20 do
               begin
                    if tabduree[j] > max then
                       max := tabduree[j];
               end;
           plus_long_album:= max;

           writeln('duree du plus long album :', max);
           close(f);
           end;




Begin
writeln('BONJOUR VEUILLEZ SAISIR VOS ALBUMS ');
saisie_album(fichier);
duree_totale(album);
plus_long_album(fichier);
read(repo);


end.







