library(readr)
syn <- read.csv("Synth1-40.csv", header=T)
Xapp <- syn[,1:2]
zapp <- syn[,3]

source("functions-1-1.R")
mu <- ceuc.app(Xapp, zapp)
front.ceuc(Xapp, zapp, mu, 1000)

front.kppv(Xapp, zapp, 3, 1000)