Program remise;
Var
mnet : real;
mbrut : real;
Begin
     repeat
     Writeln('Veuillez rentrer le montant brut');
     Readln(mbrut);
     until mbrut>0;
     mnet:=mbrut;
     If ((mnet >=200) and (mnet <=500)) then
        mnet:=mnet*0.95;
     If (mnet>500) then
        mnet:=0.9*mnet;
     Writeln('Le montant net est:', mnet:6:2,'€');
     Readln(mnet);
End.
