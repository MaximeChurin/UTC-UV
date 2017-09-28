#Calcule la densité d'une loi normale multivariée pour un tableau de données
mvdnorm <- function(X, mu, Sigma){
  X <- as.matrix(X)
  
  n <- dim(X)[1]
  p <- dim(X)[2]
  
  B <- chol(Sigma)
  U <- (X-matrix(rep(mu,n),nrow=n,byrow=T))%*%ginv(B)
  
  dens <- exp(-rowSums(U*U)/2) * (2*pi)^(-p/2) / det(B)
}

#Apprentissage du modèle par analyse discriminante quadratique
adq.app <- function(Xapp, zapp){
  n <- dim(Xapp)[1]
  p <- dim(Xapp)[2]
  g <- max(unique(zapp))
  
  param <- NULL
  param$MCov <- array(0, c(p,p,g))
  param$mean <- array(0, c(g,p))
  param$prop <- rep(0, g)
  
  for (k in 1:g){
    xi <- Xapp[k == zapp,]
    
    #Calcul de la matrice de covariance des individus de la classe k
    param$MCov[,,k] <- cov(xi)
    #Calcul de la moyenne par variable des individus de la classe k
    param$mean[k,] <- apply(xi, 2, mean)
    #Calcul de la proportion d'individus de la classe k parmi l'ensemble des individus
    param$prop[k] <- dim(xi)[1] / n
  }
  
  param
}

#Apprentissage du modèle par analyse discriminante linéaire (homoscédasticité)
adl.app <- function(Xapp, zapp){
  n <- dim(Xapp)[1]
  p <- dim(Xapp)[2]
  g <- max(unique(zapp))
  
  param <- NULL
  MCov <- array(0, c(p,p))
  param$MCov <- array(0, c(p,p,g))
  param$mean <- array(0, c(g,p))
  param$prop <- rep(0, g)
  
  for (k in 1:g) {
    xi <- Xapp[k == zapp,]
    
    #Calcul de la moyenne par variable des individus de la classe k
    param$mean[k,] <- apply(xi, 2, mean)
    #Calcul de la moyenne par variable des individus de la classe k
    param$prop[k] <- dim(xi)[1] / n
    #Incrémentation de la matrice de covariance avec pondÃ©ration du nombre d'individus de la classe k
    MCov <- MCov + param$prop[k] * cov(xi)
  }

  for (k in 1:g) {
    #Recopie de la matrice de covariance pour chaque classe
    param$MCov[,,k] <- MCov
  }
  
  param
}


#Apprentissage du modèle par analyse discriminante : bayésien naïf
nba.app <- function(Xapp, zapp){
  n <- dim(Xapp)[1]
  p <- dim(Xapp)[2]
  g <- max(unique(zapp))
  
  param <- NULL
  param$MCov <- array(0, c(p,p,g))
  param$mean <- array(0, c(g,p))
  param$prop <- rep(0, g)
  
  for (k in 1:g) {
    xi <- Xapp[k == zapp,]
    
    #Calcul de la matrice de covariance par diagonalisation de la variance des variables des individus de la classe k
    param$MCov[,,k] <- diag(apply(xi, 2, var))
    #Calcul de la moyenne par variable des individus de la classe k
    param$mean[k,] <- apply(xi, 2, mean)
    #Calcul de la moyenne par variable des individus de la classe k
    param$prop[k] <- dim(xi)[1] / n
  }
  
  param
}

#Cacul les probabilités a posteriori et les etiquettes pour un ensemble de test grâce aux paramètres estimés
ad.val <- function(param, Xtst){
  n <- dim(Xtst)[1]
  p <- dim(Xtst)[2]
  g <- length(param$prop)
  
  out <- NULL
  
  prob <- matrix(0, nrow=n, ncol=g)
  deno <- 0
  
  for (k in 1:g) {
    #Calcul de la distribution conditionelle de la class k multiplié par sa proportion
    prob[,k] <- param$prop[k] * mvdnorm(Xtst, param$mean[k,], param$MCov[,,k])
  }
  #Calcul des probabilités à posteriori de chaque classe
  prob <- prob / apply(prob, 1, sum)
  pred <- max.col(prob)
  out$prob <- prob
  out$pred <- pred
  
  out
}

prob.ad <- function(param, X, z, niveaux){
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
  
  # calcul des valeurs de la fonction 
  valf <- ad.val(param, grille)$prob[,1]
  plot(X, col=c("red","green","blue","magenta","orange")[z])
  contour(grilleX, grilleY, matrix(valf,nrow=naffX,byrow=T), add=T, drawlabels=FALSE, levels=niveaux)
}