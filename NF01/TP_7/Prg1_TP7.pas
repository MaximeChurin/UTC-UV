Program ex1;

Var

   mot : string;

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

Function palindrome (s : string) : boolean;

         Var
              temp :string;
         Begin

               temp := copy (s,1,length(s));
               If Inverse(s)=temp then
                  palindrome := true
               Else palindrome := false;
        End;


Begin

Writeln ('Saisir un mot');
readln (mot);
Writeln (palindrome(mot));
readln;

End.
