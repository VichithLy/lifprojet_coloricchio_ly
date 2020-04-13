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

Route::get('projects/{uuid}/downloadZip', 'author\ProjectsController@downloadZip')->name('projects.downloadZip');
Route::get('projects/{uuid}/downloadReadme', 'author\ProjectsController@downloadReadme')->name('projects.downloadReadme');

Route::get('image/{project?}/{filename?}', 'author\ProjectsController@displayImage')->name('projects.displayImage');


//Displaying images

/*Route::get('image/{path?}', function ($path)
{

    $path = storage_path('/' . $path);

    if (!File::exists($path)) {
        abort(404);
    }

    $file = File::get($path);
    $type = File::mimeType($path);

    $response = Response::make($file, 200);
    $response->header("Content-Type", $type);

    return $response;
    
})->where('path', '[A-Za-z0-9_/-]+(.*)')->name('projects.image');*/