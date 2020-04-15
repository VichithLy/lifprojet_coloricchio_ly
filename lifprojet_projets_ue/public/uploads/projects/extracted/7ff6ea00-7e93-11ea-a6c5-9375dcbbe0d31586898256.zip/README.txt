Billard - Lucie Fournier - p1811511

I - Comment jouer

Choisissez un jeu sur le menu principal :

- Jeu de la 15 (solo) : vous gagnez si vous atteignez un score de 61.
Le score augmente � chaque boule rentr�e (selon le num�ro de la boule).
Si la boule blanche tombe, vous perdez 10 points.

- Jeu de la 9 (solo) : vous gagnez si vous faites rentrer la boule 9.
Le but est de le faire avec le moins de tirs possibles.
Le principe est de toujours toucher en premier la plus petite boule sur le tapis.
Si vous touchez la mauvaise boule ou si vous faites tomber la boule blanche, votre nombre de tirs augmente de 10.

- Billard am�ricain (duo) : le joueur 1 doit faire tomber toutes les boules pleines, le joueur 2 toutes les boules ray�es.
L'un des joueurs gagne si toutes ses boules sont tomb�es et que la 8 est tomb�e (apr�s les autres !)
La partie est perdue si la boule 8 est tomb�e avant toutes les pleines ou toutes les ray�es.
Le score augmente de 1 pour chaque boule tomb�e.

Vous devez choisir l'emplacement de la bille blanche au d�but ou lorsqu'elle tombe.
Placez-la dans la zone de casse avec votre souris et cliquez pour valider.
Pour tirer, choisissez l'angle de tir avec votre souris.
Maintenez cliqu� pour choisir la force de tir.
Rel�chez pour tirer.

II - Fonctionnement du programme

	1) Structure

Les boules sont repr�sent�es par des particules, contenant :
- position, vitesse, forces de frottement, masse
- num�ro (de 1 � 15 et de -10 pour la blanche (pour appliquer les p�nalit�s))
- bool�en indiquant si la boule est tomb�e
- image

Le monde est repr�sent� par :
- un tableau de particules et un nombre de particules
- un tableau de trous (avec chacun une position)
- Une queue de tir (contenant une position, un angle, un bool�en indiquant si elle existe et une image)
- les scores, le joueur courant, le nombre de tirs, le jeu choisi
- le num�ro de la premi�re boule touch�e par la blanche et un bool�en indiquant si une boule a �t� touch�e ou non (pour le jeu de la 9)
- un tableau de murs obliques (ceux autour des poches) (avec leurs coordonn�es de d�but et de fin et leur inclinaison)
- une image de la table

	2) Initialisation

On initialise manuellement les coordonn�es :
- des bords de la table
- des murs obliques (autour des poches)
- des trous
- de la formation de d�part des boules (jeu � 15 ou � 9 boules)

On met �galement les scores, joueurs et bool�ens initiaux � leurs valeurs de d�part.

	3) Jeu

A chaque tour de boucle, le programme dessine la table, les boules et la queue (si on est en train de tirer) avec des images (draw).
Il met �galement � jour les coordonn�es des boules, selon leur vitesse et leurs forces de frottement (part_update).
Il v�rifie �galement les collisions :
- avec les bords de la table (verif_murs)
- avec les murs obliques (bords des poches) (verif_murs_obliques)
- "avec les trous" (la balle tombe dans un trou si son centre atteint le bord du trou) (verif_trou)
- entre les boules (verif_collisions)

Pour chaque collision (sauf pour les trous) :
- on replace la particule hors de la collision
- on calcule le nouveau vecteur vitesse
- on r�duit l�g�rement la vitesse apr�s le choc
Le d�tail des calculs est expliqu� dans les commentaires du programme.

Tout �a se fait dans update.

Quand toutes les boules sont immobiles (si la vitesse est tr�s faible, elle est mise � z�ro), on peut tirer.
On a plusieurs phases de tirs :
- Confirmation qu'on peut tirer et apparition de la queue
- Choix de l'angle avec la souris
- Choix de la force en restant cliqu�
- Confirmation de la fin de tir et disparition de la queue
Ces �tapes se v�rifient dans le main.

	4) Main

Le main est compos� de 5 menus :
- Un menu de d�part, pour choisir le jeu
- Un menu pour placer la boule blanche : il est appel� au d�but du jeu ou quand la boule blanche tombe
- Un menu de jeu principal qui :
	- v�rifie si la partie est gagn�e ou perdue
	- v�rifie si la boule blanche est tomb�e
	- v�rifie si on peut tirer et fait les diff�rentes �tapes de tirs
	- v�rifie si on a touch� la mauvaise boule au jeu de la 9
	- appelle update
- Un menu de partie gagn�e, qui affiche, selon le jeu, le score et/ou le nombre de tirs et/ou le joueur gagnant
- Un menu de partie perdue (que pour le billard am�ricain), qui affiche qui a perdu et les scores respectifs

	5) Autres pr�cisions

Le billard est fait selon l'�chelle 1cm = 1px, avec un zoom (de 3 par d�faut).
Si on change le zoom, les proportions restent les m�mes.
On peut changer les valeurs des forces de frottement et des diminuations de vitesse lors des chocs dans les constantes de d�but de programme.
On peut changer la force maximale de tir de la casse ou de tir classique dans les constantes de d�but de programme.
Toutes les images sont utilis�es l�galement car r�alis�es par moi.

Captures fournies :
- 1 : d�but jeu de la 15
- 2 : jeu de la 15
- 3 : Score de 36 au jeu de la 15 : les boules 10, 11 et 15 sont tomb�es
- 4 : Victoire au jeu de la 15 : on a un score de 62 (boules 6, 8, 1O, 11, 12, et 15 tomb�es)
- 5 : d�but jeu de la 9
- 6 : Victoire jeu de la 9 (la boule 9 est tomb�e gr�ce � la boule 4; on a eu des p�nalit�s en faisant tomber la blanche)
- 7 : Victoire du joueur 2 au billard am�ricain : toutes les boules ray�es sont tomb�es, et la 8 en dernier.