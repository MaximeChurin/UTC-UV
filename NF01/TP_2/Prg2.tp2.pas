Program Newton;

Var
x0,E,x,a,b: real;
i : integer;

Begin
i:=0;
Writeln('Entrez la valeur de x0');
Readln(x0);
Writeln('Entrez la precision');
Readln(E);
If E<0 then
   Writeln('Ce n est pas correct')
Else
    Begin
         x:=x0;
         Repeat
               i:=i+1;
               a:=-((ln(x)-(x/5))/((1/x)-0.2));
               x:=x+a;
         Until abs(ln(x)-(x/5))<E;
         Writeln('la solution est :',x:8:6);
         Writeln('la valeur de f(x) est :',(ln(x)-(x/5)));
         Writeln('le nombre d iteration est :',i);
     End;
Readln(b);
End.


