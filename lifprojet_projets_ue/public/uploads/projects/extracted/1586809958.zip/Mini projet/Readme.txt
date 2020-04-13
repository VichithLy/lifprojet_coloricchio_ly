JUST Maxime P1803674

Mon projet est un jeu de plateforme s'inspirant de new super mario bros Wii U.


Mini-projet de LIFAMI : "New Super Mario Bros WII U for Grapic"


Le but du jeu :
Vous contrôlez mario. Pour chaque niveau accessible depuis la map de séléction (map avec les rectangles noirs),
vous devez vous rendre le plus loin possible tout en restant en vie. Une fois les 5 niveaux terminés vous gagnez le jeu, 
mais attention au début vous n'avez que 5 vie, mais vous pouvez en gagnez grâce à des bonus ou à des pièces. Si vous perdez vos 5 vies, vous devez recommencer les 5 niveaux. 
Le niveau 1 est la porte la plus à gauche, le niveau 2 le deuxième plus à gauche et ainsi de suite.

Contrôle :
Flèche du haut : Sauter ou rentrer dans un niveau
Flèche de gauche : Allez à gauche
Flèche de droite : Allez à droite
Entrer : Pause (uniquement dans un niveau)



Ce jeu contient :
- Plusieurs ennemis : les tchomp, les goomba, les koopas, les fleurs de feu, les bills.
- Différents bonus : des pièces, des champignons qui font agrandir ou rétrécir mario, des champignons qui lui font gagner une vie.
- Des tiles animés : tiles power up, checkpoint (un par niveau)
- Des tiles mobiles
- Tiles spéciales : décoration, traversable sauf par le haut, destructible
- Possibilité de régler la taille des tiles et de la fenêtre dans la limite du raisonnable.


Comment il le fait :
	- Au niveau de la map, tout est fait sur la base du tilemapping (dans un tableau 2D). Il est donc facile de rajouter des niveaux (pour les éléments spéciaux il sont explique dans le code). 

	- Les goombas, koopas, champignons et le personnage de mario sont soumis à la force de gravité, avec les contraintes de la map qui les arrêtes si il faut.

	- Les fondus sont fait par interpolation linéaire (le bilinéaire prenait trop de mémoire).
	
	- L'agrandissement de mario est aussi fait par interpolation linéaire.

	- Le mario a aussi une force de déplacement latéral à l'appui de la flèche gauche ou droite. A l'appui de la flèche du haut une vitesse initiale lui est donné pour qu'il puisse sauter

	- Pour affichez les différents menus et pour pouvoir utiliser des boucles la vérification de la fenêtre est effectué et ainsi (sauf pendant le chargement des images au début) la fenêtre peut être fermé à tout moment

	- Tout les bonus et les ennemis (sauf la fleurs) ainsi que mario ont chacun des vecteurs vitesses et des forces qui leur sont appliqué selon Newton.

	- Des particules sont également présentes pour les débris des tiles destructibles
Remarque :
Certaines images sont plus ou moins mal découpé, en effet, n'étant pas graphiste il m'a été compliqué de trouver certains sprites (en particulier ceux de mario).
Le code n'est pas optimisé sur certains point mais grapic n'étant pas une bibliothèque avec beaucoup de fonction, il était plutôt difficile de faire certaines choses.
Les collisions avec le décor ne sont pas non plus bien faites.

Amusez-vous et surtout si vous créez de nouveau niveau pour vous amusez je serai ravie de pouvoir les récupérer ;) 

	


