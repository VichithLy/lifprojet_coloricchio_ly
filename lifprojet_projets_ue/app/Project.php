<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Project extends Model
{
    /*protected $fillable = [
        'title', 'year', 'description', 'git',
    ];*/

    //Implémentation des ue projects
    public function ues() {

        //Un User possèdent plusieurs roles
        return $this->belongsToMany('App\Ue');

    }

    //Contrôle sur les ue pour accès author
    public function hasAnyUes($ues) {

        if($this->ues()->whereIn('name', $ues)->first()) {
            return true;
        }

        return false;
    }

    public function hasUe($ue) {

        if($this->ues()->where('name', $ue)->first()) {
            return true;
        }

        return false;
    }
}
