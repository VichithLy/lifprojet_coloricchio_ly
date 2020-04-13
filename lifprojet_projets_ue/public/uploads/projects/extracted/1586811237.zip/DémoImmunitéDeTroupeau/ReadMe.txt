ReadMe

Démo Immunité de troupeau

En épidémiologie, le concept d'immunité de troupeau est le fait que si le taux de vaccination au seins d'une population est très élevée (>90%), la propagation d'une maladie infectieuse peut être stoppée. Un individu malade a très peu de chance de rentrer en contact avec un individu non vacciné. Ce phénomène permet de protéger des personnes ne pouvant pas être vaccinées (ex: les individus immunodeficients).
Au vu de l'épidémie de rougeole actuelle et la montée du mouvement antivax, ce sujet d'actualité rappelle que le choix de se vacciner ou pas peut avoir une influence sur les plus fragiles d'entre nous.


Dans cette démonstration, 5 populations avec différents taux de vaccination sont exposées à la même maladie, définie par sa virulence, et sa distance de contamination. Un patient 0 (malade) est placé au centre de la population. On observe en suite la dispertion de la maladie parmis les individus non vaccinés. Un graphique présente ces résultats en montrant le nombre de personnes infectées en fonction du temps. Pour chaque simulation, le taux de vaccination de la population et la couleur de sa courbe sur le graphique sont indiqués.
A chaque update de la simulation, le programme parcours le tableau des individus et pour chaque indidividus malade, il évalue la distance avec les individus non vaccinés. Si cette distance est plus petite que la distance de contamination, alors l'individus non vacciné à une chance (pondérée à la distance) d'être infecté.

Les paramètres utilisés sont:
taille de la population
Distance de contamination: 25
Virulence: 50% (un individu malade à 50% de chance d'infecter un individu non vacciné lorsqu'ils sont à une distance de 0)
Taille d'une la population: 1000
Taille d'une simulation: 300x300
Taux de vaccination: 0, 25, 50, 75, 95

On remarque que lorsque le taux de vaccination est très haut, la maladie ne peut pas se propager entre les personnes non vaccinées qui sont protégées par les personnes vaccinées. On peut aussi remarquer que pour une population avec un taux de vaccination élevée (75%) la maladie se propage quand même. 
