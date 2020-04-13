Mon mini projet de casse brique est, comme son nom l'indique, un casse brique.
Il comporte trois niveaux où il faut casser toutes les briques pour aller au niveau suivant.
Si toutes les balles sont sorties de l'écran alors on a perdu.
A partir de 10 secondes nous pouvons utiliser des bonus, avec un maximum de 2 bonus par niveau.
Ce bonus permet de faire apparaître une nouvelle balle.


Mon programme initialise une vitesse et une position par rapport a la position de la barre.
Si il reste des briques encore sur l'écran alors il calcule les collisions entre toutes les balles (contenues dans un tableau) et les briques restantes (contenues dans un tableau).
Mais aussi entre les balles elles même.
Si une balle rentre dans une brique alors il y a collision, et la balle prend la direction inverse par rapport a la face de la brique touchée. 
La brique perd "une vie" lors d'une collision avec une balle, si elle n'en a plus alors elle n'est plus affichée.
La collision entre la balle et la barre prend en compte la position de la balle par rapport au centre de la barre, plus la balle est loin plus l'angle est grand.
Le bonus qui fait apparaître une autre balle est activé avec la touche espace, cette fonction crée une nouvelle balle dans le tableau des balles.
Quand toutes les balles sont sorties de l'écran, il est affiché "game over".
Quand tous les niveaux sont finis toutes les balles s'arrêtent et il est affiché sur l'écran "you win".