<?php

namespace App\Http\Controllers\author;

use DB;
use Gate;
use Auth;
use Response;
use File;
use ZipArchive;
use Webpatser\Uuid\Uuid;
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
        $validator = Validator::make($request->all(),
            ['file'=> 'required|mimes:zip']); //Taille max des fichiers à définir avec max:[taille en octets]

        // if validation fails
        if($validator->fails()) {

            $request->session()->flash('error', 'Mauvais type de fichier');

        } else {

                // if validation success
            if($file = $request->file('file')) { //Si le fichier existe

                //Nom fichier avec extension
                $name = time().'_'.$request->file->getClientOriginalName();
                //Nom du fichier avec date d'upload
                $fileName = time().'.'.$request->file->extension(); 

                //Upload du zip dans un dossier
                
                    //Dossier d'upload
                $target_path = 'uploads/projects';
                    //Enregistrement vers le dossier
                if($file->move(public_path($target_path), $fileName)) {
                    $request->session()->flash('success', 'File uploaded successfully');
                }

                
                    //Extraction du zip dans un dossier /extracted
                $zipfile = new ZipArchive;
                //$zip_target_path = public_path('uploads/projects/extracted/' . $name);
                $zip_target_path = $target_path . '/extracted/' . $fileName;
                
                    //On ne vérifie pas que le fichier à upload n'existe pas déjà !
                if ($zipfile->open(public_path($target_path . '/' . $fileName)) === TRUE) {
                    
                    $zipfile->extractTo(public_path($zip_target_path));
                    $zipfile->close();

                    $request->session()->flash('success', 'File extracted successfully');

                } else {
                    
                    $request->session()->flash('error', 'File not extracted');

                }

                // ----------------------- //

                //Liste des fichiers dans le dossier extrait du zip
                $all_project_files = File::allfiles(public_path($zip_target_path));

                    //Récupère tous les fichiers qui possède une extension particulière
                        //images
                $img_files = preg_grep('/\.(png|PNG|jpg|JPG|jpeg|JPEG)/', $all_project_files);

                $img_files_path = [];
                foreach ($img_files as $img) {
                    $img_name = $img->getBaseName(); //nom du fichier
                    $img_files_path[] = $img->getRelativePath() . '/' . $img_name;
                    //echo $img, '</br>';
                }

                        //fichier texte
                $txt_files = preg_grep('/\.(txt|md)/', $all_project_files);
                
                $txt_files_path = [];
                foreach ($txt_files as $txt) {
                    $txt_name = $txt->getBaseName(); //nom du fichier
                    $txt_files_path[] = $txt->getRelativePath() . '/' . $txt_name;
                    //echo $txt, '</br>';
                }

                //dd($img_files_path);
                
                //Infos utiles pour base de donnée
                
                    //Titre (nom sans l'extension)
                $title = pathinfo($request->file->getClientOriginalName(), PATHINFO_FILENAME);
                    //Année
                $year = $request->year;
                    //UE
                $ue = $request->ue;
                    //Lien README
                $readme_link = $txt_files_path[0] ?? '';
                //dd($readme_link);
                    //Lien zip
                $zip_link = $zip_target_path;
                //dd($zip_link);


                    //Les images
                //dd($img_files_path);

                    //Envoyer le tabeau d'image à la vue index


                // ----------------------- //

                //Enregistrement dans la base de données 
                    //Titre
                    //Année
                    //UE
                    //Lien README
                    //Path du dossier zip


                $img_files_path_json = json_encode($img_files_path, JSON_FORCE_OBJECT); 

                //echo $img_files_path_json;
                //dd($img_files_path_json);   

                $project_ue = Ue::where('id', $ue)->first();

                if($project_created = Project::create([
                    'uuid' => (string)Uuid::generate(),
                    'name' => $fileName,
                    'title' => $title,
                    'year' => $year,
                    'readme' => $readme_link,
                    'zip' => $zip_link,
                    'images' => $img_files_path
                    
                ])) {

                    $request->session()->flash('success', $title . ' has been created');
                    $project_created->ues()->attach($project_ue);

                } else {

                    $request->session()->flash('error', 'Project ' . $title . " can't be created");

                }
                
            }

        }
        
        return redirect()->route('author.projects.index');
        
    }

    //Download an uploaded file
    public function downloadZip(Request $request, $uuid)
    {
        
        $project = Project::where('uuid', $uuid)->firstOrFail();
        $pathToFile = public_path('uploads/projects/' . $project->name);

        //Rajouter cas 404 not found
        if(is_file($pathToFile)) {

            return response()->download($pathToFile);

        } else {

            $request->session()->flash('error', "This projects can't be downloaded");

            //Redirection suivant les rôles
            if (Auth::user()->hasAnyRoles(['admin', 'author'])) {
                return redirect()->route('author.projects.index');
            }
            return redirect()->route('projects.showAll');

        }
    }

    public function downloadReadme(Request $request, $uuid)
    {
        $project = Project::where('uuid', $uuid)->firstOrFail();
        $pathToFile = public_path('uploads/projects/extracted/' . $project->name . '/' . $project->readme);
        
        if(is_file($pathToFile)) {
            return response()->download($pathToFile);
        } else { 
            
            $request->session()->flash('error', "This projects doesn't have any README file");

            if (Auth::user()->hasAnyRoles(['admin', 'author'])) {
                return redirect()->route('author.projects.index');
            }
            return redirect()->route('projects.showAll');
        }

        
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

    public function showAll(Request $request, Project $project)
    {

        /*$user = User::where('name','LIKE','%'.$q.'%')->orWhere('email','LIKE','%'.$q.'%')->get();
        if(count($user) > 0)
            return view('welcome')->withDetails($user)->withQuery ( $q );
        else return view ('welcome')->withMessage('No Details found. Try to search again !');*/


        $projects = Project::orderByDesc('created_at')->get();

        $search = $request->search;

        if(isset($search)) {
            echo $search;
            $projects = Project::where('title', 'LIKE', '%' . $search . '%')
                            ->orWhere('name','LIKE','%'. $search .'%')
                            ->orWhere('year','LIKE','%'. $search .'%')
                            ->orWhere('description','LIKE','%'. $search .'%')    
                            ->get();
        }

        if(isset($request)) {

            if($request->sort == 1) {

                 $projects = Project::all();

            } else if ($request->sort == 2) {

                $projects = Project::orderBy('title')->get();

            } else if ($request->sort == 3) {

                $projects = Project::orderByDesc('title')->get();

            } else if ($request->sort == 4) {

                $projects = Project::orderByDesc('mark')->get();

            } else if ($request->sort == 5) {

                $projects = Project::orderBy('mark')->get();

            } 

        } 
        

        return view('home')
            ->with('projects', $projects)
            ->with('sort', $request->sort)
            ->with('search', $search);

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

        //BDD
            //Suppression de l'ue
        $project->ues()->detach();
        $project->delete();

        //Fichiers
        $file_zip = public_path('uploads/projects/' . $project->name);
        $file_extracted = public_path('uploads/projects/extracted/' . $project->name);
        File::delete($file_zip); //zip
        File::deleteDirectory($file_extracted); //dossier

        $request->session()->flash('success', $project->title . ' has been deleted');

        return redirect()->route('author.projects.index');
    }
}
