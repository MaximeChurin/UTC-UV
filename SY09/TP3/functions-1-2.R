source("functions-1-1.R")
source("separ1.R")
source("separ2.R")

# Fonction estimant les paramètres d'une loi normale multivariée.
estimation <- function(x, z) {
  # Calcul de la longueur du jeu de données.
  n <- length(z)
  
  # Calcul du taux de répartition entre les différentes classes.
  pi <- (tabulate(z))
  for(i in 1:length(pi)) {
    pi[i] <- pi[i] / n
  }

  # Inititalisation de la matrice associée au paramètre mu.
  mu <- matrix(,length(pi),dim(x)[2])
  
  # Inititalisation de la liste associée au paramètre sigma.
  sigma <- list()
  
  # length(pi) nous indique les nombre de classes.
  # On boucle donc sur le nombre de classes présentes dans le jeu de données.
  for(zi in 1:length(pi)) {
    # Créaton du tableau xi qui contient toutes les données pour la classe courante.
    xi <- x[zi == z,]
    
    # Calcul du paramètre mu pour la classe courante.
    mu[zi,] <- apply(xi, 2, mean)
    
    # Calcul du paramètre sigma pour la classe courante.
    sigma[[length(sigma) + 1]] <- cov(xi)
  }
  
  
  # On retourne les 3 paramètres estimés : pi; mu est sigma.
  res <- NULL
  res$pi <- pi
  res$mu <- mu
  res$sigma <- sigma

  res
}

# Fonction évaluant les performances d'un classifieur euclidien
# sur 20 répétitions en utilisant les fonctions ceuc.app et ceuc.val.
evaluationCeuc <- function(x, z) {
  # Initialisation du tableau d'erreurs à retourner.
  erreurRes <- matrix(,20,2)
  colnames(erreurRes) <- c("app", "tst")

  # On effectue 20 répétitions.
  for(i in 1:20) {
    # Séparation du jeu de données.
    separ <- separ1(x, z)
    
    # Calcul des paramètres estimés du classifieur euclidien.
    mu = ceuc.app(separ$Xapp, separ$zapp)

    # On prédit les étiquettes sur l'ensemble d'apprentissage.
    zpred = ceuc.val(mu, separ$Xapp)
    erreur.app <- 0
    
    # Calcul du nombre total d'erreur sur l'ensemble d'apprentissage.
    for(j in 1:length(separ$zapp)) {
      if(zpred[j] != separ$zapp[j]) {
        erreur.app <- erreur.app + 1
      }
    }

    # Calcul du taux d'erreur moyen sur l'ensemble d'apprentissage. 
    erreurRes[i,1] <- erreur.app / length(separ$zapp)

    # On prédit les étiquettes sur l'ensemble de test.
    zpred = ceuc.val(mu, separ$Xtst)
    erreur.tst <- 0
    
    # Calcul du nombre total d'erreur sur l'ensemble de test
    for(j in 1:length(separ$ztst)) {
      if(zpred[j] != separ$ztst[j]) {
        erreur.tst <- erreur.tst + 1
      }
    }

    # Calcul du taux d'erreur moyen sur l'ensemble de test.
    erreurRes[i,2] <- erreur.tst[1] / length(separ$ztst)
  }

  erreurRes
}

# Fonction évaluant les performances de la méthode des K plus proches voisins
# sur 20 répétitions en utilisant les fonctions kppv.tune et kppv.val.
evaluationKppv <- function(x, z) {
  # Initialisation du tableau d'erreurs à retourner.
  erreurRes <- matrix(,20,2)
  colnames(erreurRes) <- c("app", "tst")
  
  # On effectue 20 répétitions.
  for(i in 1:20) {
    # Séparation du jeu de données.
    separ <- separ2(x, z)
    
    # Calcul du nombre de voisins optimal (jusqu'à 50 maximum).
    K = kppv.tune(separ$Xapp, separ$zapp, separ$Xval, separ$zval, c(1:50))

    # On prédit les étiquettes sur l'ensemble d'apprentissage.
    zpred = kppv.val(separ$Xapp, separ$zapp, K, separ$Xapp)
    erreur.app <- 0
    
    # Calcul du nombre total d'erreur sur l'ensemble d'apprentissage.
    for(j in 1:length(separ$zapp)) {
      if(zpred[j] != separ$zapp[j]) {
        erreur.app <- erreur.app + 1
      }
    }
    
    # Calcul du taux d'erreur moyen sur l'ensemble d'apprentissage. 
    erreurRes[i,1] <- erreur.app / length(separ$zapp)
    
    # On prédit les étiquettes sur l'ensemble de test.
    zpred = kppv.val(separ$Xapp, separ$zapp, K, separ$Xtst)
    erreur.tst <- 0
    
    # Calcul du nombre total d'erreur sur l'ensemble de test.
    for(j in 1:length(separ$ztst)) {
      if(zpred[j] != separ$ztst[j]) {
        erreur.tst <- erreur.tst + 1
      }
    }
    
    # Calcul du taux d'erreur moyen sur l'ensemble de test. 
    erreurRes[i,2] <- erreur.tst/ length(separ$ztst)
  }
  
  erreurRes
}

# Fonction estimant le taux d'erreur d'un classifieur en prenant en entrée
# les erreurs de plusieurs répétitions sous forme d'un tableau.
# La fonction calcule une estimation du taux d'erreur
# ainsi qu'un intervalle de confiance à 95%.
estimationTauxErreur <- function(erreur) {
  res <- NULL
  
  # Calcul de la moyenne.
  res$epsilon <- mean(erreur)
  
  # Calcul de l'écart-type.
  sd <- sd(erreur)

  # Calcul de la distance de moyenne aux bornes de l'intervalle de confiance à 95%.
  distance <- 1.96 * sd / sqrt(length(erreur))
  
  # Calcul de l'intervalle de confiance.
  res$borneGauche <- res$epsilon - distance
  res$borneDroite <- res$epsilon + distance
  
  res
}

#Fonctions fournies
separ1 <- function(X, z)
{
  g <- max(z)

  Xapp <- NULL
  zapp <- NULL
  Xtst <- NULL
  ztst <- NULL

  for (k in 1:g)
  {
      indk <- which(z==k)
      ntot <- length(indk)
      napp <- round(ntot*2/3)
      ntst <- ntot-napp

      itot <- sample(indk)
      iapp <- itot[1:napp]
      itst <- itot[(napp+1):ntot]

      Xapp <- rbind(Xapp, X[iapp,])
      zapp <- c(zapp, z[iapp])
      Xtst <- rbind(Xtst, X[itst,])
      ztst <- c(ztst, z[itst])
  }

  res <- NULL
  res$Xapp <- Xapp
  res$zapp <- zapp
  res$Xtst <- Xtst
  res$ztst <- ztst

  res
}

separ2 <- function(X, z)
{
  g <- max(z)

  Xapp <- NULL
  zapp <- NULL
  Xval <- NULL
  zval <- NULL
  Xtst <- NULL
  ztst <- NULL

  for (k in 1:g)
  {
      indk <- which(z==k)
      ntot <- length(indk)
      napp <- round(ntot/2)
    nval <- round(ntot/4)
      ntst <- ntot-napp-nval

      itot <- sample(indk)
      iapp <- itot[1:napp]
      ival <- itot[(napp+1):(napp+nval)]
      itst <- itot[(napp+nval+1):ntot]

      Xapp <- rbind(Xapp, X[iapp,])
      zapp <- c(zapp, z[iapp])
      Xval <- rbind(Xval, X[ival,])
      zval <- c(zval, z[ival])
      Xtst <- rbind(Xtst, X[itst,])
      ztst <- c(ztst, z[itst])
  }

  res <- NULL
  res$Xapp <- Xapp
  res$zapp <- zapp
  res$Xval <- Xval
  res$zval <- zval
  res$Xtst <- Xtst
  res$ztst <- ztst

  res
}
