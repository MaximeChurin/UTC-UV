ceuc.app <- function(Xapp, zapp){
  #Cast des paramètres au format attendu
  Xapp <- as.matrix(Xapp)
  zapp <- as.vector(zapp)
  
  #Initialisation du compteur pour la boucle
  i <- 1
  
  #Initialisation de g au nombre de classes du jeu de données (voir hypothèse dans le rapport)
  g <- max(zapp)
  
  #Initialisation de p au nombre de variables du jeu de données
  p <- dim(Xapp)[2]
  
  #Initialisation à 0 du vecteur de taille g stockant le nombre d'individus pour chaque classe 
  diviseur <- seq(0,0,length.out=g)
  
  #Initialisation à 0 de la matrice de sortie des paramètres estimés de taille g x p
  mu <- matrix(0,g,p)
  
  #Parcours de toutes les lignes du tableau individus-variables
  for (i in 1:dim(Xapp)[1]) {
    
    #Incrémentation de la ligne de la matrice mu correspondant à la classe de l'individu i avec les valeurs de ses variables
    mu[zapp[i],] <- mu[zapp[i],] + Xapp[i,]
    
    #Incrémentation du nombre d'individus de la classe de l'individu i
    diviseur[zapp[i]] <- diviseur[zapp[i]] + 1
  }
  
  #Pour chaque ligne de la matrice mu on divise la valeur de chaque variable par le nombre d'individus de la classe i
  for (i in 1:g) {
    mu[i,] = mu[i,] / diviseur[i]
  }
  
  #Retourne la matrice des paramètres estimés
  mu
}

ceuc.val <- function(mu, Xtst){
  
  #Cast des paramètres au format attendu
  mu <- as.matrix(mu)
  Xtst <- as.matrix(Xtst)
  
  #Initialisation de n au nombre d'individus de l'ensemble de test
  n <- dim(Xtst)[1]
  
  #Utilisation de la fonction fournie pour récupérer les distances euclidiennes au carré
  #de chaque individu pour toutes les classes g du jeu de données : distance est un tableau 
  #de taille g x n
  distance <- distXY(mu, Xtst)
  
  #Initialisation du vecteur de taille n pour le stockage des classes prédites
  etiquettes <- vector(length = n)
  
  #Parcours de toutes les colonnes (individus de l'ensemble de test) de la matrice distance 
  for (i in 1:n) {
    
    #Associe à chaque i l'indice de la ligne/classe de la plus petite distance
    etiquettes[i] <- which.min(distance[,i])
  }
  
  #Retourne le vecteur associant à chaque individu de l'ensemble de test sa classe prédite
  etiquettes
}

kppv.val <- function(Xapp, zapp, K, Xtst){
  
  #Cast des paramètres au format attendu
  Xapp <- as.matrix(Xapp)
  Xtst <- as.matrix(Xtst)
  zapp <- as.vector(zapp)
  
  #Initialisation de n_test au nombre d'individus de l'ensemble de test
  n_test <- dim(Xtst)[1]
  
  #Initialisation du vecteur de taille n_test pour le stockage des classes prédites
  etiquettes <- vector(length = n_test)
  
  #Initialisation de g au nombre de classes du jeu de données (voir hypothèse dans le rapport)
  g <- max(zapp)
  
  #Utilisation de la fonction fournie pour récupérer les distances euclidiennes au carré
  #de chaque individu de l'ensemble de test à tous les individus de l'ensemble d'apprentissage : distance est un tableau 
  #de taille n_test x n_apprentissage
  distance <- distXY(Xtst, Xapp)
  
  #Le apply de "order" va créer une matrice de dimension n_apprentissage x n_test
  #ou les lignes de la i eme colonne/individu i de l'ensemble de test représenteront 
  #les indices des individus de l'ensemble d'apprentissage triés par distance croissante
  #Le head va ensuite gardé que les K premières lignes pour chaque colonne de la matrice
  #soit les K plus proches voisins de chaque colonne/individu i de l'ensemble de test
  index_points_voisins <- head(apply(distance, 1, order), K)
  
  #Associe à chaque valeur d'indice de ligne/individu de l'ensemble d'apprentissage sa classe
  classe_points_voisins <- matrix(zapp[index_points_voisins], nrow=nrow(index_points_voisins))
  
  #Calcule pour chaque colonne/individu de l'ensemble de test le nombre d'occurrence de chaque valeur
  #de classe
  frequences <- apply(classe_points_voisins, 2, tabulate)
  
  #Parcours du tableau frequences pour tous les individus de l'ensemble de test
  for (i in 1:n_test) {
    
    #Associe à chaque i la classe la plus fréquente parmi les classes des K plus proches voisins
    etiquettes[i] <- which.max(frequences[[i]])
  }
  
  #Retourne le vecteur associant à chaque individu de l'ensemble de test sa classe prédite
  etiquettes
}

kppv.tune <- function(Xapp, zapp, Xval, zval, nppv){
  
  #Cast des paramètres au format attendu
  Xapp <- as.matrix(Xapp)
  Xval <- as.matrix(Xval)
  zapp <- as.vector(zapp)
  zval <- as.vector(zval)
  
  #Initialisation du vecteur de taille nppv pour le stockage des correspondances entre le vecteur
  #des classes de l'ensemble de validation et le vecteur des classes prédites pour les 
  #différentes valeurs de K
  Kopt <- vector(length = length(nppv))
  
  #Boucle pour chaque valeur K de voisins à tester
  for (i in 1:length(nppv)){
    
    #Calcul du vecteur des classes prédites pour K=nppv[i]
    etiquettes <- kppv.val(Xapp, zapp, nppv[i], Xval)
    
    #Stocke le nombre d'occurences similaires entre le vecteur des classes de l'ensemble de validation et etiquettes
    Kopt[i] <- sum(zval==etiquettes)
  }
  
  #Retourne le nombres de voisins avec le meilleur résultat soit la valeur du vecteur de voisins à tester
  #d'indice au vecteur de classes prédites le plus similaire à celui de validation
  nppv[which.max(Kopt)]
}

#Fonctions fournies
front.ceuc <- function(X, z, mu, discretisation=50)
{
  deltaX <- (max(X[,1])-min(X[,1]))/discretisation
  deltaY <- (max(X[,2])-min(X[,2]))/discretisation
  minX <- min(X[,1])-deltaX
  maxX <- max(X[,1])+deltaX
  minY <- min(X[,2])-deltaY
  maxY <- max(X[,2])+deltaY
  
  # grille d'affichage 
  grilleX <- seq(from=minX,to=maxX,by=deltaX)
  naffX <- length(grilleX)
  grilleY <- seq(from=minY,to=maxY,by=deltaY)
  naffY <- length(grilleY)
  grille <- cbind(rep.int(grilleX,times=rep(naffY,naffX)),rep(grilleY,naffX))
  
  # calcul des valeurs de la fonction 
  valf <- ceuc.val(mu, grille)
  plot(X, col=c("red","green","blue","magenta","orange")[z], asp=1)
  contour(grilleX, grilleY, matrix(valf,nrow=naffX,byrow=T), add=T, drawlabels=FALSE, levels=1.5)
}

front.kppv <- function(X, z, K, discretisation=50)
{
  deltaX <- (max(X[,1])-min(X[,1]))/discretisation
  deltaY <- (max(X[,2])-min(X[,2]))/discretisation
  minX <- min(X[,1])-deltaX
  maxX <- max(X[,1])+deltaX
  minY <- min(X[,2])-deltaY
  maxY <- max(X[,2])+deltaY
  
  # grille d'affichage 
  grilleX <- seq(from=minX,to=maxX,by=deltaX)
  naffX <- length(grilleX)
  grilleY <- seq(from=minY,to=maxY,by=deltaY)
  naffY <- length(grilleY)
  grille <- cbind(rep.int(grilleX,times=rep(naffY,naffX)),rep(grilleY,naffX))
  
  # calcul des valeurs de la fonction 
  valf <- kppv.val(X, z, K, grille)
  plot(X, col=c("red","green","blue","magenta","orange")[z], asp=1)
  contour(grilleX, grilleY, matrix(valf,nrow=naffX,byrow=T), add=T, drawlabels=FALSE, levels=1.5)
}

distXY <- function(X, Y)
{
  nx <- dim(X)[1]
  ny <- dim(Y)[1]
  h.x <- rowSums(X^2)
  h.y <- rowSums(Y^2)
  ones.x <- rep(1,nx)
  ones.y <- rep(1,ny)
  D2xy <- h.x%*%t(ones.y) - 2*X %*% t(Y) + ones.x%*%t(h.y)
}