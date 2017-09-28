program albums;
const
max_chanson=30;
max_album=20;
type
T_chanson = record
    titre:string[63];
    duree:integer;
    end;
T_album = record
    liste : array[1..max_chanson] of T_chanson;
    nb_chanson : integer;
    annee : integer;
    titre : string[63];
    artiste : string[63];
    end;
F_album = file of T_album;
var
   f:f_album;
   nbalb:integer;




// ouverture de f
procedure ouverture (var f: f_album);
var
    nom: string;
begin
    writeln('nom du fichier');
    readln(nom);
    assign(f,nom);
    rewrite(f);
end;





procedure saisie_album(var f: f_album);
var
   i,j:integer;
   album:t_album;
begin
          writeln('entrez le nombre d"albums');
          readln(nbalb);
          for i:=1 to nbalb do
          begin
          //entree des donnees dans l'enregistrement
          with album do
          Begin
          writeln('entrer nom artiste de l"album ',i);
          readln(artiste);
          writeln('entrez titre de l"album ',i);
          readln(titre);
          writeln('entrez annee de l"album ',i);
          readln(annee);
          writeln('entrez nombre de chansons de l"album ',i);
          readln(nb_chanson);
          for j:=1 to nb_chanson do
               begin
               writeln('entrez le nom de la chanson ',j);
               readln(liste[j].titre);
               writeln('entrez la duree de la chanson ',j);
               readln(liste[j].duree);
               end;
          end;
          //sauvegarde de l'enregistrement dans le fichier
          write(f,album);
          end;

end;





function duree_tot(a:t_album):integer;
var
    i,somme:integer;
begin
    somme:=0;
    for i:=1 to a.nb_chanson do
        somme:=somme+a.liste[i].duree;
    duree_tot:=somme;
end;




function plus_long_album(var f:f_album):integer;
var
    max,i:integer;
    album:t_album;
begin
    reset(f);
    read(f,album);
    max:=duree_tot(album);
    for i:=2 to nbalb do
        begin
        read(f,album);
        if duree_tot(album)>max then
            max:=duree_tot(album);
        end;
    plus_long_album:=max;
    writeln('l"album le plus long dure ', plus_long_album);
end;






begin
    ouverture(f);
    saisie_album(f);
    plus_long_album(f);
    readln;
    close(f);
end.
