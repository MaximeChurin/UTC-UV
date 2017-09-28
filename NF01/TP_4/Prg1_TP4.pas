Program table ;
        Const
             nmax=100 ;
        type
            tableau = array[1..nmax] of integer;
        Var
           i,n,k,somme,j : integer ;
           moyenne : real ;
           T : tableau ;

begin
Repeat
      Writeln('entrer le nombre d elements ');
      Readln(n);
Until ((n>0) and (n<=nmax));
For i :=1 to n do
    begin
         Writeln('entrer votre element : ',i);
         Readln(k);
         T[i]:=k;
    end;
somme:=0;
For i:=1 to n do
    somme:= somme + T[i];
moyenne:= somme/n;
j:=0;
For i:=1 to n do
    begin
    if (T[i]>moyenne) then
    j:=j+1;
    end;
For i:=1 to n do
    Writeln('l element ',i,' du tableau est: ', T[i]);
Writeln('La moyenne vaut:',moyenne:3:2);
Writeln('le nombre d element superieur a la moyenne est: ',j);
readln(n);
End.







