ROSSI Joris 
11810160

Explications de mon mini-projet

Mon mini-projet est appelé «Star Protector», c’est un mini-jeu de type shoot’em up.
Les ennemis arrivent par le haut et nous pouvons déplacer notre vaisseau avec les flèches directionnelles pour tirer sur les ennemis afin d’augmenter notre score et faire apparaître leurs chefs.
On démarre avec 5 vies.
Après le 2ème boss le dernier boss apparaît et le stage 3 entier est concentré sur ce boss avec plus d’hp.
Le but est d’éliminer leurs trois chefs pour terminer le jeu.

NB : je conseille d’avoir un très bon ordinateur car le jeu est très fluide sur mon fixe mais est lent sur les machines de Nautibus.

Comment le jeu fonctionne-t-il ?
Tous les éléments sont gérer comme des particules et sont rangés dans des tableaux de particules de différents type : munitions alliées, munitions ennemies, munitions des boss, munitions spéciales des boss, munitions pour le tir circulaire des boss ainsi que les boss, les ennemis, les bonus.
La procédure pour l’ajout du loot ne fonctionne pas mais je l’ai laissé dans le .cpp en commentaire.
J’avais prévu de faire des niveaux de difficultés différents pour au final abandonner l’idée car mon menu devenait trop dur à gérer et rajoutait des bugs. Je les ai laissées en commentaire aussi.
J’ai utilisé le principe des complexes et des vecteurs pour faire bouger mes éléments ainsi que l’attaque ultime des boss, un tir circulaire qui envoi une munition ennemie sur une trajectoire différente de 6° à chaque fois pour un total de 60 tirs simultanés.

NB2: Si le jeu est trop lent, le tir circulaire du boss risque de disparaître avant d'arriver vers le vaisseau car il est réutilisé toutes les 4 secondes.
