Program factorielle;
Var
   i,n : integer;

Begin
     Writeln('Veuillez saisir un nombre dont vous voulez la factorielle');
     Readln(n);
     For i:=1 to (n-1) do
     Begin
     n:=n*i;
     //a:=i*(i+1);
     End;
     Writeln('La factorielle vaut :',n);
     Readln(n);
End.

