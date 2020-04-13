Billard - Lucie Fournier - p1811511

I - Comment jouer

Choisissez un jeu sur le menu principal :

- Jeu de la 15 (solo) : vous gagnez si vous atteignez un score de 61.
Le score augmente à chaque boule rentrée (selon le numéro de la boule).
Si la boule blanche tombe, vous perdez 10 points.

- Jeu de la 9 (solo) : vous gagnez si vous faites rentrer la boule 9.
Le but est de le faire avec le moins de tirs possibles.
Le principe est de toujours toucher en premier la plus petite boule sur le tapis.
Si vous touchez la mauvaise boule ou si vous faites tomber la boule blanche, votre nombre de tirs augmente de 10.

- Billard américain (duo) : le joueur 1 doit faire tomber toutes les boules pleines, le joueur 2 toutes les boules rayées.
L'un des joueurs gagne si toutes ses boules sont tombées et que la 8 est tombée (après les autres !)
La partie est perdue si la boule 8 est tombée avant toutes les pleines ou toutes les rayées.
Le score augmente de 1 pour chaque boule tombée.

Vous devez choisir l'emplacement de la bille blanche au début ou lorsqu'elle tombe.
Placez-la dans la zone de casse avec votre souris et cliquez pour valider.
Pour tirer, choisissez l'angle de tir avec votre souris.
Maintenez cliqué pour choisir la force de tir.
Relâchez pour tirer.

II - Fonctionnement du programme

	1) Structure

Les boules sont représentées par des particules, contenant :
- position, vitesse, forces de frottement, masse
- numéro (de 1 à 15 et de -10 pour la blanche (pour appliquer les pénalités))
- booléen indiquant si la boule est tombée
- image

Le monde est représenté par :
- un tableau de particules et un nombre de particules
- un tableau de trous (avec chacun une position)
- Une queue de tir (contenant une position, un angle, un booléen indiquant si elle existe et une image)
- les scores, le joueur courant, le nombre de tirs, le jeu choisi
- le numéro de la première boule touchée par la blanche et un booléen indiquant si une boule a été touchée ou non (pour le jeu de la 9)
- un tableau de murs obliques (ceux autour des poches) (avec leurs coordonnées de début et de fin et leur inclinaison)
- une image de la table

	2) Initialisation

On initialise manuellement les coordonnées :
- des bords de la table
- des murs obliques (autour des poches)
- des trous
- de la formation de départ des boules (jeu à 15 ou à 9 boules)

On met également les scores, joueurs et booléens initiaux à leurs valeurs de départ.

	3) Jeu

A chaque tour de boucle, le programme dessine la table, les boules et la queue (si on est en train de tirer) avec des images (draw).
Il met également à jour les coordonnées des boules, selon leur vitesse et leurs forces de frottement (part_update).
Il vérifie également les collisions :
- avec les bords de la table (verif_murs)
- avec les murs obliques (bords des poches) (verif_murs_obliques)
- "avec les trous" (la balle tombe dans un trou si son centre atteint le bord du trou) (verif_trou)
- entre les boules (verif_collisions)

Pour chaque collision (sauf pour les trous) :
- on replace la particule hors de la collision
- on calcule le nouveau vecteur vitesse
- on réduit légèrement la vitesse après le choc
Le détail des calculs est expliqué dans les commentaires du programme.

Tout ça se fait dans update.

Quand toutes les boules sont immobiles (si la vitesse est très faible, elle est mise à zéro), on peut tirer.
On a plusieurs phases de tirs :
- Confirmation qu'on peut tirer et apparition de la queue
- Choix de l'angle avec la souris
- Choix de la force en restant cliqué
- Confirmation de la fin de tir et disparition de la queue
Ces étapes se vérifient dans le main.

	4) Main

Le main est composé de 5 menus :
- Un menu de départ, pour choisir le jeu
- Un menu pour placer la boule blanche : il est appelé au début du jeu ou quand la boule blanche tombe
- Un menu de jeu principal qui :
	- vérifie si la partie est gagnée ou perdue
	- vérifie si la boule blanche est tombée
	- vérifie si on peut tirer et fait les différentes étapes de tirs
	- vérifie si on a touché la mauvaise boule au jeu de la 9
	- appelle update
- Un menu de partie gagnée, qui affiche, selon le jeu, le score et/ou le nombre de tirs et/ou le joueur gagnant
- Un menu de partie perdue (que pour le billard américain), qui affiche qui a perdu et les scores respectifs

	5) Autres précisions

Le billard est fait selon l'échelle 1cm = 1px, avec un zoom (de 3 par défaut).
Si on change le zoom, les proportions restent les mêmes.
On peut changer les valeurs des forces de frottement et des diminuations de vitesse lors des chocs dans les constantes de début de programme.
On peut changer la force maximale de tir de la casse ou de tir classique dans les constantes de début de programme.
Toutes les images sont utilisées légalement car réalisées par moi.

Captures fournies :
- 1 : début jeu de la 15
- 2 : jeu de la 15
- 3 : Score de 36 au jeu de la 15 : les boules 10, 11 et 15 sont tombées
- 4 : Victoire au jeu de la 15 : on a un score de 62 (boules 6, 8, 1O, 11, 12, et 15 tombées)
- 5 : début jeu de la 9
- 6 : Victoire jeu de la 9 (la boule 9 est tombée grâce à la boule 4; on a eu des pénalités en faisant tomber la blanche)
- 7 : Victoire du joueur 2 au billard américain : toutes les boules rayées sont tombées, et la 8 en dernier.