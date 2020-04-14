/* README.txt

Mini-projet LIFAMI

CORCORAL Thomas
P1802691
Groupe : C / S�quence 2
Rapporteur de projet : PARIS Axel

2019 */

Qu'est-ce que LE MONDE DES PARTICULES ?

Il s'agit d'un jeu r�alis� dans le cadre de l'UE LIFAMI.
Ce dernier est compos� de 4 mini-jeux, qui s'articulent autour d'une petite histoire. 

Le but est de sauver la plan�te des particules d'un robot qui souhaite prendre possession de leur plan�te.

Le but du premier mini-jeu est de r�cup�rer des particules avec un seau afin d'engrenger le plus haut score possible.
Par la suite votre but sera de conserver un maximum de particules.

Pour le second, votre fus�e s'est fait toucher par un ast�ro�de et vous devez actionner la manette d'urgence.
Cependant les particules que vous avez r�cup�r� auparavant sont fix�es au sol mais si vous les touchez, elles seront
aspir�es dans l'espace. Vous devrez donc faire attention pour ne pas trop en perdre.

Dans le cadre du troisi�me mini-jeu votre fus�e �tant endommag�e, vous vous �tes pos� sur la Lune. Votre fus�e est d�sormais
r�par�e mais des ast�ro�des ne veulent pas vous laisser repartir. Esquivez les pendant 1 minute pour pouvoir terminer votre voyage.

Enfin, vous arriverez sur la plan�te des particules. Vous devrez alors s�lectionner une arme pour pouvoir �liminer le robot.
Chaque arme a ses caract�ristiques : Image, d�gats, d�lai de rechargement, temps de trajet, consommation de particules.



En ce qui concerne le programme :


Chaque mini-jeu est articul� autour d'une structure. On retrouve donc une structure principale World puis 4 structures pour chacun des mini-jeu mini_jeu1 / mini_jeu2 ...
Chacune des ces structures poss�de des param�tres propre � son mini-jeu.


En ce qui concerne les structures des mini-jeux :

1ere : La structure comporte les coordon�es du seau (avec une structure Vec2), un tableau de particules,
le nombre de particules et enfin le score.

2nde : La structure fait tout d'abord appelle � une autre structure nomm�e Personnage. Comme son nom l'indique elle
va repr�senter le personnage jouable. Elle est compos�e d'une image et de ses coordonn�es. Le score, un tableau de
particules et enfin le nombre de particules

3�me : Un vec2 pour les coordonn�es du personnage, le score, le nombre d'ast�ro�des, le pas de temps.
Puis on utilise la structure nomm�e DirectionMj3 qui fait appel � un tableau d'image (pour l'image de d�placement � droite
et l'image de d�placement � gauche). Puis un indice nomm� direction qui prend la valeur 0 ou 1 en fonction des actions 
de l'utilisateur et choisira l'image de d�placement appropri�e.
Enfin la structure fait appel � un tableau d'ast�ro�des. La structure des ast�ro�des comporte un tableau de particule, le nombre
de particules, un tableau de ressorts, le nombre de ressorts et un Vec2 qui repr�sente le centre de l'ast�roide pour la gestion des collisions.

4�me : Fait appel � la structure robot qui contient une Image, un vec2 pour les coordonn�es, un second Vec2 pour sa vitesse, puis la vie restante.
Un autre Personnage (Image + coordonn�es) pour le viseur, un tableau de particules pour les balles, le nombre de balles, le score, un entier repr�sentant
l'arme choisit, un tableau d'armes. La structure arme comportant le d�lai de rechargement, les d�gats, la consommation de particules, le temps de trajet des balles,
puis l'image de l'arme. 
Et enfin une variable appel� dernier_Tir qui retiendra l'heure du dernier tir pour le d�lai de rechargement.


Ensuite la structure World :

	Elle fait appel � chacune des 4 structures ci-dessus, un entier pour l'avanc� de la pr�sentation en d�but de jeu,
un tableau d'images pour la pr�sentation. Un entier pour l'avanc� des mini-jeux ou autres �tapes de transition.
Un tableau d'images pour les fonds d'�crans. Un tableau d'images pour les images de transition, le pas de temps.
Puis une variable pour connaitre l'heure de d�but de chaque mini-jeux.



	Pour le fonctionnement du programme, une premi�re fonction initialise les premi�res variables n�cessaire au fonctionnement du programme et les images.
Puis le main fait appel � la fonction update qui en fonction de la valeur de la variable Step de la fonction World (qui repr�sente l'avanc�
du programme) va d�finir quelle fonction appeler.
Les mini jeux utilisent des fonctions update et draw qui appelent elles m�mes d'autres fonctions avec des r�les pr�cis si n�cessaire
Entre certains mini-jeux il y a des phases de transition qui sont elles aussi g�r�es par le switch de la fonction update.

	Lors du lancement du programmes deux premi�res images d�filent (� l'aide de la fonction elapsedtime() ) toutes les 10 secondes. Puis le permier jeu se lance.
Cela fait donc 20 secondes ce qui est assez longs, vous avez donc la possibilit� de passer en appuyant sur jouer en bas � droite. Le programme v�rifie que la souris est bien plac�e 
sur l'�cran et que l'utilisateur appuie sur le clique gauche.
Ensuite le premier jeu se lance. Vous devez attraper des balles avec un seau. Les d�placements se font avec les fl�ches droite et gauche. Le programme bloque les 
d�placements � l'arriv� sur les bordures. Le programme fait apparaitre une particule toutes les secondes � l'aide d'une fonction sp�ciale qui renvoie une particule
avec des param�tres pr�cis. Le programme v�rifie �galement si la particule rentre dans le seau. Il fait �galement appel � une fonction qui g�re les rebonds avec le seau
et une autre qui fait �voluer les particules en fonction de leur force, de leur position et de leur vitesse.
Si la particule rentre dans le seau elle n'est plus affich�e ou mise � jour car un bool�en dans la structure particle nomm� etat est pass� en false.
Quand le programme est lanc� depuis 54 secondes, on passe � l'�tape suivante.

	Une image de transition apparait pour forcer l'utilisateur � placer sa souris � un endroit pr�cis puis � cliquer dessus. Le mini-jeu est donc initialis�. 
Les particules sont plac�es al�atoirement dans la fus�e. Ensuite le mini-jeu se lance. 
Dans celui-ci l'utilisateur d�place un personnage � l'aide de sa souris � l'int�rieur d'une fus�e. Le programme v�rifie que le joueur n'entre pas en contact 
avec une particule. Ou bien que la souris ne sorte pas de la fus�e. Si le joueur atteint la fus�e, il gagne et on passe au mini-jeu suivant.

	Celui-ci est un peu plus complexe en terme de fonctions annexe car il fait appel � des particules, des ressorts et toute la physique qui vient avec.
Pour ce faire j'ai r�utilis� les fonctions des TPs puis j'y ai rajout� celles propres au programme tel que celle qui g�re la cr�ation d'un ast�ro�de, les collision sur la Lune
Les collisions avec l'astronaute et �galement les collisions entre les deux ast�ro�des. Une autre fonction met � jour la position du milieu des ast�ro�des. Le programme update
du mini jeu g�re les d�placements ainsi que le cas d'arr�t au cas ou le mini jeu est lanc� depuis 1 minute ou bien que le score est nul.

	Ensuite une fonction qui initialise toutes les armes est lanc�e. Une image de transition est �galement lanc�e. L'utilisateur choisit une arme en cliquant dessus, le 
programme analyse le clique et les coordonn�es de ce dernier pour s�lectionner l'arme.
Le mini-jeu se lance alors. Lorsque l'utilisateur clique, une balle est tir�e si le d�lai de rechargement est d�pass�. Cette balle poss�de des caract�ristiques sp�ciales.
En effet le programme calcul la vitesse en x de la balle � l'aide de la position du viseur et du temps de trajet de l'arme s�l�ctionn�. Une fonction g�re les cas de collision entre
les balles et le robot. Une autre g�re la mise � jour de la position de la balle en fonction de sa position et de sa vitesse. On n�glige les forces dans ce mini-jeu.
En ce qui concerne le robot, il est impr�visible et c'est la qu'est la difficult�. Le programme v�rifie que le robot n'est pas � la brodure et ci ce n'est pas le cas il modifie sa 
vitesse de d�placement lat�ral entre -4 et +4 ce qui peut le faire acc�l�rer et faire demi-tour d'un coup.

L'image de conclusion est g�r� par deux variable, le score et la variable qui g�re l'�volution du programme. 
Chaque mini jeu poss�de une fonction draw qui affiche tous les �l�ments de ce dernier (particules, ressorts, personnage, image de fond etc...)
Avant de lancer un mini-jeu une fonction d'initialisation de ce dernier est lanc�e.


	En bref, chaque mini-jeu poss�de sa structure, sa fonction update, sa fonction d'initialisation, sa fonction draw et se fonctions de physique qui r�alisent les int�ractions.
L'�tape du programme est d�finie par la variable Step de la structure world. Le changement de mini-jeu s'effectue par des cas d'arr�t plac� dans les fonctions update.



