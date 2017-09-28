%%Liste des differentes orientations du plateau
board(1, [[2,3,1,2,2,3], [2,1,3,1,3,1], [1,3,2,3,1,2], [3,1,2,1,3,2], [2,3,1,3,1,3], [2,1,3,2,2,1]]).
board(2, [[2,2,3,1,2,2], [1,3,1,3,1,3], [3,1,2,2,3,1], [2,3,1,3,1,2], [2,1,3,1,3,2], [1,3,2,2,1,3]]).
board(3, [[1,2,2,3,1,2], [3,1,3,1,3,2], [2,3,1,2,1,3], [2,3,1,3,1,2], [1,3,1,3,1,2], [3,2,2,1,3,2]]).
board(4, [[3,1,2,2,3,1], [2,3,1,3,1,2], [2,1,3,1,3,2], [1,3,2,2,1,3], [3,1,3,1,3,1], [2,2,1,3,2,2]]).

%%Plateau de pion initialement vide TODO
%%matricePleine([[1,1,1,1,1,1],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[2,2,2,2,2,2]]).
matriceVide([[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0]]).

%%Ensemble de nos variables globales
:- dynamic(error/1).
:- dynamic(boardGame/1).
:- dynamic(boardPion/1).
:- dynamic(iterator/1).
:- dynamic(khan/1).
:- dynamic(khalistaRouge/2).
:- dynamic(khalistaOcre/2).
:- dynamic(possibleMoveList/1).
:- dynamic(accessibleMoveList/1).
:- dynamic(joueur/1).
:- dynamic(ligneColonne/2).
:- dynamic(scoreEnr/5).


%%Affichage du plateau de jeu + placement des pions.
afficheBoard:- boardGame(BG), boardPion(BP), write('          1          2          3          4          5          6'),
			nl,nl, afficheboard(BG, BP).
afficheboard([],[]):-retract(iterator(_)), asserta(iterator(0)).
afficheboard([X|Y],[A|B]):- iterator(Ligne), retract(iterator(Ligne)), I is Ligne+1, asserta(iterator(I)),
						write('    --------------------------------------------------------------------'),nl,
						write(I),write('    | '),afficheligne(X,A,1),nl,
						write('    --------------------------------------------------------------------'),nl,
						afficheboard(Y,B),!.

afficheligne([],[],_).
afficheligne([X|Y],[A|B],Ite):- A==0,write(X),write(' '),write(' _____ '),write('| '),Iterer is Ite+1,afficheligne(Y,B,Iterer).
afficheligne([X|Y],[A|B],Ite):- A==1,iterator(Ligne),khalistaRouge(Ligne,Colonne),Colonne==Ite,write(X),write(' '),
								write(' KhalR '),write('| '),Iterer is Ite+1,afficheligne(Y,B,Iterer).
afficheligne([X|Y],[A|B],Ite):- A==1,write(X),write(' '),write(' PionR '),write('| '),Iterer is Ite+1,afficheligne(Y,B,Iterer).
afficheligne([X|Y],[A|B],Ite):- A==2,iterator(Ligne),khalistaOcre(Ligne,Colonne),Colonne==Ite,write(X),write(' '),
								write(' KhalO '),write('| '),Iterer is Ite+1,afficheligne(Y,B,Iterer).
afficheligne([X|Y],[A|B],Ite):- A==2,write(X),write(' '),write(' PionO '),write('| '),Iterer is Ite+1,afficheligne(Y,B,Iterer).

%%Nombre element d une matrice
nbElement([],0).
nbElement([_|Q],N) :- nbElement(Q,N1), N is N1+1.

%%Affichage de la liste des choix lors d un deplacement
affichageChoix(X, N):- nbElement(X,N), afficheListe(X),!.
afficheListe([]):-retract(iterator(_)), asserta(iterator(0)).
afficheListe([T|Q]):- write('- numero '), iterator(I), J is I+1, write(J), retract(iterator(_)), asserta(iterator(J)), 
				write(' : case de coordonnee '), afficheListeLigne(T), nl, afficheListe(Q).
afficheListeLigne(Y):- write(Y).

%%Insertion dans matrice.
inserer(Valeur,Liste,[Valeur|Liste]).

%%Modification d une matrice
modificationLigne(_,_,[],[]).
modificationLigne(1,Valeur,[_|Q],Resultat) :- modificationLigne(0,Valeur,Q,Temp), inserer(Valeur,Temp,Resultat),!.
modificationLigne(Colonne,Valeur,[T|Q],Resultat) :- C is Colonne-1, modificationLigne(C,Valeur,Q,Temp), inserer(T,Temp,Resultat),!.
modificationMatrice(_,_,_,[],[]).
modificationMatrice(1,Colonne,Valeur,[T|Q],Resultat) :- modificationLigne(Colonne,Valeur,T,Liste2), 
														modificationMatrice(0,Colonne,Valeur,Q,Liste1), inserer(Liste2,Liste1,Resultat),!.
modificationMatrice(Ligne,Colonne,Valeur,[T|Q],Resultat) :- L is Ligne-1, modificationMatrice(L,Colonne,Valeur,Q,Temp), inserer(T,Temp,Resultat),!.

%%Accesseur sur une case specifique d une matrice
valeurCase(1, C, [T|_],Resultat):- valeurCaseLigne(C,T,Resultat).
valeurCase(L, C, [_|Q],Resultat):- Ldec is L-1, valeurCase(Ldec,C,Q,Resultat).
valeurCaseLigne(1, [T|_],T):-!.
valeurCaseLigne(C, [_|Q],Resultat):- Cdec is C-1, valeurCaseLigne(Cdec,Q,Resultat).

%%Placement des pions.
lireJoueur(_,_,0,Init):- Init<3,write('Vous allez devoir saisir les positions de vos pions entrant d abord les 5 sbires puis la kalista : '),nl, nl,fail.
lireJoueur(_,_,6,Init):- Init<2,write('Vous allez devoir saisir les positions de vos pions entrant d abord les 5 sbires puis la kalista : '),nl, nl,fail.
lireJoueur(X,Y,Compteur,Init):- Init<3,Compteur>=0, Compteur=<4, 
				write('Le joueur rouge : placement des sbires'), nl,
				write('Numero de ligne : '), nl, read(Ligne), nl, retract(error(_)), asserta(error(1)), Ligne>=1, Ligne=<2,
				write('Numero de colonne : '), nl, read(Colonne), nl, retract(error(_)), asserta(error(2)), Colonne>=1, Colonne=<6, 
				retract(error(_)), asserta(error(3)), valeurCase(Ligne, Colonne, X, R), R==0,
				C is Compteur+1, modificationMatrice(Ligne, Colonne, 1, X, Temp),
				retract(error(_)), asserta(error(0)),
				lireJoueur(Temp,Y,C,Init).

lireJoueur(X,Y,5,Init):- Init<3,write('Le joueur rouge : placement de la kalista'), nl,
				write('Numero de ligne : '), nl, read(Ligne), nl, retract(error(_)), asserta(error(1)), Ligne>=1, Ligne=<2,
				write('Numero de colonne : '), nl, read(Colonne), nl, retract(error(_)), asserta(error(2)), Colonne>=1, Colonne=<6, 
				retract(error(_)), asserta(error(3)), valeurCase(Ligne, Colonne, X, R), R==0,
				modificationMatrice(Ligne, Colonne, 1, X, Temp),
				retract(error(_)), asserta(error(0)),
				asserta(khalistaRouge(Ligne,Colonne)),
				lireJoueur(Temp,Y,6,Init).

lireJoueur(X,Y,Compteur,Init):- Init<2,Compteur>=6, Compteur=<10, write('Le joueur ocre : placement des sbires'), nl,				
				write('Numero de ligne : '), nl, read(Ligne), nl, retract(error(_)), asserta(error(4)), Ligne>=5, Ligne=<6,
				write('Numero de colonne : '), nl, read(Colonne), nl, retract(error(_)), asserta(error(2)), Colonne>=1, Colonne=<6, 
				retract(error(_)), asserta(error(3)), valeurCase(Ligne, Colonne, X, R), R==0,
				C is Compteur+1, modificationMatrice(Ligne, Colonne, 2, X, Temp),				
				retract(error(_)), asserta(error(0)),
				lireJoueur(Temp,Y,C,Init).

lireJoueur(X,Y,11,Init):- Init<2,write('Le joueur rouge : placement de la kalista'), nl,				
				write('Numero de ligne : '), nl, read(Ligne), nl, retract(error(_)), asserta(error(4)), Ligne>=5, Ligne=<6,
				write('Numero de colonne : '), nl, read(Colonne), nl, retract(error(_)), asserta(error(2)), Colonne>=1, Colonne=<6, 
				retract(error(_)), asserta(error(3)), valeurCase(Ligne, Colonne, X, R), R==0,
				modificationMatrice(Ligne, Colonne, 2, X, Y),				
				retract(error(_)), asserta(error(0)),
				asserta(khalistaOcre(Ligne,Colonne)).
lireJoueur(X,Y,Compteur,Init):- error(E), E==1, write('Numero de ligne doit etre 1 ou 2'), nl, nl, retract(error(1)), asserta(error(0)),
							lireJoueur(X,Y,Compteur,Init).
lireJoueur(X,Y,Compteur,Init):- error(E), E==4, write('Numero de ligne doit etre 5 ou 6'), nl, nl, retract(error(4)), asserta(error(0)), 
							lireJoueur(X,Y,Compteur,Init).
lireJoueur(X,Y,Compteur,Init):- error(E), E==2, write('Numero de colonne doit etre compris entre 1 et 6'), nl, nl, retract(error(2)), 
							asserta(error(0)), lireJoueur(X,Y,Compteur,Init).
lireJoueur(X,Y,Compteur,Init):- error(E), E==3, write('Case deja occupee'), nl, nl, retract(error(3)), asserta(error(0)), lireJoueur(X,Y,Compteur,Init).

%%Placement des pions pour une IA
lireJoueur(X,Y,Compteur,Init):- Init >2,Compteur>=0, Compteur=<4, 
				random(1,3,Ligne),random(1,7,Colonne),valeurCase(Ligne, Colonne, X, R), retract(error(_)), asserta(error(5)), R==0,
				retract(error(_)), asserta(error(0)),
				C is Compteur+1, modificationMatrice(Ligne, Colonne, 1, X, Temp),
				lireJoueur(Temp,Y,C,Init).

lireJoueur(X,Y,5,Init):- Init>2,
				random(1,3,Ligne),random(1,7,Colonne),valeurCase(Ligne, Colonne, X, R),retract(error(_)), asserta(error(5)), R==0,retract(error(_)), asserta(error(0)),
				modificationMatrice(Ligne, Colonne, 1, X, Temp),
				asserta(khalistaRouge(Ligne,Colonne)),
				lireJoueur(Temp,Y,6,Init).

lireJoueur(X,Y,Compteur,Init):- Init>1,Compteur>=6, Compteur=<10, 
				random(5,7,Ligne),random(1,7,Colonne),valeurCase(Ligne, Colonne, X, R), retract(error(_)), asserta(error(5)), R==0,retract(error(_)), asserta(error(0)),
				C is Compteur+1, modificationMatrice(Ligne, Colonne, 2, X, Temp),
				lireJoueur(Temp,Y,C,Init).

lireJoueur(X,Y,11,Init):- Init>1, 
				random(5,7,Ligne),random(1,7,Colonne),valeurCase(Ligne, Colonne, X, R),retract(error(_)), asserta(error(5)), R==0,retract(error(_)), asserta(error(0)),
				modificationMatrice(Ligne, Colonne, 2, X, Y),
				asserta(khalistaOcre(Ligne,Colonne)).
lireJoueur(X,Y,Compteur,Init):- error(E), E==5,lireJoueur(X,Y,Compteur,Init).

%%Recherche de la liste des pions deplacables JoueurvsJoueur
possibleMoves(PionBoard ,Joueur):-boardGame(BG), khan(Khan), 
								checkMatricePosition(BG,PionBoard,Joueur,Khan).
possibleMoves(PionBoard ,Joueur):- checkNbPionJoueur(N, Joueur, PionBoard), autreMove(PionBoard, Joueur, N).

autreMove(_, Joueur, N):- N\=6,
						write('Si vous voulez rajouter un pion taper 1, autre chose si vous preferez deplacer un pion: '),nl,nl,
						read(Choix), Choix==1, ajoutPion(Joueur),
						retract(joueur(_)),JoueurSuivant is (Joueur mod 2) +1 ,asserta(joueur(JoueurSuivant)),
						retractall(possibleMoveList(_)),
						deplacement.
autreMove(_, _, _):-write('Aucun pion sur le Khan, vous pouvez bouger n importe quel pion !'),nl,
					retract(khan(_)), asserta(khan(0)),
					retractall(possibleMoveList(_)),
					deplacement.


%%Recherche de la liste des pions deplacables JoueurvsMachine
possibleMovesJoueurVsMachine(PionBoard ,Joueur):-boardGame(BG), khan(Khan), 
								checkMatricePosition(BG,PionBoard,Joueur,Khan).
possibleMovesJoueurVsMachine(PionBoard ,Joueur):- checkNbPionJoueur(N, Joueur, PionBoard), autreMoveJoueurVsMachine(PionBoard, Joueur, N).

autreMoveJoueurVsMachine(_, Joueur, N):- N\=6,Joueur=1,
						write('Si vous voulez rajouter un pion taper 1, autre chose si vous preferez deplacer un pion: '),nl,nl,
						read(Choix), Choix==1, ajoutPion(Joueur),
						retract(joueur(_)),JoueurSuivant is (Joueur mod 2) +1 ,asserta(joueur(JoueurSuivant)),
						retractall(possibleMoveList(_)),
						deplacementJoueurVsMachine.
autreMoveJoueurVsMachine(_, _, _):-write('Aucun pion sur le Khan, vous pouvez bouger n importe quel pion !'),nl,
					retract(khan(_)), asserta(khan(0)),
					retractall(possibleMoveList(_)),
					deplacementJoueurVsMachine,!.

%%Recherche de la liste des pions deplacables MachinevsMachine
possibleMovesMachineVsMachine(PionBoard ,Joueur):-boardGame(BG), khan(Khan), 
								checkMatricePosition(BG,PionBoard,Joueur,Khan).
possibleMovesMachineVsMachine(PionBoard ,Joueur):- checkNbPionJoueur(N, Joueur, PionBoard), autreMoveMachineVsMachine(PionBoard, Joueur, N).

autreMoveMachineVsMachine(_, _, _):-write('Deplacement suite a un bloquage.'),nl,
					retract(khan(_)), asserta(khan(0)),
					retractall(possibleMoveList(_)),
					deplacementMachineVsMachine,!.

%%Boucle de parcours de la matrice pour trouver les pions du joueur et verifier leur non blocage
checkMatricePosition([],[],_,_):-retract(iterator(_)), asserta(iterator(0)).
checkMatricePosition([T1|Q1],[T2|Q2],Joueur,0):-iterator(Ligne), retract(iterator(Ligne)), I is Ligne+1, asserta(iterator(I)),
											checkLignePosition(1,T1,Joueur,T2,1),
											checkLignePosition(2,T1,Joueur,T2,1),
											checkLignePosition(3,T1,Joueur,T2,1),
											checkMatricePosition(Q1,Q2,Joueur,0).
checkMatricePosition([T1|Q1],[T2|Q2],Joueur,Khan):- iterator(Ligne), retract(iterator(Ligne)), I is Ligne+1, asserta(iterator(I)),
												checkLignePosition(Khan,T1,Joueur,T2,1),
												checkMatricePosition(Q1,Q2,Joueur,Khan).
checkLignePosition(_,[],_,[],_).
checkLignePosition(Khan,[Khan|Q1],Joueur,[Joueur|Q2],Colonne):- iterator(L), boardPion(BoardPion), 
											checkDeplacable(L, Colonne, BoardPion, Joueur, Khan, []),
											asserta(possibleMoveList([L,Colonne])),
											C is Colonne+1, checkLignePosition(Khan,Q1,Joueur,Q2,C).
checkLignePosition(Khan,[_|Q1],Joueur,[_|Q2], Colonne):- C is Colonne+1,
											checkLignePosition(Khan,Q1,Joueur,Q2,C).	

checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 0, _):-checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 1, []),!.
checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 0, _):-checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 2, []),!.
checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 0, _):-checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 3, []),!.
													
checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 1, OldMov):-Ligne\=1, L is Ligne-1, 
													\+checkMoveInMatrice(L,Colonne, OldMov), 
													valeurCase(L, Colonne, PionBoard, R), R\=Joueur,!.
checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 1, OldMov):-Ligne\=6, L is Ligne+1, 
													\+checkMoveInMatrice(L,Colonne, OldMov), 
													valeurCase(L, Colonne, PionBoard, R), R\=Joueur,!.
checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 1, OldMov):-Colonne\=6, C is Colonne+1, 
													\+checkMoveInMatrice(Ligne,C, OldMov), 
													valeurCase(Ligne, C, PionBoard, R), R\=Joueur,!.
checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 1, OldMov):-Colonne\=1, C is Colonne-1, 
													\+checkMoveInMatrice(Ligne,C, OldMov), 
													valeurCase(Ligne, C, PionBoard, R), R\=Joueur,!.

checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 2, OldMov):-Ligne\=1, L is Ligne-1, \+checkMoveInMatrice(L,Colonne, OldMov), 
													valeurCase(L, Colonne, PionBoard, R), R==0, append(OldMov,[[L,Colonne]],NewOldMov),
													checkDeplacable(L, Colonne, PionBoard, Joueur, 1, NewOldMov).
checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 2, OldMov):-Ligne\=6, L is Ligne+1, \+checkMoveInMatrice(L,Colonne, OldMov), 
													valeurCase(L, Colonne, PionBoard, R), R==0, append(OldMov,[[L,Colonne]], NewOldMov),
													checkDeplacable(L, Colonne, PionBoard, Joueur, 1, NewOldMov).
checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 2, OldMov):-Colonne\=1, C is Colonne-1, \+checkMoveInMatrice(Ligne,C, OldMov), 
													valeurCase(Ligne, C, PionBoard, R), R==0, append(OldMov,[[Ligne,C]],NewOldMov),
													checkDeplacable(Ligne, C, PionBoard, Joueur, 1, NewOldMov).
checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 2, OldMov):-Colonne\=6, C is Colonne+1, \+checkMoveInMatrice(Ligne,C, OldMov), 
													valeurCase(Ligne, C, PionBoard, R), R==0, append(OldMov,[[Ligne,C]],NewOldMov),
													checkDeplacable(Ligne, C, PionBoard, Joueur, 1, NewOldMov).

checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 3, OldMov):-Ligne\=1, L is Ligne-1, \+checkMoveInMatrice(L,Colonne, OldMov), 
													valeurCase(L, Colonne, PionBoard, R), R==0, append(OldMov,[[L,Colonne]],NewOldMov),
													checkDeplacable(L, Colonne, PionBoard, Joueur, 2, NewOldMov).
checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 3, OldMov):-Ligne\=6, L is Ligne+1, \+checkMoveInMatrice(L,Colonne, OldMov), 
													valeurCase(L, Colonne, PionBoard, R), R==0, append(OldMov,[[L,Colonne]], NewOldMov),
													checkDeplacable(L, Colonne, PionBoard, Joueur, 2, NewOldMov).
checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 3, OldMov):-Colonne\=1, C is Colonne-1, \+checkMoveInMatrice(Ligne,C, OldMov), 
													valeurCase(Ligne, C, PionBoard, R), R==0, append(OldMov,[[Ligne,C]],NewOldMov),
													checkDeplacable(Ligne, C, PionBoard, Joueur, 2, NewOldMov).
checkDeplacable(Ligne, Colonne, PionBoard,Joueur, 3, OldMov):-Colonne\=6, C is Colonne+1, \+checkMoveInMatrice(Ligne,C, OldMov), 
													valeurCase(Ligne, C, PionBoard, R), R==0, append(OldMov,[[Ligne,C]],NewOldMov),
													checkDeplacable(Ligne, C, PionBoard, Joueur, 2, NewOldMov).

%%Recherche de la liste des cases accessibles pour un pion donné
accessibleMoves(Ligne, Colonne, Joueur, AccessibleMoveList):- boardPion(BoardPion), boardGame(BoardGame),
														valeurCase(Ligne, Colonne, BoardGame, Khan),
														checkAccessible(Ligne, Colonne, BoardPion, Joueur, Khan, []),
														setof(Temp, accessibleMoveList(Temp), AccessibleMoveList),
														retractall(accessibleMoveList(_)), !.
													
checkAccessible(Ligne, Colonne, PionBoard,Joueur, 1, OldMov):- iterator(I), I==0,  retract(iterator(_)), asserta(iterator(1)),
													Ligne\=1, L is Ligne-1, valeurCase(L, Colonne, PionBoard, R), R\=Joueur,
													\+checkMoveInMatrice(L,Colonne, OldMov),
													asserta(accessibleMoveList([L,Colonne])), checkAccessible(Ligne, Colonne, PionBoard, Joueur, 1, OldMov).
checkAccessible(Ligne, Colonne, PionBoard,Joueur, 1, OldMov):- iterator(I), I==1,  retract(iterator(_)), asserta(iterator(2)),
													Ligne\=6, L is Ligne+1, valeurCase(L, Colonne, PionBoard, R), R\=Joueur,
													\+checkMoveInMatrice(L,Colonne, OldMov),
													asserta(accessibleMoveList([L,Colonne])), checkAccessible(Ligne, Colonne, PionBoard, Joueur, 1, OldMov).
checkAccessible(Ligne, Colonne, PionBoard,Joueur, 1, OldMov):- iterator(I), I==2,  retract(iterator(_)), asserta(iterator(3)), 
													Colonne\=6, C is Colonne+1, valeurCase(Ligne, C, PionBoard, R), R\=Joueur,
													\+checkMoveInMatrice(Ligne,C, OldMov),
													asserta(accessibleMoveList([Ligne,C])), checkAccessible(Ligne, Colonne, PionBoard, Joueur, 1, OldMov).
checkAccessible(Ligne, Colonne, PionBoard,Joueur, 1, OldMov):- iterator(I), I==3, retract(iterator(_)), asserta(iterator(0)),
													Colonne\=1, C is Colonne-1, valeurCase(Ligne, C, PionBoard, R), R\=Joueur,
													\+checkMoveInMatrice(Ligne,C, OldMov),
													asserta(accessibleMoveList([Ligne,C])).
checkAccessible(_, _, _,_, 1,_):-retract(iterator(_)), asserta(iterator(0)).

checkAccessible(Ligne, Colonne, PionBoard,Joueur, 2, OldMov):- iterator(I), I==0, retract(iterator(_)), asserta(iterator(1)),
													Ligne\=1, L is Ligne-1, valeurCase(L, Colonne, PionBoard, R), R==0,
													\+checkMoveInMatrice(L,Colonne, OldMov),
													append(OldMov,[[L,Colonne]],NewOldMov),
													retract(iterator(_)), asserta(iterator(0)),
													checkAccessible(L, Colonne, PionBoard, Joueur, 1, NewOldMov),
													retract(iterator(_)), asserta(iterator(1)),
													checkAccessible(Ligne, Colonne, PionBoard, Joueur, 2, OldMov).
checkAccessible(Ligne, Colonne, PionBoard,Joueur, 2, OldMov):- iterator(I), I==1, retract(iterator(_)), asserta(iterator(2)), 
													Ligne\=6, L is Ligne+1, valeurCase(L, Colonne, PionBoard, R), R==0,
													\+checkMoveInMatrice(L,Colonne, OldMov),
													append(OldMov,[[L,Colonne]],NewOldMov),
													retract(iterator(_)), asserta(iterator(0)),
													checkAccessible(L, Colonne, PionBoard, Joueur, 1, NewOldMov),
													retract(iterator(_)), asserta(iterator(2)),
													checkAccessible(Ligne, Colonne, PionBoard, Joueur, 2, OldMov).
checkAccessible(Ligne, Colonne, PionBoard,Joueur, 2, OldMov):- iterator(I), I==2, retract(iterator(_)), asserta(iterator(3)), 
													Colonne\=1, C is Colonne-1, valeurCase(Ligne, C, PionBoard, R), R==0,
													\+checkMoveInMatrice(Ligne,C, OldMov),
													append(OldMov,[[Ligne,C]],NewOldMov),													
													retract(iterator(_)), asserta(iterator(0)),
													checkAccessible(Ligne, C, PionBoard, Joueur, 1, NewOldMov),
													retract(iterator(_)), asserta(iterator(3)),
													checkAccessible(Ligne, Colonne, PionBoard, Joueur, 2, OldMov).
checkAccessible(Ligne, Colonne, PionBoard,Joueur, 2, OldMov):- iterator(I), I==3, 
													Colonne\=6, C is Colonne+1, valeurCase(Ligne, C, PionBoard, R), R==0,
													\+checkMoveInMatrice(Ligne,C, OldMov),
													append(OldMov,[[Ligne,C]],NewOldMov),																								
													retract(iterator(_)), asserta(iterator(0)),
													checkAccessible(Ligne, C, PionBoard, Joueur, 1, NewOldMov),
													retract(iterator(_)), asserta(iterator(0)).
checkAccessible(_, _, _,_, 2,_):-retract(iterator(_)), asserta(iterator(0)). 

checkAccessible(Ligne, Colonne, PionBoard,Joueur, 3, _):- iterator(I), I==0, retract(iterator(_)), asserta(iterator(1)),
													Ligne\=1, L is Ligne-1, valeurCase(L, Colonne, PionBoard, R), R==0,
													append([],[[L,Colonne]],NewOldMov),												
													retract(iterator(_)), asserta(iterator(0)),
													checkAccessible(L, Colonne, PionBoard, Joueur, 2, NewOldMov),
													retract(iterator(_)), asserta(iterator(1)),
													checkAccessible(Ligne, Colonne, PionBoard, Joueur, 3, _).
checkAccessible(Ligne, Colonne, PionBoard,Joueur, 3, _):- iterator(I), I==1, retract(iterator(_)), asserta(iterator(2)), 
													Ligne\=6, L is Ligne+1, valeurCase(L, Colonne, PionBoard, R), R==0,
													append([],[[L,Colonne]],NewOldMov),												
													retract(iterator(_)), asserta(iterator(0)),
													checkAccessible(L, Colonne, PionBoard, Joueur, 2, NewOldMov),
													retract(iterator(_)), asserta(iterator(2)),
													checkAccessible(Ligne, Colonne, PionBoard, Joueur, 3, _).
checkAccessible(Ligne, Colonne, PionBoard,Joueur, 3,_):- iterator(I), I==2, retract(iterator(_)), asserta(iterator(3)), 
													 Colonne\=1, C is Colonne-1, valeurCase(Ligne, C, PionBoard, R), R==0,
													append([],[[Ligne,C]],NewOldMov),												
													retract(iterator(_)), asserta(iterator(0)),
													checkAccessible(Ligne, C, PionBoard, Joueur, 2, NewOldMov),
													retract(iterator(_)), asserta(iterator(3)),
													checkAccessible(Ligne, Colonne, PionBoard, Joueur, 3, _).
checkAccessible(Ligne, Colonne, PionBoard,Joueur, 3, _):- iterator(I), I==3,  
													Colonne\=6, C is Colonne+1, valeurCase(Ligne, C, PionBoard, R), R==0,
													append([],[[Ligne,C]],NewOldMov),												
													retract(iterator(_)), asserta(iterator(0)),
													checkAccessible(Ligne, C, PionBoard, Joueur, 2, NewOldMov),
													retract(iterator(_)), asserta(iterator(0)),!.
checkAccessible(_, _, _,_, 3,_):-retract(iterator(_)), asserta(iterator(0)),!. 

%%Boucle de pause pour nous permettre d analyser les mouvements lors d une partie MachinevsMachine
pause:-nl,nl,write('Progamme en pause.'),nl,nl,sleep(6).

%%Boucle de deplacement Machine vs Machine
deplacementMachineVsMachine:- \+finDeJeu, joueur(Joueur), Joueur==1, write('L IA 1 : '), nl, nl, boardPion(BoardPion),
			possibleMovesMachineVsMachine(BoardPion,Joueur),setof(Temp, possibleMoveList(Temp), PossibleMoveList), deplacementMachine(Joueur,PossibleMoveList),
			retract(joueur(_)), asserta(joueur(2)),pause, deplacementMachineVsMachine,!.
deplacementMachineVsMachine:- \+finDeJeu, joueur(Joueur), Joueur==2, write('L IA 2 : '), nl, nl, boardPion(BoardPion),
			possibleMovesMachineVsMachine(BoardPion,Joueur),setof(Temp, possibleMoveList(Temp), PossibleMoveList), deplacementMachine(Joueur,PossibleMoveList),
			retract(joueur(_)), asserta(joueur(1)),pause, deplacementMachineVsMachine,!.

%%Boucle de deplacement Joueur vs Machine
deplacementJoueurVsMachine:- \+finDeJeu, joueur(Joueur), Joueur==1, write('Le joueur rouge : '), nl, nl, boardPion(BoardPion),
			possibleMovesJoueurVsMachine(BoardPion,Joueur), setof(Temp, possibleMoveList(Temp), PossibleMoveList), deplacementJoueur(Joueur,PossibleMoveList),
			retract(joueur(_)), asserta(joueur(2)), deplacementJoueurVsMachine,!.
deplacementJoueurVsMachine:- \+finDeJeu, joueur(Joueur), Joueur==2, write('L IA : '), nl, nl, boardPion(BoardPion),
			possibleMovesJoueurVsMachine(BoardPion,Joueur), setof(Temp, possibleMoveList(Temp), PossibleMoveList), deplacementMachine(Joueur,PossibleMoveList),
			retract(joueur(_)), asserta(joueur(1)) , deplacementJoueurVsMachine,!.

%%Boucle de deplacement Joueur vs Joueur
deplacement:- \+finDeJeu, joueur(Joueur), Joueur==1, write('Le joueur rouge : '), nl, nl, boardPion(BoardPion),
			possibleMoves(BoardPion,Joueur), setof(Temp, possibleMoveList(Temp), PossibleMoveList), deplacementJoueur(Joueur,PossibleMoveList),
			retract(joueur(_)), asserta(joueur(2)) , deplacement.
deplacement:- \+finDeJeu, joueur(Joueur), Joueur==2, write('Le joueur ocre : '), nl, nl, boardPion(BoardPion),
			possibleMoves(BoardPion,Joueur), setof(Temp, possibleMoveList(Temp), PossibleMoveList), deplacementJoueur(Joueur,PossibleMoveList),
			retract(joueur(_)), asserta(joueur(1)) , deplacement.
deplacement.

%%Verification condition de fin de jeu
finDeJeu:-khalistaOcre(L,C),boardPion(BP),valeurCase(L,C,BP,Resultat),Resultat\=2,
		nl,write('********************'),nl,write('Rouge Gagne !! '),nl,write('********************'),stop.
finDeJeu:-khalistaRouge(L,C),boardPion(BP),valeurCase(L,C,BP,Resultat),Resultat\=1,
		nl,write('********************'),nl,write('Ocre Gagne !! '),nl,write('********************'),stop.

%%Predicat d IA pour verifier qu on peut prendre la kalista adverse
khalistaMangeable([]).
khalistaMangeable([[L,C]|Q]):-joueur(Joueur),accessibleMoves(L, C, Joueur, AccessibleMoveList),
							testKhalista(AccessibleMoveList,L,C),khalistaMangeable(Q).
khalistaMangeable(_).

testKhalista([],_,_).
testKhalista([[L,C]|Q],Lpion,Cpion):-testKhalistaLigne(L,C,Lpion,Cpion),testKhalista(Q,Lpion,Cpion).
testKhalista(_,_,_).

testKhalistaLigne(Ligne,Colonne,Lpion,Cpion):-joueur(Joueur),Joueur=1,khalistaOcre(L,C),Ligne=L,Colonne=C,retract(ligneColonne(_,_)),asserta(ligneColonne(Lpion,Cpion)),asserta(ligneColonne(L,C)).
testKhalistaLigne(Ligne,Colonne,Lpion,Cpion):-joueur(Joueur),Joueur=2,khalistaRouge(L,C),Ligne=L,Colonne=C,retract(ligneColonne(_,_)),asserta(ligneColonne(Lpion,Cpion)),asserta(ligneColonne(L,C)).
testKhalistaLigne(_,_,_,_).

%%Deplacement d IA avec pour principe de se rapprocher le plus possible de la khalista adverse (voir calcul suivant)
deplacementIA([]).
deplacementIA([[Lold,Cold]|Q]):-joueur(Joueur),accessibleMoves(Lold, Cold, Joueur, AccessibleMoveList),
					scoreDeplacement(AccessibleMoveList,Lold,Cold),deplacementIA(Q).
deplacementIA(_).

scoreDeplacement([],_,_).
scoreDeplacement([[L,C]|Q],Lold,Cold):- scoreDeplacementLigne(L,C,Lold,Cold),scoreDeplacement(Q,Lold,Cold).
scoreDeplacement([_|Q],Lold,Cold):-scoreDeplacement(Q,Lold,Cold).

scoreDeplacementLigne(L,C,Lold,Cold):- joueur(Joueur),Joueur=1,khalistaOcre(Lkha,Ckha),score(Lkha,Ckha,L,C,Resultat),
													scoreEnr(ScorePrec,_,_,_,_),!,ScorePrec>Resultat,retract(scoreEnr(_,_,_,_,_)),
													asserta(scoreEnr(Resultat,L,C,Lold,Cold)).
scoreDeplacementLigne(L,C,Lold,Cold):- joueur(Joueur),Joueur=2,khalistaRouge(Lkha,Ckha),score(Lkha,Ckha,L,C,Resultat),
													scoreEnr(ScorePrec,_,_,_,_),!,ScorePrec>Resultat,retract(scoreEnr(_,_,_,_,_)),
													asserta(scoreEnr(Resultat,L,C,Lold,Cold)).
scoreDeplacementLigne(_,_,_,_).

score(Lkha,Ckha,L,C,Resultat):- valAbsMoins(Lkha,L,Tmpl),valAbsMoins(Ckha,C,Tmpc),Tmp is Tmpl + Tmpc, malus(Tmp,L,C,Resultat).

valAbsMoins(A,B,Resultat):- (A-B)<0,Resultat is (B-A).
valAbsMoins(A,B,Resultat):- Resultat is (A-B).

malus(Tmp,L,C,Resultat):- boardGame(BG),valeurCase(L,C,BG,R),R \= Tmp,Resultat is Tmp+3.
malus(Tmp,_,_,Resultat):-Resultat is Tmp.

%%Sous boucle de deplacement IA avec gestion de nos meilleurs coups
deplacementMachine(Joueur, PossibleMoveList):-asserta(ligneColonne(0,0)),khalistaMangeable(PossibleMoveList),ligneColonne(L,C),retract(ligneColonne(_,_)),
						L\=0,boardGame(BG), boardPion(BoardPion),ligneColonne(Lpion,Cpion),retract(ligneColonne(_,_)),
						modificationMatrice(Lpion, Cpion, 0, BoardPion, Temp),
						modificationMatrice(L, C, Joueur, Temp, Result),						
						retract(boardPion(_)), asserta(boardPion(Result)),								
						modificationKhalista(Lpion, Cpion,L,C,Joueur), 
						modificationKhan(L,C,BG),			
						nl, afficheBoard, retractall(possibleMoveList(_)),nl,!.
deplacementMachine(Joueur, PossibleMoveList):-asserta(scoreEnr(50,_,_,_,_)),deplacementIA(PossibleMoveList),
						scoreEnr(Resultat,L,C,Lpion,Cpion), retract(scoreEnr(_,_,_,_,_)),
						Resultat<50,boardGame(BG), boardPion(BoardPion),
						write('deplacemenet du pion situe en : '),write(Lpion),write(' '),write(Cpion),nl,nl,
						write('jusqu en : '),write(L),write(' '),write(C),nl,nl,
						modificationMatrice(Lpion, Cpion, 0, BoardPion, Temp),
						modificationMatrice(L, C, Joueur, Temp, Result),						
						retract(boardPion(_)), asserta(boardPion(Result)),								
						modificationKhalista(Lpion, Cpion,L,C,Joueur), 
						modificationKhan(L,C,BG),
						khan(Khan),write('Valeur du nouveau Khan : '),write(Khan),nl,nl,				
						nl, afficheBoard, retractall(possibleMoveList(_)),nl,!.
						%deplacement aleatoire

%%Sous boucle de deplacement Joueur avec affichage des listes de pions deplacables et les accesibles a partir de ceux ci
deplacementJoueur(Joueur, PossibleMoveList):-boardGame(BG), boardPion(BoardPion), 
						write('Actuellement le khan est situe sur une case de type : '),khan(Khan),write(Khan),nl,nl,
						write('Liste des cases deplacables'), nl, nl, affichageChoix(PossibleMoveList, Np),
						nl, write('Veuillez selectionner le numero du pion a bouger : '), nl,
						read(P), P>=1, P=<Np, nl,
						write('          1          2          3          4          5          6'),nl,nl,
						afficheboard(BG, BoardPion),nl,
						write('Liste des cases d arrivee accesibles'), nl, nl, 
						valeurCaseLigne(P, PossibleMoveList, [Ligne, Colonne]),
						accessibleMoves(Ligne, Colonne, Joueur, AccessibleMoveList), affichageChoix(AccessibleMoveList, Na),
						nl, write('Veuillez selectionner votre case d arrivee : '),nl,  
						read(A), A>=1, A=<Na, nl, 
						valeurCaseLigne(A, AccessibleMoveList, [L, C]),
						modificationMatrice(Ligne, Colonne, 0, BoardPion, Temp),
						modificationMatrice(L, C, Joueur, Temp, Result),						
						retract(boardPion(_)), 
						asserta(boardPion(Result)),								
						modificationKhalista(Ligne, Colonne,L,C,Joueur),
						modificationKhan(L,C,BG),						
						nl, afficheBoard, retractall(possibleMoveList(_)),nl,!.

deplacementJoueur(Joueur, PossibleMoveList):- nl, write('Mauvaise saisie, veuillez recommencer.'), nl, nl,
											deplacementJoueur(Joueur, PossibleMoveList).

%Modififcation Khalista
modificationKhalista(Ligne,Colonne,L,C,1):-retract(khalistaRouge(Ligne,Colonne)), asserta(khalistaRouge(L,C)).
modificationKhalista(Ligne,Colonne,L,C,2):-retract(khalistaOcre(Ligne,Colonne)), asserta(khalistaOcre(L,C)).
modificationKhalista(_,_,_,_,_).

%Modification du khan
modificationKhan(L,C,BG):-valeurCase(L,C,BG,Resultat),retract(khan(_)), asserta(khan(Resultat)).

%Calcul du nombre de pion dun joueur
checkNbPionJoueur(0,_,[]).
checkNbPionJoueur(N,Joueur,[T|Q]):- checkNbPionJoueurLigne(R1,Joueur, T), checkNbPionJoueur(R2,Joueur,Q), N is R1+R2.
checkNbPionJoueurLigne(0,_, []).
checkNbPionJoueurLigne(N,Joueur, [Joueur|Q]):- checkNbPionJoueurLigne(R1,Joueur,Q), N is R1+1.
checkNbPionJoueurLigne(N,Joueur, [_|Q]):-checkNbPionJoueurLigne(N,Joueur,Q).

%%Verification presence des coordonnees dans la matrice
checkMoveInMatrice(L,C, [[L,C]|_]).
checkMoveInMatrice(L,C, [_|Q]):-checkMoveInMatrice(L,C, Q).

%%Ajouter un pion
ajoutPion(Joueur):-nl,write('Placement du sbire sur la case : '),khan(Khan),write(Khan), nl,nl, boardPion(BoardPion),
				write('Numero de ligne : '), nl, read(Ligne), nl, retract(error(_)), asserta(error(1)), Ligne>=1, Ligne=<6,
				write('Numero de colonne : '), nl, read(Colonne), nl, retract(error(_)), asserta(error(2)), Colonne>=1, Colonne=<6,
				retract(error(_)), asserta(error(3)), valeurCase(Ligne, Colonne, BoardPion, R), R==0,
				ajouterPion(Joueur,Ligne,Colonne),retract(error(_)), asserta(error(0)).
ajoutPion(Joueur):- error(E), E==1, write('Numero de ligne doit etre compris entre 1 et 6'), nl, nl, retract(error(_)), asserta(error(0)), ajoutPion(Joueur).
ajoutPion(Joueur):- error(E), E==2, write('Numero de colonne doit etre compris entre 1 et 6'), nl, nl, retract(error(_)), asserta(error(0)), ajoutPion(Joueur).
ajoutPion(Joueur):- error(E), E==3, write('Case deja occupee'), nl, nl, retract(error(_)), asserta(error(0)), ajoutPion(Joueur).

ajouterPion(Joueur,Ligne,Colonne):- boardGame(BG),khan(Khan),valeurCase(Ligne,Colonne,BG,Resultat),
				Resultat==Khan,boardPion(X),
				modificationMatrice(Ligne, Colonne, Joueur, X, Temp),
				retract(boardPion(X)),asserta(boardPion(Temp)),afficheboard(BG,Temp).	
ajouterPion(Joueur,_,_):- write('Cette case ne correspond pas au Khan.'), nl, nl, ajoutPion(Joueur).


%%Lancement du du jeu
main:-write('Bienvenue au jeu du Khan !'), nl,nl,
	write('Veuillez choisir votre mode de jeu: 1 pour joueur contre un autre joueur, 2 pour joueur contre l IA,3 pour voir deux IA jouer.'),nl,
	read(Mode), Mode>=1, Mode=<3,!,modeDeJeu(Mode).
main:-write('Mauvaise saisie, veuillez recommencer.'), nl, nl, main.

%%Pour eviter de remplir la matrice de jeu
/*initialisationDejaRemplit(_):-write('Veuillez choisir votre orientation : un nombre entre 1 et 4'), nl,
	read(O), O>=1, O=<4,
	randomize,
	asserta(error(0)),
	asserta(khan(0)),
	asserta(joueur(1)),
	asserta(iterator(0)),
	asserta(khalistaRouge(1,6)),
	asserta(khalistaOcre(6,1)),
	matricePleine(Result),
	asserta(boardPion(Result)),		
	board(O,X),asserta(boardGame(X)),			
	afficheBoard,nl,nl.
initialisationDejaRemplit(_):-write('Mauvaise saisie, veuillez recommencer.'), nl, nl, initialisationDejaRemplit(_).*/

%%Choix du mode de jeu
modeDeJeu(Mode):- Mode=1,
	initialisation(Mode),
	deplacement,!.

modeDeJeu(Mode):- Mode=2,
	initialisation(Mode),
	deplacementJoueurVsMachine,!.

modeDeJeu(Mode):- Mode=3,
	initialisation(Mode),
	deplacementMachineVsMachine,!.

%%Initialisation du jeu				
initialisation(Mode):-write('Veuillez choisir votre orientation : un nombre entre 1 et 4'), nl,
	read(O), O>=1, O=<4,
	randomize,
	asserta(error(0)),
	asserta(khan(0)),				
	asserta(joueur(1)),
	asserta(iterator(0)),
	board(O,X),asserta(boardGame(X)),
	matriceVide(Y),
	lireJoueur(Y,Result,0,Mode),
	asserta(boardPion(Result)),				
	afficheBoard,nl,nl,!.
initialisation(Mode):-write('Mauvaise saisie, veuillez recommencer.'), nl, nl, initialisation(Mode).
