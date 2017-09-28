Program bissextiles;
Var
   an:integer;
   bissextile : boolean;
Begin
     Writeln('Veuillez saisir l annee');
     Readln(an);
     bissextile:=( (an mod(4)=0) and ((an mod(100)<>0) or (an mod(400)=0)) );
       If bissextile then
        writeln('L annee est bissextile')
     Else Writeln('L annee n est pas bissextile');
     Readln(an);
End.
