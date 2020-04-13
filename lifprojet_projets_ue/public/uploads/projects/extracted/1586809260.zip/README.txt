le programme que j'ai effectué est basé sur le TP des marchands de glaces avec quelques évolutions et donc l'illustration de la loi d' Hotelling :
chaque pixel représente un client, l'image un centre commercial et chaque point rouge un marchand.
Par pas de temps :
-pour chaque client calcul du marchand le plus rentable (en fonction de la distance au marchand, de la distance du marchand au centre commercial et du prix des glaces)
-pour chaque marchand on essaye si cela arrange son nombre de clients de le déplacer dans toutes les directions d'un pixel et on essaye aussi de varier légèrement ses prix
-on trace deux graphes en fonction du temps qui sont le nombre de client et l'évolution des prix
-on affiche en temps réel les prix de chaque marchand

j'ai choisi de faire évoluer mon système sur une semaine; cela implique donc des jours de fermeture du centre commercial (affichés) et donc la distance marchand-centre commercial ne rentre pas en compte ces jours-ci.
j'ai également choisi de faire un bilan de fin de semaine par marchand + les graphes + le marchand qui a le plus de clients et celui qui a gagné le plus d'argent
j'ai enfin du modifier tout le programme pour agrandir la fenêtre grapic et faire rentrer toutes les informations
