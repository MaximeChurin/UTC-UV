Program tableaumatch ;

type
            fichier = file of string;
Var
            f : fichier;
            s,nom_externe,c : string;
            i : integer;
Begin

Writeln ('Saisir le nom externe du fichier');
Readln (nom_externe);
Assign (f,nom_externe);
Rewrite(f);
c:='';
i:=1;
While c<>'$' do
Begin
Writeln ('Saisir la chaine de caractère');
Readln (s);
Write (f,s);
Writeln ('Saisir un caractère ou $ pour arreter a saisie');
Readln (c);
End;
Reset (f);

While not eof(f) do
Begin
Repeat
Read (f,c)
Until ( (c<>' ') and (c<>',') and (c<>'.') and (not eof(f)) );
i:=i+1;
Repeat
Read (f,c);
Until ( (c=' ') or (c=',') or (c='.') or (eof (f)) );
End;
Writeln (i);
Readln (i);
End.









