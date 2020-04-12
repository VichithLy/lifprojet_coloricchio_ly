DANTIER Florian
p1710759

Mini projet : Find the way
Thème : Particules

Toutes les images sont stockées sont dans data/

Pour ce mini-projet j'ai choisi de faire une sorte de minigolf.
Le but étant d’amener la balle à destination, au drapeau.
Pour ce faire, nous devons cliquer avec le bouton gauche de la souris afin de déplacer la balle.
Plus on reste appuyé longtemps dessus plus la balle partira avec de la vitesse, avec une limite de 3 secondes au maximum.
La balle est une particule, représenté par une image.
Il y a bien évidemment plusieurs obstacles : 

1) Des murs classiques, la balle rebondit donc dessus. 
-> Ces obstacles ont donc nécessité de gérer les percussions avec d'autres choses que les bords de la fenêtre.

2) Des murs destructibles, la balle rebondit dessus si elle a une vitesse inférieure à une valeur spécifiée sinon, si
la balle a une vitesse supérieure à cette valeur le mur "se casse" et donc la balle passe à travers.
-> Ces obstacles ont nécessité les mêmes compétences que les murs classiques avec en plus une gestion de la vitesse
au moment de l'impact de la balle pour que le mur disparaisse.

3) Des murs inclinés, avec pour but de faire rebondir la balle sur des murs non alignés avec le repère afin d'ajouter
des réactions un peu plus complexes que sur des murs "droits".
-> Pour gérer ces rebonds, j'ai dû avoir recours à une formule mathématique modélisant ce phénomène. Les rebonds sont
donc bien plus durs à gérer sur ces murs, là où l'on inversait simplement une composante pour les rebonds "classiques".

4) Des trous noirs qui font donc office d'obstacles. Ces derniers n'attirent pas la balle sur toute la carte, mais 
uniquement dans un rayon d'action symbolisée par un cercle rouge (non plein).
-> Pour établir ces objets j'ai dû me servir des notions vu dans le thème particule et de quelques notions basique de géométrie.
L'attraction des trous noirs sont effectués via les équations de la mécanique Newtonienne : F = G * (masseA * masseB ) / d² ...

5) Des trous basiques, à éviter à tout prix !! A la différence des trous noirs où, avec suffisamment de vitesse on peut les traverser, 
ces trous-ci font perdre la partie et recommencez au dernier checkpoint dès que l'on y passe.
-> Pour ces objets, il m'a suffi de détecter la distante + rayon entre la balle et ces trous pour gérer cette mécanique.

Enfin, en dernier "objets" il y a le point d'arrivée, symbolisé par un trou et un drapeau. Ce dernier est géré exactement comme les "trous basiques"
sauf que cette fois-ci lorsque l'on arrive dessus, cela nous fait gagner la partie.

Mis à part cela, le jeu dispose d'un menu graphique à son lancement, permettant de choisir entre deux parcours de mini golf.
Lorsque la partie est gagnée, vous pourrez voir une message vous indiquant le nombre de coups total fait pour arrivée à la fin du parcours et 
le menu de départ est de nouveau disponible afin de relancer une partie sur l'un des deux parcours.

