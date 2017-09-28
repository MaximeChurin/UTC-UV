program matrice_magique;
const
     NMAX = 100;
type
    tTab = array[1..NMAX,1..NMAX] of integer;
var
    mat : tTab;
    i, j, n : integer;
    somme, sommeRef : integer;
    moy : real;
    bMagique : boolean;

begin
     //////////Saisie de la taille de la matrice et vérification de la taille/////
     repeat
           write('Taille de la matrice carree : ');
           readln(n);
     until n <= NMAX;

     /////////////Saisie Matrice/////////////////
     for i:=1 to n do
         begin
              //Saisie Ligne
              writeln('Saisir ligne ', i);
              for j:=1 to n do
                  //Saisie colonne
                  readln(mat[i,j]);
          end;

      //////////Afficher la matrice/////////////
      for i:=1 to n do
         begin
              for j:=1 to n do
                  write(mat[i,j], ' ');
               writeln;
          end;

     ///////////////Calcul moyenne/////////////
     moy:=0;
     for i:=1 to n do
         for j:=1 to n do
              moy := moy + mat[i,j];
      moy := moy / (n*n);

      //////////////Afficher la moyenne/////////
      writeln('La moyenne est : ', moy:5:2);


      /////////////Calcul de la somme reference (= 1ere ligne)////////////
      sommeRef := 0;
      for j:=1 to n do
          sommeRef := sommeRef + mat[1,j];

      writeln('Somme Ref : ', sommeRef);

       bMagique := true;
      /////////// Voir si toutes les lignes sont égales à la somme ref///////
       i:=2;
       while (i<=n) AND bMagique do
             begin
                  somme := 0;
                  for j:=1 to n do
                      somme := somme + mat[i,j];
                  if somme <> sommeRef then
                     bMagique := false;
                  writeln('Somme ligne ', i, ' = ', somme);
                  i := i+1;
              end;

        /////////// Si toujours magique continuer sur colonnes/////////
        if bMagique then
           begin
                 writeln('lignes ok on continue sur colonnes');

                 /////////// Voir si toutes les colonnes sont égales à la somme ref
                 j:=1;
                 while (j<n) and bMagique do
                       begin
                            somme := 0;
                            for i:=1 to n do
                                somme := somme + mat[i,j];
                            if somme <> sommeRef then
                               bMagique := false;

                             writeln('Somme colonne ', j, ' = ', somme);
                             j := j+1;
                       end;

                  ///////////// Si toujours magique continuer sur Diagonale 1
                  if bMagique then
                     begin
                         writeln('colonnes ok on continue sur la diagonale 1');

                         /////// Voir Diagonale 1
                         somme := 0;
                         for i:=1 to n do
                               somme := somme + mat[i,i];

                         writeln('Somme Diagonale 1 = ', somme);
                         if somme <> sommeRef then
                            bMagique := false

                         //////// Si toujours magique continuer Diagonale 2
                         else
                             begin
                                  writeln('diagonale 1 ok on continue sur diagonale 2');

                                 ///////// Voir Diagonale 2
                                 somme := 0;
                                 for i:=1 to n do
                                    somme := somme + mat[i, n-i+1];

                                 writeln('Somme Diagonale 2 = ', somme);
 
                                 if somme <> sommeRef then
                                     bMagique := false
                              end;
                       end;

             end;

         if bMagique then
            writeln('La matrice est magique!!!!!')
         else
            writeln('La matrice n est pas magique');

         readln;


end.
