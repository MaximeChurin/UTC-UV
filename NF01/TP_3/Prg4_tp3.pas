program noote;
Var
   note:real;
Begin
     Writeln('Saisir la note');
     Readln(note);
     While ((note<0) or (note>20)) do
           begin
                      Writeln('Saisir la note car la precedente n est pas correcte');
                      Writeln('Ou quittez l application');
                      Readln(note);
           end;
     Readln(note);
End.


