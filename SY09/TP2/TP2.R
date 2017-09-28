library(ggplot2)
library(MASS)
data(iris)
iris.acp <- princomp(iris[,1:4])
summary(iris.acp)
plot(iris.acp)
data_iris <- iris[,1:4]
iris.dist <- dist(data_iris)
isoMDS(iris.dist)

data_iris2 <- data_iris[-102,]
iris.dist2 <- dist(data_iris2)
isoMDS(iris.dist2)
iso <- isoMDS(iris.dist2)
plot(iso$points)
ggplot(cmdscale(iris.dist))

iris.acp$scores

sh <- Shepard(iris.dist2, iso$points)
plot(sh, pch = ".")
