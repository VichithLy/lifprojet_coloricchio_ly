le programme que j'ai effectu� est bas� sur le TP des marchands de glaces avec quelques �volutions et donc l'illustration de la loi d' Hotelling :
chaque pixel repr�sente un client, l'image un centre commercial et chaque point rouge un marchand.
Par pas de temps :
-pour chaque client calcul du marchand le plus rentable (en fonction de la distance au marchand, de la distance du marchand au centre commercial et du prix des glaces)
-pour chaque marchand on essaye si cela arrange son nombre de clients de le d�placer dans toutes les directions d'un pixel et on essaye aussi de varier l�g�rement ses prix
-on trace deux graphes en fonction du temps qui sont le nombre de client et l'�volution des prix
-on affiche en temps r�el les prix de chaque marchand

j'ai choisi de faire �voluer mon syst�me sur une semaine; cela implique donc des jours de fermeture du centre commercial (affich�s) et donc la distance marchand-centre commercial ne rentre pas en compte ces jours-ci.
j'ai �galement choisi de faire un bilan de fin de semaine par marchand + les graphes + le marchand qui a le plus de clients et celui qui a gagn� le plus d'argent
j'ai enfin du modifier tout le programme pour agrandir la fen�tre grapic et faire rentrer toutes les informations
