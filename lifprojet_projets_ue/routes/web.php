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

//Route::get('/home', 'HomeController@index')->name('home');

//Montrer tous les projets sur la page d'accueil
Route::get('/home', 'author\ProjectsController@showAll')->name('projects.showAll');

// ===== Admin - UsersController =====

Route::namespace('Admin')->prefix('admin')->name('admin.')->middleware('can:manage-users')->group(function() {
    //middleware permet de nous assurer que seulement certains rôles ont accés aux controllers
    //cf auth provider

    Route::resource('/users', 'UsersController', ['except' => ['show', 'create', 'store']]); 
});

Route::namespace('author')->prefix('author')->name('author.')->middleware('can:manage-projects')->group(function() {
    //middleware permet de nous assurer que seulement certains rôles ont accés aux controllers
    //cf auth provider

    Route::resource('/projects', 'ProjectsController', ['except' => ['show', 'create']]); 
});

// Download Route
Route::get('download/{filename}', function($filename)
{
    // Check if file exists in app/storage/file folder
    //$file_path = public_path('uploads/projects') . '/'. $filename;
    $file_path = URL::to('/uploads/projects'). '/'. $filename;
    
    if (file_exists($file_path))
    {
        // Send Download
        return Response::download($file_path, $filename, [
            'Content-Length: '. filesize($file_path)
        ]);

 
    }
    else
    {
        //dd($file_path);
        // Error
        exit('Requested file does not exist on our server!');
    }
})->name('project.download');