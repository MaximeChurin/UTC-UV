Program ex3;

Var

   n,m : integer;

Function add (x,y :integer) : integer;

   Begin

        If y<>1 then
           add := x  + add (x,y-1)
        Else add:=x;

   End;




Begin

Writeln ('Saisir 2 entiers naturels');
Readln (n,m);
Writeln (add (n,m));
Readln (n);

End.

//cette fonction réalise la multiplication de n par m
