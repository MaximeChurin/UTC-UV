Program mat;
Const nmax=1000;
type
    matrice = array[1..nmax,1..nmax] of real;
Var
   nl1,nc1,nl2,nc2,i,j : integer ;
   op : char;
   k : integer;
   MA,MB,MC : matrice ;
Begin
Repeat
      Writeln('Entrer le nombre de lignes de votre 1ere matrice');
      Readln(nl1);
Until nl1>0;
Repeat
      Writeln('Entrer le nombre de colonnes de votre 1ere matrice');
      Readln(nc1);
Until nc1>0;
Repeat
      Writeln('Entrer le nombre de lignes de votre 2eme matrice');
      Readln(nl2);
Until nl2>0;
Repeat
      Writeln('Entrer le nombre de colonnes de votre 2eme matrice');
      Readln(nc2);
Until nc2>0;
For i:=1 to nl1 do
    For j:=1 to nc1 do
        begin
             Writeln('entrer la composante de votre ligne ', i, ' et de votre colonne ', j ,' de la matrice 1');
             Readln(k);
             MA[i,j]:=k;
        end;
For i:=1 to nl2 do
    For j:=1 to nc2 do
        begin
             Writeln('entrer la composante de votre ligne ', i, ' et de votre colonne ', j ,' de la matrice 2');
             Readln(k);
             MB[i,j]:=k;
        end;
Writeln('Quelle operation voulez vous faire? +,-,*');
Readln(op);
                if ((op='+') or (op='-')) then       // gestion erreurs
                   if ((nc1<>nc2) or (nl1<>nl2)) then
                      Writeln('operation voulue impossible,si il un resultat est enonce il sera faux');
                if (op='*') then
                   if (nc1<>nl2) then
                      Writeln('operation voulue impossible, ,si il un resultat est enonce il sera faux');

case op of
     '+' : begin
           For i:=1 to nl1 do
               begin
                    For j:=1 to nc1 do
                    MC[i,j]:=MA[i,j]+MB[i,j];
                end;
           end;
     '-' : begin
           For i:=1 to nl1 do
               begin
                    For j:=1 to nc1 do
                    MC[i,j]:=MA[i,j]-MB[i,j];
                end;
           end;
     '*' : begin
           For i:=1 to nl2 do
               begin
                    For j:=1 to nc1 do
                        Begin
                             for k:=1 to nl2 do
                             MC[i,j]:=MC[i,j] + MA[i,k]*MB[k,j];
                        end;
                end;
           end;
end;
Writeln('Le resultat de l operation A ',op,'B est :');
for i:=1 to nl1 do
    begin
         for j:=1 to nc2 do
             Writeln(MC[i,j]:3:4);
    end;
readln(k);
end.




