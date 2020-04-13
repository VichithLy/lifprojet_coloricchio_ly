@extends('layouts.app')

@section('content')
    <div class="row justify-content-center">
        <div class="col-md-12">
            <div class="card">
                
                <div class="card-header">Home</div>

                

                <!-- =================== NOTIFICATION ====================== -->

                <div class="card-body">
                    @if (session('status'))
                        <div class="alert alert-success" role="alert">
                            {{ session('status') }}
                        </div>
                    @endif  
              
                    <!-- =================== BARRE DE RECHERCHE ====================== -->

                    <nav class="navbar navbar-light mb-3">

                        
                    <form class="form-inline mb-2" action="" method="GET">            
                            <input class="form-control mr-sm-2" type="search" placeholder="Search a project" aria-label="Search">
                            <button class="btn btn-outline-success my-2 my-sm-0" type="submit">Search</button>
                    </form>    
                        
                    <form class="form-inline mb-2" action="{{ route('projects.showAll') }}" method="GET">

                            @csrf

                        <div class="input-group input-group-sm">

                            <div class="input-group-prepend ">
                                <span class="input-group-text rounded" id="inputGroup-sizing-sm">UE</span>
                            </div>
                            <div class="mr-sm-3">
                                <select class="form-control form-control-sm" name="ue">
                                    <option value="1" selected>Tous</option>
                                    <option value="2">LIFO63</option>
                                    <option value="3">LIFAP6</option>
                                </select>
                            </div>

                            <div class="input-group-prepend ">
                                <span class="input-group-text rounded" id="inputGroup-sizing-sm">Année</span>
                            </div>
                            <div class="mr-sm-3">
                                <select class="form-control form-control-sm" name="year">
                                    <option value="1">Toutes</option>
                                    <option value="2">2018</option>
                                    <option value="3">2019</option>
                                    <option value="4">2020</option>
                                </select>
                            </div>

                            <div class="input-group-prepend">
                                <span class="input-group-text rounded" id="inputGroup-sizing-sm">Trier par</span>
                            </div>
                            <div>
                                <select class="form-control form-control-sm" name="sort">
                                    <option value="1">Date d'ajout</option>
                                    <option value="2">Ordre alphabétique</option>
                                    <option value="3">Note</option>
                                </select>
                            </div>
                            

                        </div>

                        <button type="submit" class="btn btn-secondary btn-sm float-right ml-2">
                            Submit
                        </button>

                        </form>
                    </nav>

                    
                    <!--<img src="{{ asset('storage/uploads/projects/extracted/full_jpg.jpg') }}" alt="aaa">-->
                    

                    <!-- =================== CARTE PROJET ====================== -->
                    <div class="row">                      
                        
                    

                        @foreach ($projects as $project)
                            
                            <div class="col-xs-12 col-sm-6 col-md-4">
                                <div class="card border-dark mb-4">
                                    

                                    

                                    <div id="carouselExampleSlidesOnly" class="carousel slide" data-ride="carousel" data-interval="1000">
                                        <div class="carousel-inner">
                                            
                                            @if (isset($projects->find($project->id)->images[0]))
                                                    <div class="carousel-item active">
                                                        <img class="d-block w-100" style="max-height:15em" src="{{URL::to('/uploads/projects/extracted/' . $project->name . '/' . $projects->find($project->id)->images[0]) }}" alt="First slide">
                                                    </div>    
                                                @endif

                                        </div>
                                    </div>

    
                                    <div class="card-body">
                                        <h5 class="card-title text-center"><strong>{{ $project->title }}</strong></h5>

                                        <ul class="list-group ">
                                            <li class="list-group-item">UE : <strong>{{ implode(', ', $project->ues()->pluck('name')->toArray()) }}</strong></li>
                                            <li class="list-group-item">Année : <strong>{{ $project->year }}</strong></li>
                                        </ul>

                                        <div class="card-text mt-3">
                                            <p><u>Commentaire :</u></p> 
                                            {{ $project->description }}
                                        </div>
                                    </div>
                                    <ul class="list-group list-group-flush">
                                        <li class="list-group-item">
                                            <a href="{{ route('projects.downloadReadme', $project->uuid ?? '') }}">README</a>
                                        </li>
                                        <li class="list-group-item">Note : <strong>{{ $project->mark }}/20</strong></li>
                                    </ul>
                                    <div class="card-body">
                                        <div><a href="{{ route('projects.downloadZip', $project->uuid ?? '') }}" class="card-link">Télécharger le projet</a></div>
                                        <div><a href="{{ $project->git ?? '' }}" class="card-link" target="_blank">Dépôt Git</a></div>
                                    </div>

                                </div>
                            </div>
                            
                        @endforeach
                    
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
