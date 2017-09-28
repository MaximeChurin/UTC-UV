library(readr)
syn <- read.csv("C:/Users/maxime/Desktop/SY09/TP3/Synth1-40.csv", header=T)
Xapp <- syn[,1:2]
zapp <- syn[,3]

source("fonctions-1-1.R")
mu <- ceuc.app(Xapp, zapp)
front.ceuc(Xapp, zapp, mu, 1000)

front.kppv(Xapp, zapp, 3, 1000)

#Regles de Bayes
#3) Trace pour synth1-1000
syn_1000 <- read.csv("C:/Users/maxime/Desktop/SY09/TP3/Synth1-1000.csv", header=T)
variable <- syn_1000[,1:2]
etiquettes <- syn_1000[,3]
graphics::plot(variable[,1],variable[,2],xlab="x1", ylab="x2", type="n")
text(variable[,1],variable[,2],cex=0.5,rownames(variable))
abline(-3/2, -2, col=c("red"))

graphics::plot(variable[,1],variable[,2],xlab="x1", ylab="x2", type="n")
points(variable[,1],variable[,2], pch=20, col = c("lightseagreen", "#E36EF6")[etiquettes])
abline(-3/2, -2, col=c("red"), lwd=2)
legend("bottomright", legend=c("Classe 1", "Classe 2"), fill = c("lightseagreen", "#E36EF6"), bty = "n")

sd(variable[1:496,1])
sd(variable[1:496,2])
sd(variable[497:1000,1])
sd(variable[497:1000,2])
sum(variable[1:496,1])/496
sum(variable[1:496,2])/496
sum(variable[497:1000,1])/504
sum(variable[497:1000,2])/504

syn2_1000 <- read.csv("C:/Users/maxime/Desktop/SY09/TP3/Synth2-1000.csv", header=T)
variable2 <- syn2_1000[,1:2]
etiquettes2 <- syn2_1000[,3]
graphics::plot(variable2[,1],variable2[,2],xlab="x1", ylab="x2", type="n")
points(variable2[,1],variable2[,2], pch=20, col = c("lightseagreen", "#E36EF6")[etiquettes2])
abline(v=1.1155, col=c("red"), lwd=2)
legend("bottomleft", legend=c("Classe 1", "Classe 2"), fill = c("lightseagreen", "#E36EF6"), bty = "n")

syn2_1000 <- read.csv("C:/Users/maxime/Desktop/SY09/TP3/Synth2-1000.csv", header=T)
variable2 <- syn2_1000[,1:2]
etiquettes2 <- syn2_1000[,3]
graphics::plot(variable2[,1],variable2[,2],xlab="x1", ylab="x2", type="n")
points(variable2[,1],variable2[,2], pch=20, col = c("lightseagreen", "#E36EF6")[etiquettes2])
par(new=TRUE)
curve(0.8*x^2-6.8*x+6.59, xlab="", ylab="", xlim=range(variable2[,1]), ylim=range(variable2[,2]))
legend("bottomleft", legend=c("Classe 1", "Classe 2"), fill = c("lightseagreen", "#E36EF6"), bty = "n")

sd(variable2[1:523,1])
sd(variable2[1:523,2])
sd(variable2[524:1000,1])
sd(variable2[524:1000,2])
sum(variable2[1:523,1])/523
sum(variable2[1:523,2])/523
sum(variable2[524:1000,1])/477
sum(variable2[524:1000,2])/477
