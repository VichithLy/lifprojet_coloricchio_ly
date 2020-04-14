/* README.txt

Mini-projet LIFAMI

CORCORAL Thomas
P1802691
Groupe : C / Séquence 2
Rapporteur de projet : PARIS Axel

2019 */

Qu'est-ce que LE MONDE DES PARTICULES ?

Il s'agit d'un jeu réalisé dans le cadre de l'UE LIFAMI.
Ce dernier est composé de 4 mini-jeux, qui s'articulent autour d'une petite histoire. 

Le but est de sauver la planète des particules d'un robot qui souhaite prendre possession de leur planète.

Le but du premier mini-jeu est de récupérer des particules avec un seau afin d'engrenger le plus haut score possible.
Par la suite votre but sera de conserver un maximum de particules.

Pour le second, votre fusée s'est fait toucher par un astéroïde et vous devez actionner la manette d'urgence.
Cependant les particules que vous avez récupéré auparavant sont fixées au sol mais si vous les touchez, elles seront
aspirées dans l'espace. Vous devrez donc faire attention pour ne pas trop en perdre.

Dans le cadre du troisième mini-jeu votre fusée étant endommagée, vous vous êtes posé sur la Lune. Votre fusée est désormais
réparée mais des astéroïdes ne veulent pas vous laisser repartir. Esquivez les pendant 1 minute pour pouvoir terminer votre voyage.

Enfin, vous arriverez sur la planète des particules. Vous devrez alors sélectionner une arme pour pouvoir éliminer le robot.
Chaque arme a ses caractéristiques : Image, dégats, délai de rechargement, temps de trajet, consommation de particules.



En ce qui concerne le programme :


Chaque mini-jeu est articulé autour d'une structure. On retrouve donc une structure principale World puis 4 structures pour chacun des mini-jeu mini_jeu1 / mini_jeu2 ...
Chacune des ces structures possède des paramètres propre à son mini-jeu.


En ce qui concerne les structures des mini-jeux :

1ere : La structure comporte les coordonées du seau (avec une structure Vec2), un tableau de particules,
le nombre de particules et enfin le score.

2nde : La structure fait tout d'abord appelle à une autre structure nommée Personnage. Comme son nom l'indique elle
va représenter le personnage jouable. Elle est composée d'une image et de ses coordonnées. Le score, un tableau de
particules et enfin le nombre de particules

3ème : Un vec2 pour les coordonnées du personnage, le score, le nombre d'astéroïdes, le pas de temps.
Puis on utilise la structure nommée DirectionMj3 qui fait appel à un tableau d'image (pour l'image de déplacement à droite
et l'image de déplacement à gauche). Puis un indice nommé direction qui prend la valeur 0 ou 1 en fonction des actions 
de l'utilisateur et choisira l'image de déplacement appropriée.
Enfin la structure fait appel à un tableau d'astéroïdes. La structure des astéroïdes comporte un tableau de particule, le nombre
de particules, un tableau de ressorts, le nombre de ressorts et un Vec2 qui représente le centre de l'astéroide pour la gestion des collisions.

4ème : Fait appel à la structure robot qui contient une Image, un vec2 pour les coordonnées, un second Vec2 pour sa vitesse, puis la vie restante.
Un autre Personnage (Image + coordonnées) pour le viseur, un tableau de particules pour les balles, le nombre de balles, le score, un entier représentant
l'arme choisit, un tableau d'armes. La structure arme comportant le délai de rechargement, les dégats, la consommation de particules, le temps de trajet des balles,
puis l'image de l'arme. 
Et enfin une variable appelé dernier_Tir qui retiendra l'heure du dernier tir pour le délai de rechargement.


Ensuite la structure World :

	Elle fait appel à chacune des 4 structures ci-dessus, un entier pour l'avancé de la présentation en début de jeu,
un tableau d'images pour la présentation. Un entier pour l'avancé des mini-jeux ou autres étapes de transition.
Un tableau d'images pour les fonds d'écrans. Un tableau d'images pour les images de transition, le pas de temps.
Puis une variable pour connaitre l'heure de début de chaque mini-jeux.



	Pour le fonctionnement du programme, une première fonction initialise les premières variables nécessaire au fonctionnement du programme et les images.
Puis le main fait appel à la fonction update qui en fonction de la valeur de la variable Step de la fonction World (qui représente l'avancé
du programme) va définir quelle fonction appeler.
Les mini jeux utilisent des fonctions update et draw qui appelent elles mêmes d'autres fonctions avec des rôles précis si nécessaire
Entre certains mini-jeux il y a des phases de transition qui sont elles aussi gérées par le switch de la fonction update.

	Lors du lancement du programmes deux premières images défilent (à l'aide de la fonction elapsedtime() ) toutes les 10 secondes. Puis le permier jeu se lance.
Cela fait donc 20 secondes ce qui est assez longs, vous avez donc la possibilité de passer en appuyant sur jouer en bas à droite. Le programme vérifie que la souris est bien placée 
sur l'écran et que l'utilisateur appuie sur le clique gauche.
Ensuite le premier jeu se lance. Vous devez attraper des balles avec un seau. Les déplacements se font avec les flèches droite et gauche. Le programme bloque les 
déplacements à l'arrivé sur les bordures. Le programme fait apparaitre une particule toutes les secondes à l'aide d'une fonction spéciale qui renvoie une particule
avec des paramètres précis. Le programme vérifie également si la particule rentre dans le seau. Il fait également appel à une fonction qui gère les rebonds avec le seau
et une autre qui fait évoluer les particules en fonction de leur force, de leur position et de leur vitesse.
Si la particule rentre dans le seau elle n'est plus affichée ou mise à jour car un booléen dans la structure particle nommé etat est passé en false.
Quand le programme est lancé depuis 54 secondes, on passe à l'étape suivante.

	Une image de transition apparait pour forcer l'utilisateur à placer sa souris à un endroit précis puis à cliquer dessus. Le mini-jeu est donc initialisé. 
Les particules sont placées aléatoirement dans la fusée. Ensuite le mini-jeu se lance. 
Dans celui-ci l'utilisateur déplace un personnage à l'aide de sa souris à l'intérieur d'une fusée. Le programme vérifie que le joueur n'entre pas en contact 
avec une particule. Ou bien que la souris ne sorte pas de la fusée. Si le joueur atteint la fusée, il gagne et on passe au mini-jeu suivant.

	Celui-ci est un peu plus complexe en terme de fonctions annexe car il fait appel à des particules, des ressorts et toute la physique qui vient avec.
Pour ce faire j'ai réutilisé les fonctions des TPs puis j'y ai rajouté celles propres au programme tel que celle qui gère la création d'un astéroïde, les collision sur la Lune
Les collisions avec l'astronaute et également les collisions entre les deux astéroïdes. Une autre fonction met à jour la position du milieu des astéroïdes. Le programme update
du mini jeu gère les déplacements ainsi que le cas d'arrêt au cas ou le mini jeu est lancé depuis 1 minute ou bien que le score est nul.

	Ensuite une fonction qui initialise toutes les armes est lancée. Une image de transition est également lancée. L'utilisateur choisit une arme en cliquant dessus, le 
programme analyse le clique et les coordonnées de ce dernier pour sélectionner l'arme.
Le mini-jeu se lance alors. Lorsque l'utilisateur clique, une balle est tirée si le délai de rechargement est dépassé. Cette balle possède des caractéristiques spéciales.
En effet le programme calcul la vitesse en x de la balle à l'aide de la position du viseur et du temps de trajet de l'arme séléctionné. Une fonction gère les cas de collision entre
les balles et le robot. Une autre gère la mise à jour de la position de la balle en fonction de sa position et de sa vitesse. On néglige les forces dans ce mini-jeu.
En ce qui concerne le robot, il est imprévisible et c'est la qu'est la difficulté. Le programme vérifie que le robot n'est pas à la brodure et ci ce n'est pas le cas il modifie sa 
vitesse de déplacement latéral entre -4 et +4 ce qui peut le faire accélérer et faire demi-tour d'un coup.

L'image de conclusion est géré par deux variable, le score et la variable qui gère l'évolution du programme. 
Chaque mini jeu possède une fonction draw qui affiche tous les éléments de ce dernier (particules, ressorts, personnage, image de fond etc...)
Avant de lancer un mini-jeu une fonction d'initialisation de ce dernier est lancée.


	En bref, chaque mini-jeu possède sa structure, sa fonction update, sa fonction d'initialisation, sa fonction draw et se fonctions de physique qui réalisent les intéractions.
L'étape du programme est définie par la variable Step de la structure world. Le changement de mini-jeu s'effectue par des cas d'arrêt placé dans les fonctions update.



