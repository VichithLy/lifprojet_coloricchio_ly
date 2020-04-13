<style>

    /* Classe obligatoire pour les flèches */
    .flecheDesc {
        width: 0; 
        height: 0; 
        float:right;
        margin: 10px;
        border-left: 5px solid transparent;
        border-right: 5px solid transparent;
        border-bottom: 5px solid black;
      }
      .flecheAsc {
        width: 0; 
        height: 0;
        float:right;
        margin: 10px;
        border-left: 5px solid transparent;
        border-right: 5px solid transparent;
        border-top: 5px solid black;
      }
    

</style>

<script>

  // Tri dynamique de tableau HTML
  function twInitTableau() {
    // Initialise chaque tableau de classe « avectri »
       [].forEach.call( document.getElementsByClassName("avectri"), function(oTableau) {
       var oEntete = oTableau.getElementsByTagName("tr")[0];
       var nI = 1;
      [].forEach.call( oEntete.querySelectorAll("th:not([class])"), function(oTh) {
        oTh.addEventListener("click", twTriTableau, false);
        oTh.setAttribute("data-pos", nI);
        if(oTh.getAttribute("data-tri")=="1") {
         oTh.innerHTML += "<span class=\"flecheDesc\"></span>";
        } else {
          oTh.setAttribute("data-tri", "0");
          oTh.innerHTML += "<span class=\"flecheAsc\"></span>";
        }
        // Tri par défaut
        if (oTh.className=="selection") {
          oTh.click();
        }
        nI++;
      });
    });
  }
  
  function twInit() {
    twInitTableau();
  }
  function twPret(maFonction) {
    if (document.readyState != "loading"){
      maFonction();
    } else {
      document.addEventListener("DOMContentLoaded", maFonction);
    }
  }
  twPret(twInit);

  function twTriTableau() {
    // Ajuste le tri
    var nBoolDir = this.getAttribute("data-tri");
    this.setAttribute("data-tri", (nBoolDir=="0") ? "1" : "0");
    // Supprime la classe « selection » de chaque colonne.
    [].forEach.call( this.parentNode.querySelectorAll("th"), function(oTh) {oTh.classList.remove("selection");});
    // Ajoute la classe « selection » à la colonne cliquée.
    this.className = "selection";
    // Ajuste la flèche
    this.querySelector("span").className = (nBoolDir=="0") ? "flecheAsc" : "flecheDesc";

    // Construit la matrice
    // Récupère le tableau (tbody)
    var oTbody = this.parentNode.parentNode.parentNode.getElementsByTagName("tbody")[0]; 
    var oLigne = oTbody.rows;
    var nNbrLigne = oLigne.length;
    var aColonne = new Array(), i, j, oCel;
    for(i = 0; i < nNbrLigne; i++) {
      oCel = oLigne[i].cells;
      aColonne[i] = new Array();
      for(j = 0; j < oCel.length; j++){
        aColonne[i][j] = oCel[j].innerHTML;
      }
    }

    // Trier la matrice (array)
    // Récupère le numéro de la colonne
    var nIndex = this.getAttribute("data-pos");
    // Récupère le type de tri (numérique ou par défaut « local »)
    var sFonctionTri = (this.getAttribute("data-type")=="num") ? "compareNombres" : "compareLocale";
    // Tri
    aColonne.sort(eval(sFonctionTri));
    // Tri numérique
    function compareNombres(a, b) {return a[nIndex-1] - b[nIndex-1];}

    function compareLocale(a, b) {return a[nIndex-1].localeCompare(b[nIndex-1]);}
    // Renverse la matrice dans le cas d’un tri descendant
    if (nBoolDir==0) aColonne.reverse();
    
    // Construit les colonne du nouveau tableau
    for(i = 0; i < nNbrLigne; i++){
      aColonne[i] = "<td>"+aColonne[i].join("</td><td>")+"</td>";
    }

    // assigne les lignes au tableau
    oTbody.innerHTML = "<tr>"+aColonne.join("</tr><tr>")+"</tr>";
  }

</script>

@extends('layouts.app')

@section('content')
    <div class="row justify-content-center">
        <div class="col-md-12">


            <div class="card">
                
                <div class="card-header">Projects management </div>
                
                <div class="card-body">
                    @if (session('status'))
                        <div class="alert alert-success" role="alert">
                            {{ session('status') }}
                        </div>
                    @endif  


                    <!-- =================== UPLOAD DE PROJETS ====================== -->

                    <div class="border rounded mb-4">
                        <div class="font-weight-bold h5 m-2">
                            Ajouter des projets
                        </div>

                        <div class="m-3 pt-2 pr-2 pl-2 border rounded">
                            Pré-requis des projets à upload : 
                            <ul>
                                <li>Dossier au format <strong>.zip UNIQUEMENT</strong></li>
                                <li>Un titre de dossier explicite (nom du projet et noms des étudiant)</li>
                                <li>Des images au format <strong>.png</strong> ou <strong>.jpg</strong> ou <strong>.jpeg</strong></li>
                                <li>Un fichier README au format <strong>.txt</strong> ou <strong>.md</strong></li>
                            </ul>
                        </div>

                        <!-- Formulaire projet -->

                        <div class="mt-4 mr-3 ml-3">
                            <form action="{{ route('author.projects.store') }}" method="POST" enctype="multipart/form-data">

                                @csrf

                                <div class="input-group">

                                    <!-- ====== Champ UE ====== -->

                                    <div class="input-group-prepend mb-2">
                                        <span class="input-group-text rounded" id="inputGroup-sizing-sm">UE</span>
                                    </div>
                                    <div class="mr-sm-5">
       
                                        <select name="ue" class="form-control ">
                                            @foreach (array_combine($ue_ids, $ue_names) as $id => $name)                                     
                                                <option value="{{ $id }}">{{ $name }}</option> 
                                            @endforeach                                                            
                                        </select>

                                    </div>

                                    <!-- ====== Champ année ====== -->

                                    <div class="input-group-prepend mb-2">
                                        <span class="input-group-text rounded" id="">Year</span>
                                    </div>
                                    <div class="mr-sm-5">
                                        <input id="year" type="number" class="form-control" name="year" value="{{ date('Y') }}" min="1950" max="{{ date('Y') }}" autofocus>
                                        @error('year')
                                            <p class="help is-invalid">{{ $message }}</p>
                                        @enderror
                                    </div>

                                </div>

                                    <!-- ====== Champ upload ====== -->
                                
                                <div class="custom-file mt-3 mb-3">
                                    <input type="file" name="file" class="custom-file-input" id="customFile" required>
                                    <label class="custom-file-label" for="customFile">Choose file</label>
                                </div>

                                <div class="form-group">
                                    <button type="submit" class="form-control">Submit</button>
                                </div>

                            </form>
                        </div>
                    </div>

                    <!-- =================== PROJECTS MANAGEMENT ====================== -->

                    

                    <div class="table-responsive">

                        <table class="avectri table table-bordered ">

                            <thead>
                                <tr>
                                    <th class="no_arrow" scope="col">Action</th>
                                    <th scope="col" >#</th>                                  
                                    <th scope="col">Title</th>
                                    <th scope="col">Year</th>       
                                    <th scope="col">UE</th>
                                    <th scope="col">Comment</th>
                                    <th scope="col">README</th>
                                    <th scope="col">Mark</th>
                                    <th scope="col">Zip</th>
                                    <th scope="col">Git</th>
                                    <th scope="col">Created at</th>
                                    
                                </tr>
                            </thead>
                            
                            <tbody>

                                @foreach ($projects as $project)
                                    
                                    <tr>

                                        <th>
                                            <a href="{{ route('author.projects.edit', $project->id) }}"> 
                                                <button type="button" class="btn btn-primary mb-2">Edit</button>
                                            </a>
                                            
                                            @can('manage-projects')    
                                                <form action="{{ route('author.projects.destroy', $project->id) }}" method="POST">
                                                    @csrf

                                                    {{ method_field('DELETE') }}

                                                    <button type="submit" class="btn btn-danger">Delete</button>
                                                </form> 
                                            @endcan
                                        </th>       

                                        <td scope="row">{{ $project->id }}</td>

                                    
                                        <td>{{ $project->title }}</td>
                                        <td>{{ $project->year }}</td>                                
                                        <td>{{ implode(', ', $project->ues()->pluck('name')->toArray()) }}</td>
                                        <td>{{ $project->description }}</td>
                                        <td><a href="{{ route('projects.downloadReadme', $project->uuid ?? '') }}">README</td>
                                        <td>{{ $project->mark }}/20</td>
                                        <td>
                                            <a href="{{ route('projects.downloadZip', $project->uuid ?? '') }}">Télécharger le projet</a>
                                        
                                        </td>
                                        <td><a href="{{ $project->git }}" target="_blank">Dépôt git</td>
                                        <td>{{ $project->created_at }}</td>
                                                     
                                    </tr>
                            @endforeach
                            </tbody>

                        </table>
                    </div>

                </div>
            </div>
        </div>
    </div>
@endsection

@section('script')
    <style>
        .carousel-control-prev-icon {
            background-image: url("data:image/svg+xml;charset=utf8,%3Csvg xmlns='http://www.w3.org/2000/svg' fill='%23303030' viewBox='0 0 8 8'%3E%3Cpath d='M5.25 0l-4 4 4 4 1.5-1.5-2.5-2.5 2.5-2.5-1.5-1.5z'/%3E%3C/svg%3E");
        }

        .carousel-control-next-icon {
            background-image: url("data:image/svg+xml;charset=utf8,%3Csvg xmlns='http://www.w3.org/2000/svg' fill='%23303030' viewBox='0 0 8 8'%3E%3Cpath d='M2.75 0l-1.5 1.5 2.5 2.5-2.5 2.5 1.5 1.5 4-4-4-4z'/%3E%3C/svg%3E");
        }
    </style>
@endsection
