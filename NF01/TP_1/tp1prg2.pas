program Maximum ;
var
   a, b : integer;                                                       // les variables doivent �tres des nombres entiers relatifs, elles sont saisies par l'utilisateur
   m : integer;
begin
   writeln('donner les deux nombres a b');
   readln(a,b);                                                       // les nombres peuvent �tre plac�s n'importe o� dans la fen�tre (� la suite, � la ligne, espac�s de plusieurs lignes) on saisit a puis b
   if a < b then m:=b                                                 // fonction if, permet d'effectuer un test (si, alors, sinon)
            else m:=a;                                                 // m prend la valeur du maximum des 2 nombres, et ":=" permet d'attribuer une valeur � une variable
   writeln('le maximum des deux nombres ',a,' et ', b,' est : ',m);      // affichage, les " '......' "permettent d'afficher des messages textes autre que des variables et " ,variable, " ou ", variable," peu importe l'espacement, permet d'ins�rer les variables dans le texte affich�
   readln;                                                               //permet de pouvoir visualier le r�sultat du programme suite � son �x�cution
end.


                                                    // le programme permet de comparer 2 nombres entiers relatifs et d'afficher le maximum des 2.
