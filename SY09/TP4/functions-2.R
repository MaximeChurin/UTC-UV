source("discriminante.R")
source("regression-logistique.R")
library(MASS)
library(tree)

#Fonction fournie
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

# Fonction évaluant les performances de l'analyse discriminante quadratique.
evaluationAdq <- function(Xapp, zapp, N) {
  # Initialisation du tableau d'erreurs à retourner.
  erreurRes <- c(1:N)
  
  # On effectue N répétitions.
  for(i in 1:N) {
    # Séparation du jeu de données.
    separ <- separ1(Xapp, zapp)
    
    # Calcul des paramètres.
    paramAdq = adq.app(separ$Xapp, separ$zapp)
    
    # On prédit les étiquettes sur l'ensemble de test.
    adq = ad.val(paramAdq, separ$Xtst)
    erreur.tst <- 0
    
    # Calcul du nombre total d'erreur sur l'ensemble de test.
    for(j in 1:length(separ$ztst)) {
      if(adq$pred[j] != separ$ztst[j]) {
        erreur.tst <- erreur.tst + 1
      }
    }
    
    # Calcul du taux d'erreur moyen sur l'ensemble de test. 
    erreurRes[i] <- erreur.tst / length(separ$ztst)
  }
  
  erreurRes
}

# Fonction évaluant les performances de l'analyse discriminante linéaire.
evaluationAdl <- function(Xapp, zapp, N) {
  # Initialisation du tableau d'erreurs à retourner.
  erreurRes <- c(1:N)
  
  # On effectue N répétitions.
  for(i in 1:N) {
    # Séparation du jeu de données.
    separ <- separ1(Xapp, zapp)
    
    # Calcul des paramètres.
    paramAdl = adl.app(separ$Xapp, separ$zapp)
    
    # On prédit les étiquettes sur l'ensemble de test.
    adl = ad.val(paramAdl, separ$Xtst)
    erreur.tst <- 0
    
    # Calcul du nombre total d'erreur sur l'ensemble de test.
    for(j in 1:length(separ$ztst)) {
      if(adl$pred[j] != separ$ztst[j]) {
        erreur.tst <- erreur.tst + 1
      }
    }
    
    # Calcul du taux d'erreur moyen sur l'ensemble de test 
    erreurRes[i] <- erreur.tst / length(separ$ztst)
  }
  
  erreurRes
}

# Fonction évaluant les performances d'un classifieur bayésien naif.
evaluationNba <- function(Xapp, zapp, N) {
  # Initialisation du tableau d'erreurs à retourner.
  erreurRes <- c(1:N)
  
  # On effectue N répétitions.
  for(i in 1:N) {
    # Séparation du jeu de données.
    separ <- separ1(Xapp, zapp)
    
    # Calcul des paramètres.
    paramNba = nba.app(separ$Xapp, separ$zapp)
    
    # On prédit les étiquettes sur l'ensemble de test.
    nba = ad.val(paramNba, separ$Xtst)
    erreur.tst <- 0
    
    # Calcul du nombre total d'erreur sur l'ensemble de test.
    for(j in 1:length(separ$ztst)) {
      if(nba$pred[j] != separ$ztst[j]) {
        erreur.tst <- erreur.tst + 1
      }
    }
    
    # Calcul du taux d'erreur moyen sur l'ensemble d'apprentissage. 
    erreurRes[i] <- erreur.tst / length(separ$ztst)
  }
  
  erreurRes
}

# Fonction évaluant les performances d'un classifieur en utilisant la régression logistique linéaire.
evaluationLog <- function(Xapp, zapp, N) {
  # Initialisation du tableau d'erreurs à retourner.
  erreurRes <- c(1:N)
  
  # On effectue N répétitions.
  for(i in 1:N) {
    # Séparation du jeu de données.
    separ <- separ1(Xapp, zapp)
    
    # Calcul des paramètres.
    paramLog <- log.app(separ$Xapp, separ$zapp, T, 1*10^(-5))
    
    # On prédit les étiquettes sur l'ensemble de test
    estim.log = log.val(paramLog$beta, separ$Xtst)
    erreur.tst <- 0

    # Calcul du nombre total d'erreur sur l'ensemble de test
    for(j in 1:length(separ$ztst)) {
      if(estim.log$pred[j] != separ$ztst[j]) {
        erreur.tst <- erreur.tst + 1
      }
    }
    
    # Calcul du taux d'erreur moyen sur l'ensemble de test
    erreurRes[i] <- erreur.tst / length(separ$ztst)
  }
  
  erreurRes
}

# Fonction évaluant les performances d'un classifieur en utilisant la régression logistique quadratique.
evaluationLog2 <- function(Xapp, zapp, N) {
  # Initialisation du tableau d'erreurs à retourner.
  erreurRes <- c(1:N)
  
  # On effectue N répétitions.
  for(i in 1:N) {
    # Séparation du jeu de données.
    separ <- separ1(Xapp, zapp)
    
    # Calcul des paramètres.
    paramLog <- log.app(transfrom.quadratique(separ$Xapp), separ$zapp, T, 1*10^(-5))

    # On prédit les étiquettes sur l'ensemble de test.
    log = log.val(paramLog$beta, transfrom.quadratique(separ$Xtst))
    erreur.tst <- 0
    
    # Calcul du nombre total d'erreur sur l'ensemble de test.
    for(j in 1:length(separ$ztst)) {
      if(log$pred[j] != separ$ztst[j]) {
        erreur.tst <- erreur.tst + 1
      }
    }
    
    # Calcul du taux d'erreur moyen sur l'ensemble de test. 
    erreurRes[i] <- erreur.tst / length(separ$ztst)
  }
  
  erreurRes
}


# Fonction évaluant les performances de la méthode des arbres binaires.
evaluationArbre <- function(Xapp, zapp, N) {
  # Initialisation du tableau d'erreurs à retourner.
  erreurRes <- c(1:N)
  
  # On effectue N répétitions.
  for(i in 1:N) {
    # Séparation du jeu de données.
    separ <- separ1(Xapp, zapp)
    zapp.factor <- as.factor(separ$zapp)
    tree.formula <- zapp.factor ~ .
    tree.app <- tree(formula = tree.formula, data = separ$Xapp, control=tree.control(nobs=dim(separ$Xapp)[1], mindev = 0.0001), model = T)

    prune <- prune.misclass(tree.app, k=1)
    prob <- predict(prune, separ$Xtst)
    pred <- max.col(prob)

    erreur.tst <- 0
    
    # Calcul du nombre total d'erreur sur l'ensemble de test.
    for(j in 1:length(separ$ztst)) {
      if(pred[j] != separ$ztst[j]) {
        erreur.tst <- erreur.tst + 1
      }
    }
    
    # Calcul du taux d'erreur moyen sur l'ensemble de test. 
    erreurRes[i] <- erreur.tst / length(separ$ztst)
  }
  
  erreurRes
}
