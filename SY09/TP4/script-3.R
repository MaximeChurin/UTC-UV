source("C:/Users/maxime/Desktop/SY09/TP4/functions-2.R")

spam <- read.csv("C:/Users/maxime/Desktop/SY09/TP4/spam.csv", header=T)
X <- spam[,2:58]
z <- spam[,59]

#ARBRE
mean(evaluationArbre(X, z, 20))

#Forest
library(party)
library(randomForest)
set.seed(1)
output.forest <- randomForest(as.factor(z) ~ ., data = X)
output.forest
#selection des variables
randomForest::varImpPlot(output.forest)

#Transormation de X
X2 <-cbind(X[,21], X[,23:27])
X2 <-cbind(X2, X[,55:57])
X2 <-cbind(X2, X[,52:53])
X2 <-cbind(X2, X[,19])
X2 <-cbind(X2, X[,16])
X2 <-cbind(X2, X[,7])
X2 <-cbind(X2, X[,5])
X2 <-cbind(X2, X[,46])

#LOG
mean(evaluationLog(X2, z, 20))


