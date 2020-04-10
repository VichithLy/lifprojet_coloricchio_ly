<?php

use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\Hash;
use App\User;
use App\Role;
use App\Ue;

class UsersTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        User::truncate();
        DB::table('role_user')->truncate();
        DB::table('ue_user')->truncate();

        //Roles
        $adminRole = Role::where('name', 'admin')->first();
        $authorRole = Role::where('name', 'author')->first();
        $userRole = Role::where('name', 'user')->first(); 

        $admin = User::create([
            'name' => 'Admin User',
            'email' => 'admin@admin.com',
            'password' => Hash::make('password')
        ]);

        $author = User::create([
            'name' => 'Author User',
            'email' => 'author@author.com',
            'password' => Hash::make('password')
        ]);

        $user = User::create([
            'name' => 'Generic User',
            'email' => 'user@user.com',
            'password' => Hash::make('password')
        ]);

        $admin->roles()->attach($adminRole);
        $author->roles()->attach($authorRole);
        $user->roles()->attach($userRole);
            
        //UE
        $authorUe = Ue::where('name', 'LIFASR1')->first();  

        $admin->ues()->attach(Ue::where('name', 'LIFAP1')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFASR1')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFASR3')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFAMI')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFAP2')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFASR2')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFAP3')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFBDW1')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFASR4')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFAP4')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFAP5')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFPROLOG')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFGRAPHIQUE')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFASR5')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFIHM')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFAP6')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFASR6')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFBDW2')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFLC')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFLF')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFAP7')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFPROJET')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFASR7')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFAlgoNum/Optim')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFDATA')->first());
        $admin->ues()->attach(Ue::where('name', 'LIFSTAGE')->first());
        
        $author->ues()->attach($authorUe);
            

    }
}
