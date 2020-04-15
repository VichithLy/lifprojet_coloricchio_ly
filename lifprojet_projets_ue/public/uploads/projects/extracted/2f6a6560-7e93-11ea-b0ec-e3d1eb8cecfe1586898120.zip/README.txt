Tom Ogier
11804144

le projet que j'ai fais en lifami est un jeu de tir/visé composé de deux niveaux.
le but du jeu est de mettre la balle bleu clair dans la cible elle-même bleu clair tout en evitant les obstacles bleu foncé
dans le premier niveau, il n'y a que des balles bleu foncé comme obstacle et dans le niveau deux il y a en plus une planche entre le stand de tir et la cible 

pour visé il faut utiliser les touches directionnelles gauche et droite,
pour lancer la balle il faut ramener la balle vers le joueur grâce au touches directionnelles haut et bas
plus la balle est ramenée vers le joueur plus elle va vite 
pour lancer la balle après l'avoir rapproché il faut utiliser la touche espace
attention si vous utiliser la touche espace sans avoir rapproché la balle, elle sera lancée sans force, elle n'avancera donc pas
En conclusion si votre balle touche un obstacle bleu foncé vous perdez si elle touche la cible bleue clair vous gagnez


Ce programme est basé principalement sur le système de particules(rotation, scale, translation etc...) et les équations physiques de Newton
Toutes les balles( bleu clair ou foncé ) sont des particules composées d'une position, d'une masse, d'une vitesse et d'une force 
la vitesse dépend de la vitesse a l'instant t-1, de la masse et de la force
la position dépend de la position t-1 et de la vitesse
Pour la visée j'utilise le système de masse ressort 
Dans ce programme il y a des collisions pour savoir si il y a victoire ou défaite 
soit ce sont des collisions en calculant la distance entre deux particules 
soit ce sont des collisions dépendant de la position de la particule dans la fenêtre