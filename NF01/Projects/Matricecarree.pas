Program MatriceMagique;
//Marche uniquement pour NMAX=3
Const
      NMAX=3;
Type
     MatriceCarree=array[1..NMAX,1..NMAX] of integer;
     tableau=array[1..NMAX] of integer;
Var
   i, j, n, somme, somme1, somme2, somme3, sommel, sommec, sommed : integer;
   mat : MatriceCarree;
   tab1, tab2, tab3 : tableau; //peut on mettre tab1..tabNMAX
   moy : real;
Begin
// saisie de la mtrice
For i:=1 to NMAX do
    Begin
    For j:=1 to NMAX do
        Begin
             Writeln ('Veuillez saisir le chiffre de la colonne ',j,' et de la ligne ', i);
             Readln (n);
             mat [i, j]:=n;
        End;
    End;
//pas pratique si NMAX grand : injections dans un tableau des valeurs de chaque colonne le numero de la ligne variant et calcul de ces combre
//ta1 jusqu'à tabNMAX
For i:=1 to NMAX do
        Begin
        tab1 [i]:= mat[i, 1];
        somme:= somme + tab1[i];
        somme1:=somme;
        End;
For i:=1 to NMAX do
        Begin
        tab2 [i]:= mat[i, 2];
        somme:= somme + tab2[i];
        somme2:=somme-somme1;
        End;
For i:=1 to NMAX do
        Begin
        tab3 [i]:= mat[i, 3];
        somme:= somme + tab3[i];
        somme3:=somme-somme1-somme2;
        End;
moy:=somme/(NMAX*NMAX);
Writeln ('la moyenne de cette matrice est :',moy:5:3);
Writeln ('La somme de chaque ligne est :',somme1,' ',somme2,' ', somme3);
//calcul des somme de colonnes
IF (somme1<>somme2) or (somme2<>somme3) or (somme1<>somme3) then
   Writeln ('Matrice non magique')
//calcul des somme de lignes
Else
    Begin
        sommel:=somme1;
        somme:=0;
        For j:=1 to NMAX do
            Begin
            tab1 [j]:= mat[1, j];
            somme:= somme + tab1[j];
            somme1:=somme;
            End;
        For j:=1 to NMAX do
            Begin
            tab2 [j]:= mat[2, j];
            somme:= somme + tab2[j];
            somme2:=somme-somme1;
            End;
        For j:=1 to NMAX do
            Begin
            tab3 [j]:= mat[3, j];
            somme:= somme + tab3[j];
            somme3:= somme-somme1-somme2;
            End;
            Writeln ('La somme de chaque colonne est :', somme1,' ',somme2,' ', somme3);
        IF (somme1<>somme2) or (somme2<>somme3) or (somme1<>somme3) then
           Writeln ('Matrice non magique')
// calcul des diagonales
        Else
            Begin
            sommec:=somme1;
            somme:=0;
            For j:=1 to NMAX do
                Begin
                tab1 [j]:= mat[j, j];
                somme:= somme + tab1[j];
                somme1:=somme;
                End;
            For i:=1 to NMAX do
                Begin
                For j:=NMAX to 1 do
                    Begin
                    If   i+j=NMAX+1 then
                    tab2 [i]:= mat[i, j];
                    somme:= somme + tab2[i];
                    somme2:=somme-somme1;
                    End;
                End;
            sommed:=somme1;
            Writeln ('la somme de chaque diagonale est:', somme1,' ',somme2);
            IF (somme1<>somme2) then
            Writeln ('Matrice non magique');
            End;
    Writeln ('la somme de chaque ligne est:', sommel,', la somme de chaque colonne est:',sommec,', la somme de chaque diagonale est:', sommed);
    If (sommel<>sommec) or (sommel<>sommed) or (sommec<>sommed) then
    Writeln ('Matrice non magique')
    Else
    Writeln ('Matrice magique');
    End;
For i:=1 to NMAX do
    Begin
    For j:=1 to NMAX do
    Writeln (mat [i, j]);
    End;
Readln (n);
End.




