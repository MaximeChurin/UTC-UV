Voir rapport TP1 pour crabs
supprimer 102 143

#acp et aftd

data(iris)
iris
data_iris<-iris[,1:4]
data_iris2<-data_iris[-102,]
dist_iris<-dist(data_iris2)
C<-cmdscale(dist_iris, k=4, eig=T)
graphics::plot(C$points[,1],C$points[,2],xlab="Axe 1 (92.5%)", ylab="Axe 2 (5.3%)",pch=20, col="black")
abline(h=0,v=0)

C$eig[1:76]
C$eig[1]/sum(C$eig[1:76])*100
C$eig[2]/sum(C$eig[1:76])*100

rownames(C, do.NULL = TRUE, prefix = "row")
names <- iris[c(5)]
names <- names[-102,]
rownames(C) <- names
graphics::plot(C$points[,1],C$points[,2],xlab="Axe 1 (92.5%)", ylab="Axe 2 (5.3%)", type="n")
points(C$points[,1],C$points[,2], pch=20, col = c("lightseagreen", "#E36EF6", "#E47E00")[iris$Species])
legend("bottomright", legend=c("setosa", "versicolor", "virginica"), fill = c("lightseagreen", "#E36EF6", "#E47E00"), bty = "L")
abline(h=0,v=0)


data_iris2.acp <- princomp(data_iris2)
data_iris2.acp$scores
library(ggbiplot)
ggbiplot(data_iris2.acp, obs.scale = 1)
ggbiplot(data_iris2.acp, obs.scale = 1, var.scale = 1,
         groups = iris$Species[-102], ellipse = TRUE) +
  scale_color_discrete(name = '',h =c(200,400)) +
  theme(legend.direction = 'horizontal', legend.position = 'top')

#nombre de repartition : cb de groupe a construire avec ou sans couleurs question de prevision, si on applique un clustering ascendant ou kmeans
#dans l'objectif des questions suivantes qui tenteras via des méthodes de trouver le nombre de groupe
#que nous comparerons a la repartition ideal

#aftd

library(readr)
crabs2 <- read_csv("C:/Users/maxime/Desktop/SY09/TP2/crabs2.csv")
data_crabs2<-crabs2[,1:4]
dist_crabs2<-dist(data_crabs2)
D<-cmdscale(dist_crabs2, k=4, eig=T)
graphics::plot(D$points[,1],D$points[,2],xlab="Axe 1 (55%)", ylab="Axe 2 (37.2%)",pch=20, col="black")
abline(h=0,v=0)

rownames(D, do.NULL = TRUE, prefix = "row")
names <- crabs2[c(5)]
rownames(D) <- names
crabs2$Species <- paste0(crabs2$sp,crabs2$sex)
crabs2$Species <- factor(crabs2$Species)
graphics::plot(D$points[,1],D$points[,2],xlab="Axe 1 (55%)", ylab="Axe 2 (37.2%)", type="n")
points(D$points[,1],D$points[,2],pch=20, col = c("lightseagreen", "lightcoral", "#E47E00", "#E36EF6")[crabs2$Species])
legend("topright", legend=c("FO", "MO", "FB", "MB"), fill = c("lightseagreen", "lightcoral", "#E47E00", "#E36EF6"), bty = "n")
abline(h=0,v=0)
D$eig[1:106]
D$eig[1]/sum(D$eig[1:106])*100
D$eig[2]/sum(D$eig[1:106])*100

#aftd

library(readr)
mut <- read.csv("C:/Users/maxime/Desktop/SY09/TP2/mutations2.csv", header=T, row.names=1)
mut <- as.dist(mut, diag=T, upper=T)
E<-cmdscale(mut, k=2, eig=T)
E
library(ggplot2)
library(ggrepel)
df <- data.frame(x = E$points[,1], y = E$points[,2], z = rownames(E$points))
ggplot(data = df, aes(x = x, y = y)) +
  theme_bw() +
  xlab("Axe 1 (53.4%)") +
  ylab("Axe 2 (16.2%)") +
  geom_text_repel(aes(label = z), box.padding = unit(0.6, "lines")) +
  geom_point(colour = "lightcoral",   size = 2)

E<-cmdscale(mut, k=5, eig=T)
E
library(ggplot2)
library(ggrepel)
df <- data.frame(x = E$points[,1], y = E$points[,2], z = rownames(E$points))
ggplot(data = df, aes(x = x, y = y)) +
  theme_bw() +
  xlab("Axe 1 (53.4%)") +
  ylab("Axe 2 (16.2%)") +
  geom_text_repel(aes(label = z), box.padding = unit(0.6, "lines")) +
  geom_point(colour = "lightcoral",   size = 2)

rownames(E, do.NULL = TRUE, prefix = "row")
graphics::plot(E$points[,1],E$points[,2],xlab="Axe 1 (53.4%)", ylab="Axe 2 (16.2%)", pch=20)
abline(h=0,v=0)
text(E$points[,1],E$points[,2],cex=0.5,rownames(E$points))
E$eig[1:14]
sum(E$eig[1:14])
E$eig[1]/sum(E$eig[1:14])*100
E$eig[2]/sum(E$eig[1:14])*100
#qualite % du % explique en garde seulement les valeurs propres positves et on calcule leur inertie
#ici bonne representation

library(MASS)
G<-cmdscale(mut, k=2)
plot(Shepard(mut, cmdscale(mut, k=2)), xlab="Distance observée", ylab="Distance reconstruite", pch = 20)
abline(0, 1)
plot(Shepard(mut, cmdscale(mut, k=5)), xlab="Distance observée", ylab="Distance reconstruite", pch = 20)
abline(0, 1)
plot(Shepard(mut, cmdscale(mut, k=14)), xlab="Distance observée", ylab="Distance reconstruite", pch = 20)
abline(0, 1)
reg.simple<-lm(Shepard(mut, cmdscale(mut, k=2))$x~Shepard(mut, cmdscale(mut, k=2))$yf) 
summary(reg.simple) 
reg.simple<-lm(Shepard(mut, cmdscale(mut, k=5))$x~Shepard(mut, cmdscale(mut, k=5))$yf) 
summary(reg.simple)
#diagramme de shepard proche de la droite bon, loin de la droite mauvais
#tracer la droite plutot que par des points
#recommencer avec k=3,4 et 5 pour les shepard

#II clustering hierarchique (cout des verticals) plus mieux que l'ascendant
#methode du coude : nombre de groupe, valeurs propres => plus on rajoute plus on ameliore
#changement significatif de pente on choisi : adapte pour un modele dependant un seul parametre

library(readr)
library(ggplot2)
library(cluster)
crabs2 <- read_csv("C:/Users/maxime/Desktop/SY09/TP2/crabs2.csv")
data_crabs2<-crabs2[,1:4]
crabs2.2means <- kmeans(data_crabs2, 2)
clusplot(data_crabs2, crabs2.2means$cluster, color=TRUE, shade=TRUE, labels=0, lines=0)

crabs2.4means <- kmeans(data_crabs2, 4)
clusplot(data_crabs2, crabs2.4means$cluster, color=TRUE, shade=TRUE, labels=0, lines=0)


library(readr)
mut <- read.csv("C:/Users/maxime/Desktop/SY09/TP2/mutations2.csv", header=T, row.names=1)
mut <- as.dist(mut, diag=T, upper=T)
E<-cmdscale(mut, k=5, eig=T)
mut.3means <- kmeans(E$points, 3)
plot(E$points, col=mut.3means$cluster, xlab="Axe 1 (53.4%)", ylab="Axe 2 (16.2%)", pch=19)
#clusplot(E$points, mut.3means$cluster, color=TRUE, shade=TRUE, labels=0, lines=0)
mut.3means$tot.withinss