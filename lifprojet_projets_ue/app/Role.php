<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Role extends Model
{
    public function users() {
        
        //Un role est possédé par plusieurs users
        return $this->belongsToMany('App\User');

    }
}
