<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Ue extends Model
{
    public function users() {
        
        //Un ue est possédé par plusieurs users
        return $this->belongsToMany('App\User');

    }

    public function projects() {
        
        //Un ue est possédé par plusieurs projets
        return $this->hasMany('App\Project');

    }
}
