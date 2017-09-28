Program Pyramide;
Var
   i, j, n, y: integer;
Begin
Writeln ('Saisir le nombre de ligne');
Readln (n);
For i:=1 to n do
Begin
     For j:=1 to (n-i) do
     Write (' ');
     For j:=1 to i do
          Write (j);
     For j:=(i-1) downto 1 do
         Write (j);
Writeln;
End;
Read (n);
End.

