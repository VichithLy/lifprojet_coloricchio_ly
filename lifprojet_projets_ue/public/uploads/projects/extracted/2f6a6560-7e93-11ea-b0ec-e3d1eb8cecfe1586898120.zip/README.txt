Tom Ogier
11804144

le projet que j'ai fais en lifami est un jeu de tir/vis� compos� de deux niveaux.
le but du jeu est de mettre la balle bleu clair dans la cible elle-m�me bleu clair tout en evitant les obstacles bleu fonc�
dans le premier niveau, il n'y a que des balles bleu fonc� comme obstacle et dans le niveau deux il y a en plus une planche entre le stand de tir et la cible 

pour vis� il faut utiliser les touches directionnelles gauche et droite,
pour lancer la balle il faut ramener la balle vers le joueur gr�ce au touches directionnelles haut et bas
plus la balle est ramen�e vers le joueur plus elle va vite 
pour lancer la balle apr�s l'avoir rapproch� il faut utiliser la touche espace
attention si vous utiliser la touche espace sans avoir rapproch� la balle, elle sera lanc�e sans force, elle n'avancera donc pas
En conclusion si votre balle touche un obstacle bleu fonc� vous perdez si elle touche la cible bleue clair vous gagnez


Ce programme est bas� principalement sur le syst�me de particules(rotation, scale, translation etc...) et les �quations physiques de Newton
Toutes les balles( bleu clair ou fonc� ) sont des particules compos�es d'une position, d'une masse, d'une vitesse et d'une force 
la vitesse d�pend de la vitesse a l'instant t-1, de la masse et de la force
la position d�pend de la position t-1 et de la vitesse
Pour la vis�e j'utilise le syst�me de masse ressort 
Dans ce programme il y a des collisions pour savoir si il y a victoire ou d�faite 
soit ce sont des collisions en calculant la distance entre deux particules 
soit ce sont des collisions d�pendant de la position de la particule dans la fen�tre