Program TP4;
Const

MaxEquipe = 20;
MaxMatch=1000;

Type
Equipe = record
       nom : string;
       numero : integer;
       End;
TabNom_Eq = array [1..MaxEquipe] of Equipe;
TabMatch = array [1..MaxMatch, 1..4] of integer;

Var

   T_e : TabNom_Eq;
   T_m : TabMatch;
   nbre_eq, nbre_match : integer;



Procedure  SaisieNoms (var tN : TabNom_Eq; var nM : integer);

Var
     s : string;
Begin
     Writeln('Saisir le nom d une equipe ou $ pour arreter');
     Readln (s);
     nM:=1;
     Repeat
     tN[nM].nom := s;
     tN[nM].numero := nM;
     nM:=nM+1;
     Writeln('Saisir le nom d une equipe ou $ pour arreter');
     Readln (s);
     Until (s='$') or (nM>20);

End;

Procedure  SaisieMatch (var tM : TabMatch; var x : integer);

Var
    s : string;
Begin
     x:=1;
     s:=' ';
     While s<>'$' do
     Begin
     Writeln ('Saisir le numero de l equipe locale');
     Readln (tM[x,1]);
     Writeln ('Saisir le numero de l equipe exterieure');
     Readln (tM[x,2]);
     Writeln ('Saisir le score de l equipe locale');
     Readln (tM[x,3]);
     Writeln ('Saisir le score de l equipe exterieure');
     Readln (tM[x,4]);
     x:=x+1;
     Writeln ('Saisir $ pour arreter ou un caractere pour continuer');
     Readln(s);
     End;
     x:=x-1;

End;

Function QuiGagne (tab:TabMatch; x : integer) : integer;
Begin

     If (tab [x,3]>tab [x,4]) then
        QuiGagne := 1;
     If (tab [x,3]<tab [x,4]) then
        QuiGagne := -1;
     If (tab[x,3]=tab [x,4]) then
        QuiGagne := 0;

End;

Procedure AffiGagnants (tab : TabMatch ; x : integer; tN : TabNom_Eq);
Var

i: integer;

Begin
For i:=1 to x do
    Begin

    If QuiGagne(tab,x)=1 then
    Writeln ('Le gagnant du match ',i,' est ', tN[tab[i,1]].nom);
    If QuiGagne(tab,x)=0 then
    Writeln ('pas de gagnant');
    If QuiGagne(tab,x)=-1 then
    Writeln ('Le gagnant du match ',i,' est ', tN[tab[i,2]].nom);

    End;

End;

Begin

SaisieNoms (T_e, nbre_eq);
SaisieMatch (T_m, nbre_match);
AffiGagnants (T_m, nbre_match, T_e);
Readln (nbre_match);

End.

