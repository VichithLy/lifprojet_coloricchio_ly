# Site des projets d'Unités d'Enseignement (UE)

**Auteurs :** Vichith Ly / Coloricchio Tony

**Informations générales**

LIFPROJET : Site web de gestion de projets d'Unités d'Enseignement (UE)

**Prérequis**
*  Installer Composer : [https://getcomposer.org/download/](https://getcomposer.org/download/)
*  Installer Laravel : composer global require "laravel/installer"
    *  Informer la variable d’environnement path de l’emplacement du dossier …/composer/vendor/bin.
*  Télécharger Laragon ou Wamp ou autre logiciel du même type selon l'OS
*  Télécharger l'application et la mettre dans le dossier www
    
**Démarrage**

*  Test local du projet :
    
    1. Ouvrir le fichier env. et compléter/modifier les champs pour la connexion à la base de données
        * Si utilisation de la base de données dans le projet (script de la BDD à la racine du projet) :
            * DB_DATABASE=lifprojet_projets_ue_bdd
            * DB_USERNAME=root
            * DB_PASSWORD=
        * Si à partir d'une base vide : 
            * Modifier le fichier env. avec les informations de votre BDD  
            * Ajouter les migrations Laravel dans la BDD avec artisan : php artisan migrate
            * Peupler la BDD : php artisan db:seed (ATTENTION Faire cette commande deux fois pour peupler les utilisateurs et les projets)
    2. Ouvrir depuis un navigateur : [http://localhost/lifprojet_coloricchio_ly/lifprojet_projets_ue/public](http://localhost/lifprojet_coloricchio_ly/lifprojet_projets_ue/public)

    

    