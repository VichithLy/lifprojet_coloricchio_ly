Auteurs : Vichith Ly / Coloricchio Tony

Sujet : ARCM --> Développement d'un site web pour les projets des Unités d'Enseignements

Objectifs :

- Importer des projets dans la base de données
- Professeurs et élèves peuvent consulter et télécharger ces projets 


Installation :

- Installation de Composer (https://getcomposer.org/download/)

- Effectuer la commande "composer install" puis "composer global require laravel/installer" dans un terminal (à la racine du projet)

- Ensuite, il sera possible d'utiliser php artisan

- Configurer le fichier .env, en indiquant les informations de sa base de données. Voici un exemple :
- DB_CONNECTION=mysql
- DB_HOST=127.0.0.1
  DB_PORT=3306
  DB_DATABASE=laravel
  DB_USERNAME=root
  DB_PASSWORD=
 
- Effectuer les migrations vers la base de données avec la commande "php artisan migration"

- Remplir la base de données avec la commande "php artisan db:seed" **(à effectuer 2 fois de suite!!)**
