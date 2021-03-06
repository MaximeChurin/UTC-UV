#Apprentissage du mod�le par regression logistique
log.app <- function(Xapp, zapp, intr, epsi){
  n <- dim(Xapp)[1]
  p <- dim(Xapp)[2]
  
  Xapp <- as.matrix(Xapp)
  
  if (intr == T){
    Xapp <- cbind(rep(1,n),Xapp)
    p <- p + 1
  }
  
  targ <- matrix(as.numeric(zapp),nrow=n)
  targ[which(targ==2),] <- 0
  tXap <- t(Xapp)
  
  beta <- matrix(0,nrow=p,ncol=1)
  
  conv <- F
  iter <- 0
  while (conv == F){
    iter <- iter + 1
    bold <- beta
    
    prob <- postprob(beta, Xapp)
    #Calcul de la matrice diagonale gr�ce aux probabilit�s � posteriori des classes
    MatW <- diag(as.vector(prob * (1 - prob)))
    
    #Application de la formule de l'algorithme Newton-Raphson pour calculer le vecteur des poids
    beta <- bold + solve(tXap%*%MatW%*%Xapp)%*%tXap%*%(targ-prob)
    
    if (norm(beta-bold)<epsi){
      conv <- T
    }
  }
  
  prob <- postprob(beta, Xapp)
  out <- NULL
  out$beta <- beta
  out$iter <- iter
  #Affectation des probabilit� � posteriori de la classe 1
  out$logL <- prob
  
  out
}

#Cacul les probabilit�s a posteriori et les etiquettes pour un ensemble de test gr�ce aux param�tres estim�s
log.val <- function(beta, Xtst){
  m <- dim(Xtst)[1]
  p <- dim(beta)[1]
  pX <- dim(Xtst)[2]
  
  Xtst <- as.matrix(Xtst)
  
  if (pX == (p-1)){
    Xtst  <- cbind(rep(1,m),Xtst)
  }
  
  #Calcul des probabilit� � posteriori de la classe 1
  prob <- postprob(beta, Xtst)
  #R�cup�ration de la position maximale pour chaque ligne de la matrice entre les 
  #probabilit�s � posteriori de la classe 1 et de la classe 2
  pred <- max.col(cbind(prob, 1 - prob))
  
  out <- NULL
  out$prob <- prob
  out$pred <- pred
  
  return(out)
}

#Calcul des probabilit� � posteriori de la classe 1
postprob <- function(beta, X){
  X <- as.matrix(X)
  #Cacul par la m�thode du maximum de vraisemblance des probabilit� � posteriori de la classe 1
  prob <- exp(X%*%beta)/(1+exp(X%*%beta))
}

#Modification de l'espace du mod�le pour l'adapter � la regression logistique quadratique
transfrom.quadratique <- function(X){
  #Affectation du nombre de variables
  p <- dim(X)[2]
  
  #Boucle de p-1 it�rations
  for(j in 1:(p-1)){
    #Boucle de j+1 � p it�rations
    for(i in (j+1):p){
      #Calcul des diff�rentes combinaisons entre chaque couple de variables
      X<-cbind(X,X[,j]*X[,i])
    }
  }
  for(k in 1:p){
    #Calcul des carr�s des diff�rentes variables
    X<-cbind(X,X[,k]*X[,k])
  }
  X
}

prob.log <- function(param, X, z, niveaux){
  discretisation=50
  deltaX <- (max(X[,1]) -min(X[,1]))/discretisation
  deltaY <- (max(X[,2]) -min(X[,2]))/discretisation
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
  
  grille <- as.matrix(grille)
  
  # calcul des valeurs de la fonction 
  valf <- log.val(param, grille)$prob[,1]
  plot(X, col=c("red","green","blue","magenta","orange")[z])
  contour(grilleX, grilleY, matrix(valf,nrow=naffX,byrow=T), add=T, drawlabels=FALSE, levels=niveaux)
}

prob.log2 <- function(param, X, z, niveaux){
  discretisation=50
  deltaX <- (max(X[,1]) -min(X[,1]))/discretisation
  deltaY <- (max(X[,2]) -min(X[,2]))/discretisation
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
  grille <- cbind(grille, grille[,1]*grille[,2], grille[,1]^2, grille[,2]^2)
  
  grille <- as.matrix(grille)
  
  # calcul des valeurs de la fonction 
  valf <- log.val(param, grille)$prob[,1]
  plot(X, col=c("red","green","blue","magenta","orange")[z])
  contour(grilleX, grilleY, matrix(valf,nrow=naffX,byrow=T), add=T, drawlabels=FALSE, levels=niveaux)
}