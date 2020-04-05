<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function () {
    return view('welcome');
});

Auth::routes();

Route::get('/home', 'HomeController@index')->name('home');

// ===== Admin - UsersController =====

//Route::resource('/admin/users', 'Admin\UsersController', ['except' => ['show', 'create', 'store']]); //Enlever create si création de compte par l'admin

    //Amélioration
Route::namespace('Admin')->prefix('admin')->name('admin.')->group(function() {
    Route::resource('/users', 'UsersController', ['except' => ['show', 'create', 'store']]); 

});