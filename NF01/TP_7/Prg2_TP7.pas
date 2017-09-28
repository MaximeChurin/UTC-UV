Program ex2;

Var
s1,s2 : string;
palin : boolean;

Function inverse (s : string): string;

         Var

            l : integer;

         Begin

              l := length (s);
              If l <> 1 then
                 inverse := s[l] + inverse(copy(s,1,l-1))
              Else
                  inverse := s;
              End;
Begin

     Writeln('Saisir un mot');
     Readln (s1);
     s2:= copy (s1,1,length(s1));
     If inverse (s1)=s2 then
        palin:=true
     Else
         palin:= false;
     Writeln ('le mot est-il un palindrome : ', palin);
     readln (s1);

End.

