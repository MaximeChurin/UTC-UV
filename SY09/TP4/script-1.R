library(readr)
library(MASS)
syn <- read.csv("Synth1-40.csv", header=T)
Xapp <- syn[,1:2]
zapp <- syn[,3]
levels <- c(0.2, 0.4, 0.6, 0.8)

source("discriminante.R")
estim.adq <- adq.app(Xapp, zapp)
estim.adl <- adl.app(Xapp, zapp)
estim.nba <- nba.app(Xapp, zapp)

prob.ad(estim.adq, Xapp, zapp, levels)
prob.ad(estim.nba, Xapp, zapp, levels)
prob.ad(estim.adl, Xapp, zapp, levels)

source("regression-logistique.R")
param <- log.app(Xapp, zapp, T, 1*10^(-5))
prob.log(param$beta, Xapp, zapp, levels)
Xapp2 <- transfrom.quadratique(Xapp)
param2 <- log.app(Xapp2, zapp, T, 1*10^(-5))
prob.log2(param2$beta, Xapp, zapp, levels)
