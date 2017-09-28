Program factorielle;
Var
   FactN, N, i : integer;
Begin
     Writeln('Veuillez saisir un nombre dont vous voulez la factorielle');
     Readln(N);
     FactN:=1;
     For i:=1 to N do
     FactN:=FactN*i;
     Writeln('La factorielle vaut :',FactN);
     Readln(N);
End.

