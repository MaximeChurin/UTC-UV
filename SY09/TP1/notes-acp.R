setwd("C:/Users/maxime/Desktop/SY09/TP1")
notes <- read.csv("sy02-p2016.csv", na.strings="", header=T)
notes$nom <- factor(notes$nom, levels=notes$nom)
notes$niveau <- factor(notes$niveau, ordered=T)
notes$resultat <- factor(notes$resultat, levels=c("F","Fx","E","D","C","B","A"), ordered=T)

---1.1---

---formation origine étudiants----
boxplot(notes$note.totale~notes$statut, varwidth=TRUE, col=c("gold","darkgreen"), ylab="Note finale de l'UV SY02")
r <- aov(notes$note.totale~notes$statut)
anova(r)

---specialite étudiants----
b<-subset(notes, !(specialite %in% c("HuTech")))
boxplot(b$note.totale~factor(b$specialite,exclude=NULL), varwidth=TRUE, col=c("gold","darkgreen"), ylab="Note finale de l'UV SY02")

---niveau étudiants----
boxplot(notes$note.totale~notes$niveau, varwidth=TRUE, col=c("gold","darkgreen"), xlab="Semestre", ylab="Note finale de l'UV SY02")
table(notes$note.totale,notes$niveau)
r <- aov(notes$note.totale~notes$niveau)
anova(r)

---correcteurs median----
boxplot(notes$note.median~notes$correcteur.median, varwidth=TRUE, col=c("gold","darkgreen"), ylab="Note m�dian de l'UV SY02")

---exemple---
par(cex.lab=1.5)
par(cex.axis=0.5)
b<-subset(notes, !(dernier.diplome.obtenu %in% c("AUTRE 2E CYCLE", "INGENIEUR")))
boxplot(b$note.totale~factor(b$dernier.diplome.obtenu,exclude=NULL), xlab="Dernier diplome obtenu", ylab="Note finale de l'UV SY02")
plot(notes$resultat, notes$niveau)
pairs(notes$resultat~notes$niveau)
table(notes$resultat, notes$niveau)

counts <- table(notes$resultat, notes$statut)
barplot(counts, legend=rownames(counts), beside = TRUE, horiz = TRUE)

---2.1---
moy.median <- aggregate(note.median~correcteur.median, data=notes, FUN=mean)
names(moy.median) <- c("correcteur","moy.median")
std.median <- aggregate(note.median~correcteur.median, data=notes, FUN=sd)
names(std.median) <- c("correcteur","std.median")
median <- merge(moy.median, std.median)
moy.final <- aggregate(note.final~correcteur.final, data=notes, FUN=mean)
names(moy.final) <- c("correcteur","moy.final")
std.final <- aggregate(note.final~correcteur.final, data=notes, FUN=sd)
names(std.final) <- c("correcteur","std.final")
final <- merge(moy.final, std.final)
correcteurs <- merge(median, final, all=T)
correcteurs
cor <- correcteurs[-c(2,8),]
cor
X<-cor[,2:5]
X <-scale(X, center = T, scale = F)
V<-(1/6) * t(X) %*% X
V
x=xtable(V,align=rep("",ncol(V)+1), digits=3)
print(x, floating=FALSE, tabular.environment="pmatrix", hline.after=NULL, include.rownames=FALSE, include.colnames=FALSE)
eigen(V)
c <- X %*% eigen(V)$vectors
rownames(c, do.NULL = TRUE, prefix = "row")
rownames(c) <- c("1","4","5","6","7", "8")
git2r::plot(c[,1],c[,2],xlab="Axe 1 (66%)", ylab="Axe 2 (25%)",type="n", asp=1)
abline(h=0,v=0)
text(c[,1],c[,2],cex=0.9,rownames(c), col = c("lightseagreen"))
D<-diag(diag(matrix(1/6, nrow=6, ncol=6)))
(1/sqrt(V[1][1]))*(1/sqrt(eigen(V)$values[3]))*t(matrix(X[,1]))%*%D%*%matrix(c[,3])
L <- diag(eigen(V)$values)
Cor
rownames(Cor, do.NULL = TRUE, prefix = "row")
rownames(Cor) <- c("moy.median","std.median","moy.final","std.final")
colnames(Cor, do.NULL = TRUE, prefix = "col")
colnames(Cor) <- c("moy.median","std.median","moy.final","std.final")
par(pty="s")
graphics::plot(Cor[,1],Cor[,2],xlab="Axe 1 (66%)", ylab="Axe 2 (25%)",pch=19, col="black", xlim=c(-1.1,+1.1),ylim=c(-1.1,+1.1))
abline(h=0,v=0)
text(Cor[,1],Cor[,2],labels=row.names(Cor),cex=1.3,col = c("lightseagreen"), pos=4)
symbols(0,0,circles=1,inches=F,add=T)

k1<-t(t(c[,1]))%*%(u[,1])
k2<-t(t(c[,1]))%*%(u[,1])+t(t(c[,2]))%*%(u[,2])
k3<-t(t(c[,1]))%*%(u[,1])+t(t(c[,2]))%*%(u[,2])+t(t(c[,3]))%*%(u[,3])
k4<-t(t(c[,1]))%*%(u[,1])+t(t(c[,2]))%*%(u[,2])+t(t(c[,3]))%*%(u[,3])+t(t(c[,4]))%*%(u[,4])
Cor2<-c(1.296242,   -0.343885,  0 ,         0)
Cor3<-c(   0  ,         0  ,       0.419661,  -0.867321)
-----1er plan------
Cor2(Cor2%*%u[,1], Cor2%*%u[,2])
Cor2(-0.1488966,-0.6904904)
Cor3(Cor3%*%u[,1], Cor3%*%u[,2])
Cor3(-0.4003011, 0.1328996)
-----2er plan------
Cor2(Cor2%*%u[,1], Cor2%*%u[,3])
Cor2(-0.1488966,-0.2699082)
Cor3(Cor3%*%u[,1], Cor3%*%u[,3])
Cor3(-0.4003011, -0.8478917)

git2r::plot(c[,1],c[,2],xlab="Axe 1 (66%)", ylab="Axe 2 (25%)",type="n", asp=1)
abline(h=0,v=0)
text(c[,1],c[,2],cex=0.9,rownames(c), col = c("lightseagreen"))
points.default(-0.1488966,-0.6904904, type="p", pch="2", col="lightcoral")
points.default(-0.4003011, 0.1328996, type="p", pch="3", col="lightcoral")

git2r::plot(c[,1],c[,2],xlab="Axe 1 (66%)", ylab="Axe 3 (5.8%)",type="n", asp=1)
abline(h=0,v=0)
text(c[,1],c[,2],cex=0.9,rownames(c), col = c("lightseagreen"))
points.default(-0.1488966,-0.2699082, type="p", pch="2", col="lightcoral")
points.default(-0.4003011, -0.8478917, type="p", pch="3", col="lightcoral")