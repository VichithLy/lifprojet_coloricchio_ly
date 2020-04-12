<?php

namespace App\Http\Controllers\author;

use DB;
use Gate;
use Auth;
use File;
use ZipArchive;
use App\Project;
use App\Ue;
use App\Http\Controllers\Controller;
use Illuminate\Support\Facades\Storage;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Validator;
use App\Http\Requests\ProjectsRequest;

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
        //On récupère les infos de l'utilisateur connecté
        $current_user = Auth::user();
        $ue_names = $current_user->ues()->pluck('name')->toArray();
        $ue_ids = $current_user->ues()->pluck('ue_id')->toArray();

        //dd($ue_names);
        //dd($ue_ids);

        //On récupère les id des projets seulement visibles par l'utilisateur
        $author_projects = DB::table('projects')
            ->join('project_ue', 'projects.id', '=', 'project_ue.project_id')
            ->join('ues', 'project_ue.ue_id', '=', 'ues.id')
            ->select('projects.*')
            ->whereIn('ue_id', $ue_ids)
            ->orderBy('id')
            ->pluck('id')
            ->toArray(); //transforme notre collection en simple tableau d'int

        //On récupère les instances de Project suivant les id trouvés pas notre requête
        $projects = Project::whereIn('id', $author_projects)->get();
        
        //dd($projects);

        return view('author.projects.index')
        ->with('projects', $projects)
        ->with('ue_names', $ue_names)
        ->with('ue_ids', $ue_ids)
        ->with('author_projects', $author_projects);
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
        // file validation
        $validator      =   Validator::make($request->all(),
            ['file'      =>   'required|mimes:zip,rar|max:2048']);

        // if validation fails
        if($validator->fails()) {
            $request->session()->flash('error', 'Mauvais type de fichier');
        }
        
        // if validation success
        if($file = $request->file('file')) { //Si le fichier existe

            //Infos utiles du formulaire
                //Titre (nom sans l'extension)
            $title = pathinfo($request->file->getClientOriginalName(), PATHINFO_FILENAME);
                //Année
            $year = $request->year;
                //UE
            $ue = $request->ue;

            //Nom fichier avec extension
            $name = $request->file->getClientOriginalName();
            //Nom du fichier avec date d'upload
            $fileName = time().'.'.$request->file->extension(); 

            //Upload du zip dans un dossier
            
                //Dossier d'upload
            $target_path = 'uploads/projects';
                //Enregistrement vers le dossier
            if($file->move(public_path($target_path), $name)) {
                $request->session()->flash('success', 'File uploaded successfully');
            }

                //Extraction du zip dans un dossier /extracted
            $zipfile = new ZipArchive;
            //$zip_target_path = public_path('uploads/projects/extracted/' . $name);
            $zip_target_path = $target_path . '/extracted/' . $name;
            
                //On ne vérifie pas que le fichier à upload n'existe pas déjà !
            if ($zipfile->open(public_path($target_path . '/' . $name)) === TRUE)
            {
                $zipfile->extractTo(public_path($zip_target_path));
                $zipfile->close();

                $request->session()->flash('success', 'File extracted successfully');
            } else {
                
                $request->session()->flash('error', 'File not extracted');

            }

            // ----------------------- //

            //Liste des fichiers dans le dossier extrait du zip
            $project_path = $zip_target_path;
            $files_within_project = File::allfiles(public_path($project_path));

            $txt_files = array();

            /*foreach ($files_within_project as $file) {
                echo $file . "<br />";
            }*/

            //foreach (glob('/*.txt') as $file) {
                //$txt_files[] = $file;
            //}

            dd($files_within_project);
            
            

            //Lien README

            //Lien zip

            //Récupérer toutes les images dans un tableau
                //Envoyer le tabeau d'image à la vue index


            // ----------------------- //

            //Enregistrement dans la base de données 
                //Titre
                //Année
                //UE
                //Lien README
                //Path du dossier zip

        }

        
        return redirect()->route('author.projects.index');
        
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
