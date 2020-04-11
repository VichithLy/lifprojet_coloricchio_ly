<?php

namespace App\Http\Controllers\Admin;

use App\Http\Controllers\Controller;
use Gate;
use App\User;
use App\Role;
use App\Ue;
use Illuminate\Http\Request;

class UsersController extends Controller
{

    //Visibilité page lorsque authentifié
   

    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        //Affiche tous les users
        $users = User::all();

        $current_user = auth()->user();

        return view('admin.users.index')
        ->with('users', $users)
        ->with('current_user', $current_user);
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */

    /*
    public function create()
    {
        //CREER DES COMPTES PROFESSEURS ICI
    }

    
    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */

    /*

    public function store(Request $request)
    {
        //
    }

    /**
     * Display the specified resource.
     *
     * @param  \App\User  $user
     * @return \Illuminate\Http\Response
     */

    /*
    public function show(User $user)
    {
        //
    }*/


    public function getCurrentUser()
    {
        //Affiche tous les users
        $users = User::all();

        dd($users);
    }



    /**
     * Show the form for editing the specified resource.
     *
     * @param  \App\User  $user
     * @return \Illuminate\Http\Response
     */
    public function edit(User $user)
    {
        //Vérification autorisation accès en tant qu'admin
        if(Gate::denies('edit-users')){
            return redirect(route('admin.users.index'));
        }

        $roles = Role::all();
        $ues = Ue::all();

        return view('admin.users.edit')->with([
            'user' => $user,
            'roles' => $roles,
            'ues' => $ues
        ]);
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \App\User  $user
     * @return \Illuminate\Http\Response
     */
    public function update(UsersRequest $request, User $user)
    {
        //On utilise sync() au lieu de attach() car on passe en paramètre un tableau de rôles
        $user->roles()->sync($request->roles);
        $user->ues()->sync($request->ues);

        $user->name = $request->name;
        $user->email = $request->email;

        

        if($user->save()) {
            //Alerte
            $request->session()->flash('success', $user->name . ' has been updated');
        } else {
            $request->session()->flash('error', 'Error on updating the user');
        }

        return redirect()->route('admin.users.index');
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  \App\User  $user
     * @return \Illuminate\Http\Response
     */
    public function destroy(Request $request, User $user)
    {

        $role = $user->roles()->pluck('name')->first();

        //Si admin
        if($role == "admin"){

            $request->session()->flash('error', 'You cannot delete the admin');

        } else if (Gate::denies('delete-users')) {

            return redirect(route('admin.users.index'));

        } else {

            //Suppression du/des rôles
            $user->roles()->detach();
            $user->delete();
            $request->session()->flash('success', $user->name . ' has been deleted');
            
        }

        return redirect()->route('admin.users.index');
    }
}
