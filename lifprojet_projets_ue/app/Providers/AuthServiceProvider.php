<?php

namespace App\Providers;

use Illuminate\Foundation\Support\Providers\AuthServiceProvider as ServiceProvider;
use Illuminate\Support\Facades\Gate;

class AuthServiceProvider extends ServiceProvider
{
    /**
     * The policy mappings for the application.
     *
     * @var array
     */
    protected $policies = [
        // 'App\Model' => 'App\Policies\ModelPolicy',
    ];

    /**
     * Register any authentication / authorization services.
     *
     * @return void
     */
    public function boot()
    {
        $this->registerPolicies();

        //Création d'un gate pour nos accès utilisateur
            //User
                //Admin
        Gate::define('manage-users', function($user){
            return $user->hasAnyRoles(['admin']);
        });
                //Edit
        Gate::define('edit-users', function($user){
            return $user->hasRole('admin');
        });
                //Delete
        Gate::define('delete-users', function($user){
            return $user->hasRole('admin');
        });


            //Project
        Gate::define('manage-projects', function($user){
            return $user->hasAnyRoles(['admin', 'author']);
        });   
    }
}
