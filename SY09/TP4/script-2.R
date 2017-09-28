source("functions-2.R")

#2.1

syn1.1000 <- read.csv("Synth1-1000.csv", header=T)
syn2.1000 <- read.csv("Synth2-1000.csv", header=T)
syn3.1000 <- read.csv("Synth3-1000.csv", header=T)

#Jeu de données Synth1-1000.

#ADQ
mean(evaluationAdq(syn1.1000[,1:2], syn1.1000[,3], 20))

estim.adq <- adq.app(syn1.1000[,1:2], syn1.1000[,3])
prob.ad(estim.adq, syn1.1000[,1:2], syn1.1000[,3], c(0.5))

#ADL
mean(evaluationAdl(syn1.1000[,1:2], syn1.1000[,3], 20))

estim.adl <- adl.app(syn1.1000[,1:2], syn1.1000[,3])
prob.ad(estim.adl, syn1.1000[,1:2], syn1.1000[,3], c(0.5))

#NBA
mean(evaluationNba(syn1.1000[,1:2], syn1.1000[,3], 20))

estim.nba <- nba.app(syn1.1000[,1:2], syn1.1000[,3])
prob.ad(estim.nba, syn1.1000[,1:2], syn1.1000[,3], c(0.5))

#LOG
mean(evaluationLog(syn1.1000[,1:2], syn1.1000[,3], 20))

estim.log <- log.app(syn1.1000[,1:2], syn1.1000[,3], T, 1*10^(-5))
prob.log(estim.log$beta, syn1.1000[,1:2], syn1.1000[,3], c(0.5))

#LOG QUARDRATIQUE
mean(evaluationLog2(syn1.1000[,1:2], syn1.1000[,3], 20))

estim.log2 <- log.app(transfrom.quadratique(syn1.1000[,1:2]), syn1.1000[,3], T, 1*10^(-5))
prob.log2(estim.log2$beta, syn1.1000[,1:2], syn1.1000[,3], c(0.5))

#ARBRE
mean(evaluationArbre(syn1.1000[,1:2], syn1.1000[,3], 20))

#Jeu de données Synth2-1000.

#ADQ
mean(evaluationAdq(syn2.1000[,1:2], syn2.1000[,3], 20))

estim.adq <- adq.app(syn2.1000[,1:2], syn2.1000[,3])
prob.ad(estim.adq, syn2.1000[,1:2], syn2.1000[,3], c(0.5))

#ADL
mean(evaluationAdl(syn2.1000[,1:2], syn2.1000[,3], 20))

estim.adl <- adl.app(syn2.1000[,1:2], syn2.1000[,3])
prob.ad(estim.adl, syn2.1000[,1:2], syn2.1000[,3], c(0.5))

#NBA
mean(evaluationNba(syn2.1000[,1:2], syn2.1000[,3], 20))

estim.nba <- nba.app(syn2.1000[,1:2], syn2.1000[,3])
prob.ad(estim.nba, syn2.1000[,1:2], syn2.1000[,3], c(0.5))

#LOG
mean(evaluationLog(syn2.1000[,1:2], syn2.1000[,3], 20))

estim.log <- log.app(syn2.1000[,1:2], syn2.1000[,3], T, 1*10^(-5))
prob.log(estim.log$beta, syn2.1000[,1:2], syn2.1000[,3], c(0.5))

#LOG QUARDRATIQUE
mean(evaluationLog2(syn2.1000[,1:2], syn2.1000[,3], 20))

estim.log2 <- log.app(transfrom.quadratique(syn2.1000[,1:2]), syn2.1000[,3], T, 1*10^(-5))
prob.log2(estim.log2$beta, syn2.1000[,1:2], syn2.1000[,3], c(0.5))

#ARBRE
mean(evaluationArbre(syn2.1000[,1:2], syn2.1000[,3], 20))

#Jeu de données Synth3-1000.

#ADQ
mean(evaluationAdq(syn3.1000[,1:2], syn3.1000[,3], 20))

estim.adq <- adq.app(syn3.1000[,1:2], syn3.1000[,3])
prob.ad(estim.adq, syn3.1000[,1:2], syn3.1000[,3], c(0.5))

#ADL
mean(evaluationAdl(syn3.1000[,1:2], syn3.1000[,3], 20))

estim.adl <- adl.app(syn3.1000[,1:2], syn3.1000[,3])
prob.ad(estim.adl, syn3.1000[,1:2], syn3.1000[,3], c(0.5))

#NBA
mean(evaluationNba(syn3.1000[,1:2], syn3.1000[,3], 20))

estim.nba <- nba.app(syn3.1000[,1:2], syn3.1000[,3])
prob.ad(estim.nba, syn3.1000[,1:2], syn3.1000[,3], c(0.5))

#LOG
mean(evaluationLog(syn3.1000[,1:2], syn3.1000[,3], 20))

estim.log <- log.app(syn3.1000[,1:2], syn3.1000[,3], T, 1*10^(-5))
prob.log(estim.log$beta, syn3.1000[,1:2], syn3.1000[,3], c(0.5))

#LOG QUARDRATIQUE
mean(evaluationLog2(syn3.1000[,1:2], syn3.1000[,3], 20))

estim.log2 <- log.app(transfrom.quadratique(syn3.1000[,1:2]), syn3.1000[,3], T, 1*10^(-5))
prob.log2(estim.log2$beta, syn3.1000[,1:2], syn3.1000[,3], c(0.5))

#ARBRE
mean(evaluationArbre(syn3.1000[,1:2], syn3.1000[,3], 20))

#2.2

#2.2.1
#Pima

Donn <- read.csv("Pima.csv", header=T)
X <- Donn[,1:7]
z <- Donn[,8]

#ADQ
mean(evaluationAdq(X, z, 100))

#ADL
mean(evaluationAdl(X, z, 100))

#NBA
mean(evaluationNba(X, z, 100))

#LOG
mean(evaluationLog(X, z, 100))

#LOG QUARDRATIQUE
mean(evaluationLog2(X, z, 100))

#2.2.2
#breast cancer Wisconsin

Donn <- read.csv("bcw.csv", header=T)
X <- Donn[,1:9]
z <- Donn[,10]

#ADQ
mean(evaluationAdq(X, z, 100))

#ADL
mean(evaluationAdl(X, z, 100))

#NBA
mean(evaluationNba(X, z, 100))

#LOG
mean(evaluationLog(X, z, 100))

#ARBRE
mean(evaluationArbre(X, z, 100))

