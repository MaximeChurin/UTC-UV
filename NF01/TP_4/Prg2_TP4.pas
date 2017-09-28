Program tablo ;
        Const
             c_max=1000;
             l_max=1000;
        Type
            Matrice = array[1..c_max, 1..l_max] of integer;
        Var
        M1, M2, M3 : matrice;
        i,j,c1,c2,l1,l2 : integer;
        x : longint;
        signe : char;
Begin
repeat
Writeln('Entrer le nombre de colonnes et de lignes de la matrice 1 ');
Readln(c1,l1);
until  ((c1>0) and (c1<=c_max) and (l1>0) and (l1<=l_max));
For i:=1 to l1 do
    begin
         For j:=1 to c1 do
             Begin
             Writeln ('Saisir le chiffre a entré dans la ligne ',i,' de la colonne ',j);
             Read (x);
             M1[j,i]:= x;
             End;
    End;

repeat
Writeln('Entrer le nombre de colonnes et de lignes de la matrice 2 ');
Readln(c2,l2);
until  ((c2>0) and (c2<=c_max) and (l2>0) and (l2<=l_max));
For i:=1 to l2 do
    begin
         For j:=1 to c2 do
             Begin
             Writeln ('Saisir le chiffre a entré dans la ligne ',i,' de la colonne ',j);
             Read (x);
             M2[j,i]:= x;
             End;
    End;
Writeln ('Saisir l opération que vous souhaitez effectuer : + - *');
Readln (signe);
Case signe of
     '+' : Begin
           If ((c1=c2) and (l1=l2)) then
              Begin
              For i:=1 to c1 do
                  Begin
                  For j:=1 to l1 do
                      M3[i,j]:= M1[i,j] + M2[i,j];
                  End;
              End;
           End;
     '-' : Begin
           If ((c1=c2) and (l1=l2)) then
              Begin
              For i:=1 to c1 do
                  Begin
                  For j:=1 to l1 do
                      M3[i,j]:= M1[i,j] - M2[i,j];
                  End;
              End;
           End;
End;


Readln (x);
End.


