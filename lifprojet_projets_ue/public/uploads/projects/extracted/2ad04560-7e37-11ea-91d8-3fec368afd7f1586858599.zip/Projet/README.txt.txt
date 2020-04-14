Mon programme est un Proies Vs Pr�dateurs am�lior�.
Il s'agit � la fois d'une simulation et d'un jeu.

Au d�but de la simulation, les r�gles sont affich�es dans la console et des param�tres initiaux sont demand�s � l'utilisateur. 
Une fois ceux-ci correctement remplis, la simulation commence.
Les cases de la grille sont initialis�es, une "rivi�re" et des "gu�s" sont g�n�r�s al�atoirement et des proies et pr�dateurs apparaissent al�atoirement. 
Le jeu commence ensuite.
Il consiste en l'�volution par �tape (des jours) des proies et des pr�dateurs. Les pr�dateurs veulent d�vorer les proies, qui tentent de leur �chapper.
Des facteurs tels que la soif, la famine, la vieillesse et la maladie peuvent causer leur mort, raison pour laquelle ils int�ragissent avec les cases voisines (pour manger, boire, se d�placer, se reproduire), mais �galement avec le reste de la grille (pour fuir ou chasser).
Ils peuvent �galement se reproduire afin de perp�tuer l'esp�ce.
Afin d'�viter une surpopulation, seuls les "adultes", ceux vivant depuis au moins 1/3 de leur dur�e de vie maximale, peuvent s'accoupler. De m�me, il existe un syst�me de reproduction sexu�e et les femelles ne peuvent pas mettre bas chaque jour.

Afin de cr�er une "animation" de pluie (laide, mais au moins on comprend de quoi il s'agit), j'ai utilis� 3 images que j'ai altern�es dans la fonction draw.

J'ai d� utiliser un algorithme de recherche du "meilleur coup", bas� sur mes connaissances de l'algorithme d'�checs minimax simplifi� (on ne recherche que le meilleur coup � l'instant T, pas le meilleur coup dans le futur).

Des menus permettent au joueur de modifier les param�tres afin d'aider ou d�favoriser une des esp�ces. (ATTENTION : AFIN D'AMELIORER L'UTILISATION DE CES MENUS, J'AI MODIFIE UN PARAMETRE DE GRAPIC ! Et leur couleur, que je trouvais tr�s peu agr�able)
Quand un param�tre est modifi�, on passe au jour suivant, et l'�volution de l'�cosyst�me a lieue.
Si le joueur ne souhaite pas modifier de param�tre, il peut simplement passer le jour, ou bien attendre 12s que cela se fasse seul.
Afin de cr�er ce timing, j'ai utilis� la librairie time pour cr�er une sorte d'horloge, permettant � la simulation d'avancer seule ou avec l'intervention du joueur.

Si une des esp�ces dispara�t ou devient trop envahissante, la simulation prend fin, une animation d�clare la d�faite, puis le jeu recommence tout seul.

Le plus difficile a �t� de trouver des id�es d'am�liorations. Le code en lui-m�me, en dehors de la fonction d'�volution, est tr�s basique. Cette derni�re m'a cependant demand� pas mal d'efforts pour la rendre assez efficace et g�rer les diff�rents param�tres qui s'ajoutaient sans cesse.