<?php

namespace App\Http\Controllers\author;

use App\Http\Controllers\Controller;
use Gate;
use Auth;
use App\Project;
use App\Ue;
use Illuminate\Http\Request;

class ProjectsController extends Controller
{

    //Visibilité page lorsque authentifié
    public function __construct() {
        $this->middleware('auth');
    }

    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {   
        //Affiche tous les projets
        $projects = Project::all();

        //On récupère les infos de l'utilisateur connecté
        $current_user = Auth::user();
        
        $ue_names = $current_user->ues()->pluck('name')->toArray();
        $ue_ids = $current_user->ues()->pluck('ue_id')->toArray();

        //dd($ue_names);
        //dd($ue_ids);

        return view('author.projects.index')
        ->with('projects', $projects)
        ->with('ue_names', $ue_names)
        ->with('ue_ids', $ue_ids);
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        //
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        dd($request);
        return 'Je viens de créer un projet.';
    }

    /**
     * Display the specified resource.
     *
     * @param  \App\Project  $project
     * @return \Illuminate\Http\Response
     */
    public function show(Project $project)
    {
        //
    }

    public function showAll(Project $project)
    {
        $projects = Project::all();
        
        
        //->ues()->pluck('name')->toArray();

        return view('home')->with('projects', $projects);
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  \App\Project  $project
     * @return \Illuminate\Http\Response
     */
    public function edit(Project $project)
    {
        //Vérification autorisation accès en tant qu'admin ou author
        if(Gate::denies('manage-projects')){
            return redirect(route('author.projects.index'));
        }

        $projects = Project::all();
        $ues = Ue::all();

        return view('author.projects.edit')->with([
            'project' => $project,
            'ues' => $ues
        ]);
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \App\Project  $project
     * @return \Illuminate\Http\Response
     */
    public function update(ProjectsRequest $request, Project $project)
    {
        //dd($request);

        //On utilise sync() au lieu de attach() pour remplacer l'ancien ue
        $project->ues()->sync($request->ue);

        $project->title = $request->title;
        $project->year = $request->year;
        $project->description = $request->description;
        $project->mark = $request->mark;
        $project->git = $request->git;

        if($project->save()) {
            //Alerte
            $request->session()->flash('success', $project->title . ' has been updated');
        } else {
            $request->session()->flash('error', 'Error on updating the user');
        }

        return redirect()->route('author.projects.index');
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  \App\Project  $project
     * @return \Illuminate\Http\Response
     */
    public function destroy(Request $request, Project $project)
    {
 
        if (Gate::denies('manage-projects')) {
            return redirect(route('home'));
        } 

        //Suppression de l'ue
        $project->ues()->detach();
        $project->delete();
        $request->session()->flash('success', $project->title . ' has been deleted');

        return redirect()->route('author.projects.index');
    }
}
