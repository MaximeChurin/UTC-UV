program Racines;
var 
a, b, c , d, x1, x2 : real;                        // déclaration des variables  de types réels
begin
	d:=0;                                          // initialisation de la variable d
	writeln('entrez les coefficients a b et c');   // affichage d'un message demandant d'entrer les cofficients à l'utilisateur
	readln (a, b, c);                              // attribution d'une valeur à d en fonction des variables a,b,c rentrées précedemment par l'utilisateur
	d:=b*b-4*a*c;                                  // test avec 3 cas
	if d > 0 then
		begin                                              // attribution de valeurs à x1 et x2 qui sont les racines du polynôme du 2nd degrè en fonction des autres variables et avec la racine carré, diviser , multiplier...
			x1:=(-b+sqrt(d))/(2*a);
			x2:=(-b-sqrt(d))/(2*a);
			write('les deux solutions sont');
			writeln(x1, x2);                              // affichage des solutions sur 2 lignes, une pour le message, une pour les variables x1 et x2
		end
	else                                                 // sinon , cas de la solution unique , on peut utiliser d et x1 car ces variables ne seront utilisées que dans 1 cas, on utilise un if,else,else...
		if d=0 then
			begin
				x1:=-b/(2*a);
				write('la solution unique est :');
				writeln(x1);                                // on pourra remarquer qu'il y a une hiérarchie ou un ordre dans le test, on effectue le 2ème sinon après le 1er , et ainsi de suite
			end
		else
			writeln('pas de solution dans IR ');          // sinon affiché le message "pas de solution dans IR

readln(a);                                                // permet de visualiser le résultat
end.                                                       // le "." permet de savoir que c'est le "end final" du programme et non un "end" d'une fontion, comme celui du test par exemple

