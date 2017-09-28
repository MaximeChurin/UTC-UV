Program ex4;

Var

   x : integer;
   s : string;

Procedure Affichechiffres (c : string);

          Var

          l: integer;

          Begin

          l:=length(c);
          If l<>1 then
             Begin
                  Write(c[1],'/');
                  Affichechiffres (copy(c,2,l));
             End
          Else
              Writeln (c);
          End;




Begin

     Writeln ('Saisir un nombre');
     Readln (x);
     str (x,s);
     Affichechiffres (s);
     Readln (s);

End.
