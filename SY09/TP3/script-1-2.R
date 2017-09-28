source("functions-1-2.R")

#1.2.1
#jeux de données Synth1-40, Synth1-100, Synth1-500, Synth1-1000

syn1.40 <- read.csv("Synth1-40.csv")
syn1.100 <- read.csv("Synth1-100.csv")
syn1.500 <- read.csv("Synth1-500.csv")
syn1.1000 <- read.csv("Synth1-1000.csv")

#1.2.1.1
#estimation des paramètres

estimation(syn1.40[,1:2], syn1.40[,3])

estimation(syn1.100[,1:2], syn1.100[,3])

estimation(syn1.500[,1:2], syn1.500[,3])

estimation(syn1.1000[,1:2], syn1.1000[,3])

#1.2.1.2
#estimation du taux d'erreur pour le classifieur euclidien

erreur.syn1.40 <- evaluationCeuc(syn1.40[,1:2], syn1.40[,3])
estimationTauxErreur(erreur.syn1.40[,"app"])
estimationTauxErreur(erreur.syn1.40[,"tst"])

erreur.syn1.100 <- evaluationCeuc(syn1.100[,1:2], syn1.100[,3])
estimationTauxErreur(erreur.syn1.100[,"app"])
estimationTauxErreur(erreur.syn1.100[,"tst"])

erreur.syn1.500 <- evaluationCeuc(syn1.500[,1:2], syn1.500[,3])
estimationTauxErreur(erreur.syn1.500[,"app"])
estimationTauxErreur(erreur.syn1.500[,"tst"])

erreur.syn1.1000 <- evaluationCeuc(syn1.1000[,1:2], syn1.1000[,3])
estimationTauxErreur(erreur.syn1.1000[,"app"])
estimationTauxErreur(erreur.syn1.1000[,"tst"])

#1.2.1.3
#test de la fonction kppv.tune en utilisant l'ensemble d'apprentissage comme ensemble de validation

separ.syn1.40 <- separ1(syn1.40[,1:2], syn1.40[,3])
kppv.tune(separ.syn1.40$Xapp, separ.syn1.40$zapp, separ.syn1.40$Xapp, separ.syn1.40$zapp, c(1:40))

#1.2.1.4
#estimation du taux d'erreur pour la méthode des K plus proches voisins

erreur.syn1.40 <- evaluationKppv(syn1.40[,1:2], syn1.40[,3])
estimationTauxErreur(erreur.syn1.40[,"app"])
estimationTauxErreur(erreur.syn1.40[,"tst"])

erreur.syn1.100 <- evaluationKppv(syn1.100[,1:2], syn1.100[,3])
estimationTauxErreur(erreur.syn1.100[,"app"])
estimationTauxErreur(erreur.syn1.100[,"tst"])

erreur.syn1.500 <- evaluationKppv(syn1.500[,1:2], syn1.500[,3])
estimationTauxErreur(erreur.syn1.500[,"app"])
estimationTauxErreur(erreur.syn1.500[,"tst"])

erreur.syn1.1000 <- evaluationKppv(syn1.1000[,1:2], syn1.1000[,3])
estimationTauxErreur(erreur.syn1.1000[,"app"])
estimationTauxErreur(erreur.syn1.1000[,"tst"])

#1.2.2
#jeux de données Synth2-1000

syn2.1000 <- read.csv("Synth2-1000.csv")

#estimation des paramètres

estimation(syn2.1000[,1:2], syn2.1000[,3])

#estimation du taux d'erreur pour le classifieur euclidien

erreur.syn2.1000 <- evaluationCeuc(syn2.1000[,1:2], syn2.1000[,3])
estimationTauxErreur(erreur.syn2.1000[,"app"])
estimationTauxErreur(erreur.syn2.1000[,"tst"])

#estimation du taux d'erreur pour la méthode des K plus proches voisins

erreur.syn2.1000 <- evaluationKppv(syn2.1000[,1:2], syn2.1000[,3])
estimationTauxErreur(erreur.syn2.1000[,"app"])
estimationTauxErreur(erreur.syn2.1000[,"tst"])

#1.2.3
#jeux de données réelles

breastcancer <- read.csv("Breastcancer.csv")
pima <- read.csv("Pima.csv")

#estimation du taux d'erreur pour le classifieur euclidien

erreur.pima <- evaluationCeuc(pima[,1:7], pima[,8])
estimationTauxErreur(erreur.pima[,"app"])
estimationTauxErreur(erreur.pima[,"tst"])

erreur.breastcancer <- evaluationCeuc(breastcancer[,1:9], breastcancer[,10])
estimationTauxErreur(erreur.breastcancer[,"app"])
estimationTauxErreur(erreur.breastcancer[,"tst"])

#estimation du taux d'erreur pour la méthode des K plus proches voisins

erreur.pima <- evaluationKppv(pima[,1:7], pima[,8])
estimationTauxErreur(erreur.pima[,"app"])
estimationTauxErreur(erreur.pima[,"tst"])

erreur.breastcancer <- evaluationKppv(breastcancer[,1:9], breastcancer[,10])
estimationTauxErreur(erreur.breastcancer[,"app"])
estimationTauxErreur(erreur.breastcancer[,"tst"])
