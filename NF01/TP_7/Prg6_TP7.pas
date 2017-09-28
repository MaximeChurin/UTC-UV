Program ex6;

Var

n,m : integer;

Function add(x,y : integer) : integer;

         Begin

         If y<>1 then
            add := x + add(x,y-1)
         Else
             add := x;

         End;

Begin

Writeln ('Saisir 2 entiers naturels');
Readln (n,m);
writeln (add(n,m));
Readln;

End.


