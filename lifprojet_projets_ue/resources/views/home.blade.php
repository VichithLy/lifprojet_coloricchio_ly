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
                        <form class="form-inline mb-2">
                            <input class="form-control mr-sm-2" type="search" placeholder="Search a project" aria-label="Search">
                            <button class="btn btn-outline-success my-2 my-sm-0" type="submit">Search</button>
                        </form>

                        <div class="input-group input-group-sm">

                            <div class="input-group-prepend ">
                                <span class="input-group-text rounded" id="inputGroup-sizing-sm">UE</span>
                            </div>
                            <div class="mr-sm-5">
                                <select class="form-control form-control-sm">
                                    <option>Tous</option>
                                    <option>LIFO63</option>
                                    <option>LIFAP6</option>
                                </select>
                            </div>

                            <div class="input-group-prepend ">
                                <span class="input-group-text rounded" id="inputGroup-sizing-sm">Année</span>
                            </div>
                            <div class="mr-sm-5">
                                <select class="form-control form-control-sm">
                                    <option>Toutes</option>
                                    <option>2018</option>
                                    <option>2019</option>
                                    <option>2020</option>
                                </select>
                            </div>

                            <div class="input-group-prepend">
                                <span class="input-group-text rounded" id="inputGroup-sizing-sm">Trier par</span>
                            </div>
                            <div>
                                <select class="form-control form-control-sm">
                                    <option>Date d'ajout</option>
                                    <option>Ordre alphabétique</option>
                                    <option>Note</option>
                                </select>
                            </div>

                        </div>
                    </nav>

                    
                    <!-- =================== CARTE PROJET ====================== -->
                    <div class="row">
                        
                        @foreach ($projects as $project)
                        
                            <div class="col-xs-12 col-sm-6 col-md-4">
                                <div class="card border-dark mb-4">
                                    <!-- Images -->
                                    <div id="carouselExampleControls{{$project->id}}" class="carousel slide" data-ride="carousel">
                                        <div class="carousel-inner">
                                            <div class="carousel-item active">
                                            <img class="card-img-top" src="{{ URL::to('/') }}/images/dora.png" alt="First slide">
                                            </div>
                                            <div class="carousel-item">
                                            <img class="card-img-top" src="{{ URL::to('/') }}/images/dora.png" alt="Second slide">
                                            </div>
                                            <div class="carousel-item">
                                            <img class="card-img-top" src="{{ URL::to('/') }}/images/dora.png" alt="Third slide">
                                            </div>
                                        </div>
                                        <a class="carousel-control-prev" href="#carouselExampleControls{{$project->id}}" role="button" data-slide="prev">
                                            <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                                            <span class="sr-only">Previous</span>
                                        </a>
                                        <a class="carousel-control-next" href="#carouselExampleControls{{$project->id}}" role="button" data-slide="next">
                                            <span class="carousel-control-next-icon" aria-hidden="true"></span>
                                            <span class="sr-only">Next</span>
                                        </a>
                                    </div>  
                                    
                                    <div class="card-body">
                                        <h5 class="card-title text-center"><strong>{{ $project->title }}</strong></h5>

                                        <ul class="list-group ">
                                            <li class="list-group-item">UE : <strong>{{ implode(', ', $project->ues()->pluck('name')->toArray()) }}</strong></li>
                                            <li class="list-group-item">Année : <strong>{{ $project->year }}</strong></li>
                                        </ul>

                                        <div class="card-text mt-3">
                                            <p><u>Description :</u></p> 
                                            {{ $project->description }}
                                        </div>
                                    </div>
                                    <ul class="list-group list-group-flush">
                                        <li class="list-group-item">
                                            <a href="#" class="card-link">README : {{ $project->readme }}</a></li>
                                        <li class="list-group-item">Note : <strong>{{ $project->mark }}/20</strong></li>
                                    </ul>
                                    <div class="card-body">
                                        <div><a href="#" class="card-link">Télécharger le projet : {{ $project->zip }}</a></div>
                                        <div><a href="{{ $project->git }}" class="card-link">Dépôt Git</a></div>
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
