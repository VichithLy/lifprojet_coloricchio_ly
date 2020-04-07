<?php

namespace App;

use Illuminate\Contracts\Auth\MustVerifyEmail;
use Illuminate\Foundation\Auth\User as Authenticatable;
use Illuminate\Notifications\Notifiable;

class User extends Authenticatable
{
    use Notifiable;

    /**
     * The attributes that are mass assignable.
     *
     * @var array
     */
    protected $fillable = [
        'name', 'email', 'password',
    ];

    /**
     * The attributes that should be hidden for arrays.
     *
     * @var array
     */
    protected $hidden = [
        'password', 'remember_token',
    ];

    /**
     * The attributes that should be cast to native types.
     *
     * @var array
     */
    protected $casts = [
        'email_verified_at' => 'datetime',
    ];

    //Implémentation des roles users
    public function roles() {

        //Un User possèdent plusieurs roles
        return $this->belongsToMany('App\Role');

    }

    //Contrôle sur les rôles pour accès utilisateur
    public function hasAnyRoles($roles) {

        //On regarde si les rôles de la table roles matchent avec les rôles passés en paramètre (par rapport à la colonne name)
        if($this->roles()->whereIn('name', $roles)->first()) {
            return true;
        }

        return false;
    }

    public function hasRole($role) {

        if($this->roles()->where('name', $role)->first()) {
            return true;
        }

        return false;
    }
}
