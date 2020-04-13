JUST Maxime P1803674

Mon projet est un jeu de plateforme s'inspirant de new super mario bros Wii U.


Mini-projet de LIFAMI : "New Super Mario Bros WII U for Grapic"


Le but du jeu :
Vous contr�lez mario. Pour chaque niveau accessible depuis la map de s�l�ction (map avec les rectangles noirs),
vous devez vous rendre le plus loin possible tout en restant en vie. Une fois les 5 niveaux termin�s vous gagnez le jeu, 
mais attention au d�but vous n'avez que 5 vie, mais vous pouvez en gagnez gr�ce � des bonus ou � des pi�ces. Si vous perdez vos 5 vies, vous devez recommencer les 5 niveaux. 
Le niveau 1 est la porte la plus � gauche, le niveau 2 le deuxi�me plus � gauche et ainsi de suite.

Contr�le :
Fl�che du haut : Sauter ou rentrer dans un niveau
Fl�che de gauche : Allez � gauche
Fl�che de droite : Allez � droite
Entrer : Pause (uniquement dans un niveau)



Ce jeu contient :
- Plusieurs ennemis : les tchomp, les goomba, les koopas, les fleurs de feu, les bills.
- Diff�rents bonus : des pi�ces, des champignons qui font agrandir ou r�tr�cir mario, des champignons qui lui font gagner une vie.
- Des tiles anim�s : tiles power up, checkpoint (un par niveau)
- Des tiles mobiles
- Tiles sp�ciales : d�coration, traversable sauf par le haut, destructible
- Possibilit� de r�gler la taille des tiles et de la fen�tre dans la limite du raisonnable.


Comment il le fait :
	- Au niveau de la map, tout est fait sur la base du tilemapping (dans un tableau 2D). Il est donc facile de rajouter des niveaux (pour les �l�ments sp�ciaux il sont explique dans le code). 

	- Les goombas, koopas, champignons et le personnage de mario sont soumis � la force de gravit�, avec les contraintes de la map qui les arr�tes si il faut.

	- Les fondus sont fait par interpolation lin�aire (le bilin�aire prenait trop de m�moire).
	
	- L'agrandissement de mario est aussi fait par interpolation lin�aire.

	- Le mario a aussi une force de d�placement lat�ral � l'appui de la fl�che gauche ou droite. A l'appui de la fl�che du haut une vitesse initiale lui est donn� pour qu'il puisse sauter

	- Pour affichez les diff�rents menus et pour pouvoir utiliser des boucles la v�rification de la fen�tre est effectu� et ainsi (sauf pendant le chargement des images au d�but) la fen�tre peut �tre ferm� � tout moment

	- Tout les bonus et les ennemis (sauf la fleurs) ainsi que mario ont chacun des vecteurs vitesses et des forces qui leur sont appliqu� selon Newton.

	- Des particules sont �galement pr�sentes pour les d�bris des tiles destructibles
Remarque :
Certaines images sont plus ou moins mal d�coup�, en effet, n'�tant pas graphiste il m'a �t� compliqu� de trouver certains sprites (en particulier ceux de mario).
Le code n'est pas optimis� sur certains point mais grapic n'�tant pas une biblioth�que avec beaucoup de fonction, il �tait plut�t difficile de faire certaines choses.
Les collisions avec le d�cor ne sont pas non plus bien faites.

Amusez-vous et surtout si vous cr�ez de nouveau niveau pour vous amusez je serai ravie de pouvoir les r�cup�rer ;) 

	


