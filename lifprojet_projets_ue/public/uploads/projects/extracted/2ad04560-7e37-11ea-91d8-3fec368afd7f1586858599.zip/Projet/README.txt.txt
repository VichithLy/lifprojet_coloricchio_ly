Mon programme est un Proies Vs Prédateurs amélioré.
Il s'agit à la fois d'une simulation et d'un jeu.

Au début de la simulation, les règles sont affichées dans la console et des paramètres initiaux sont demandés à l'utilisateur. 
Une fois ceux-ci correctement remplis, la simulation commence.
Les cases de la grille sont initialisées, une "rivière" et des "gués" sont générés aléatoirement et des proies et prédateurs apparaissent aléatoirement. 
Le jeu commence ensuite.
Il consiste en l'évolution par étape (des jours) des proies et des prédateurs. Les prédateurs veulent dévorer les proies, qui tentent de leur échapper.
Des facteurs tels que la soif, la famine, la vieillesse et la maladie peuvent causer leur mort, raison pour laquelle ils intéragissent avec les cases voisines (pour manger, boire, se déplacer, se reproduire), mais également avec le reste de la grille (pour fuir ou chasser).
Ils peuvent également se reproduire afin de perpétuer l'espèce.
Afin d'éviter une surpopulation, seuls les "adultes", ceux vivant depuis au moins 1/3 de leur durée de vie maximale, peuvent s'accoupler. De même, il existe un système de reproduction sexuée et les femelles ne peuvent pas mettre bas chaque jour.

Afin de créer une "animation" de pluie (laide, mais au moins on comprend de quoi il s'agit), j'ai utilisé 3 images que j'ai alternées dans la fonction draw.

J'ai dû utiliser un algorithme de recherche du "meilleur coup", basé sur mes connaissances de l'algorithme d'échecs minimax simplifié (on ne recherche que le meilleur coup à l'instant T, pas le meilleur coup dans le futur).

Des menus permettent au joueur de modifier les paramètres afin d'aider ou défavoriser une des espèces. (ATTENTION : AFIN D'AMELIORER L'UTILISATION DE CES MENUS, J'AI MODIFIE UN PARAMETRE DE GRAPIC ! Et leur couleur, que je trouvais très peu agréable)
Quand un paramètre est modifié, on passe au jour suivant, et l'évolution de l'écosystème a lieue.
Si le joueur ne souhaite pas modifier de paramètre, il peut simplement passer le jour, ou bien attendre 12s que cela se fasse seul.
Afin de créer ce timing, j'ai utilisé la librairie time pour créer une sorte d'horloge, permettant à la simulation d'avancer seule ou avec l'intervention du joueur.

Si une des espèces disparaît ou devient trop envahissante, la simulation prend fin, une animation déclare la défaite, puis le jeu recommence tout seul.

Le plus difficile a été de trouver des idées d'améliorations. Le code en lui-même, en dehors de la fonction d'évolution, est très basique. Cette dernière m'a cependant demandé pas mal d'efforts pour la rendre assez efficace et gérer les différents paramètres qui s'ajoutaient sans cesse.