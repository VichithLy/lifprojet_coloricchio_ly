@extends('layouts.app')

@section('content')
    <div class="row justify-content-center">
        <div class="col-md-12">
            <div class="card">
                
                <div class="card-header">Projects panel</div>

                

                <div class="card-body">
                    @if (session('status'))
                        <div class="alert alert-success" role="alert">
                            {{ session('status') }}
                        </div>
                    @endif  


                    <!-- =================== UPLOAD DE PROJETS ====================== -->

                    <nav class="navbar navbar-light border rounded mb-4">
                        <div class="font-weight-bold h5 mb-3">
                            Ajouter des projets
                         </div>

                        <div class="input-group input-group-sm">

                            <div class="input-group-prepend mb-2">
                                <span class="input-group-text rounded" id="inputGroup-sizing-sm">UE</span>
                            </div>
                            <div class="mr-sm-5">
                                <select class="form-control form-control-sm">
                                    <option>LIFO63</option>
                                    <option>LIFAP6</option>
                                </select>
                            </div>

                            <div class="input-group-prepend mb-2">
                                <span class="input-group-text rounded" id="inputGroup-sizing-sm">Année</span>
                            </div>
                            <div class="mr-sm-5">
                                <select class="form-control form-control-sm">
                                    <option>Aucune</option>
                                    <option>2018</option>
                                    <option>2019</option>
                                    <option>2020</option>
                                </select>
                            </div>

                            
                        </div>

                        <div class="custom-file">
                            <input type="file" class="custom-file-input" id="customFile">
                            <label class="custom-file-label" for="customFile">Upload a project</label>
                        </div>
                    </nav>

                    
                    <!-- =================== BARRE DE RECHERCHE ====================== -->

                    <nav class="navbar navbar-light mb-3">
                        <form class="form-inline mb-2">
                            <input class="form-control mr-sm-2" type="search" placeholder="Search a projet" aria-label="Search">
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
                    <div class="card-columns">
                        
                        <div class="card border-dark">
                            <!-- Images -->
                            <div id="carouselExampleControls0" class="carousel slide" data-ride="carousel">
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
                                <a class="carousel-control-prev" href="#carouselExampleControls0" role="button" data-slide="prev">
                                    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                                    <span class="sr-only">Previous</span>
                                </a>
                                <a class="carousel-control-next" href="#carouselExampleControls0" role="button" data-slide="next">
                                    <span class="carousel-control-next-icon" aria-hidden="true"></span>
                                    <span class="sr-only">Next</span>
                                </a>
                            </div>  
                            
                            <div class="card-body">
                                <h5 class="card-title text-center"><strong>Dora & Babouche</strong></h5>

                                <ul class="list-group ">
                                    <li class="list-group-item">UE : <strong>Dessins animés</strong></li>
                                    <li class="list-group-item">Année : <strong>2020</strong></li>
                                </ul>

                                <div class="card-text mt-3">
                                    <p><u>Description :</u></p> 
                                    Cette image représente Dora ainsi que son meilleur ami Babouche. Ces deux tourtereaux ne peuvent se séparer.
                                </div>
                            </div>
                            <ul class="list-group list-group-flush">
                                <li class="list-group-item">README</li>
                                <li class="list-group-item">Note : <strong>20/20</strong></li>
                            </ul>
                            <div class="card-body">
                                <div><a href="#" class="card-link">Télécharger le projet</a></div>
                                <div><a href="#" class="card-link">Dépôt Git</a></div>
                            </div>

                            <!-- Actions de l'admin -->
                            <div class="card-body">
                                <button type="button" class="btn btn-primary">Edit</button>
                                <button type="button" class="btn btn-danger">Delete</button>       
                            </div>
                        </div>


                        <!------------------------------------------------------------------------->

                        <div class="card border-dark">
                            
                            <!-- Images -->
                            <div id="carouselExampleControls1" class="carousel slide" data-ride="carousel">
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
                                <a class="carousel-control-prev" href="#carouselExampleControls1" role="button" data-slide="prev">
                                    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                                    <span class="sr-only">Previous</span>
                                </a>
                                <a class="carousel-control-next" href="#carouselExampleControls1" role="button" data-slide="next">
                                    <span class="carousel-control-next-icon" aria-hidden="true"></span>
                                    <span class="sr-only">Next</span>
                                </a>
                            </div>  
                            
                            <div class="card-body">
                                <h5 class="card-title text-center"><strong>Dora & Babouche</strong></h5>
                                
                                <ul class="list-group ">
                                    <li class="list-group-item">UE : <strong>Dessins animés</strong></li>
                                    <li class="list-group-item">Année : <strong>2020</strong></li>
                                </ul>

                                <div class="card-text mt-3">
                                    <p><u>Description :</u></p> 
                                    Cette image représente Dora ainsi que son meilleur ami Babouche. Ces deux tourtereaux ne peuvent se séparer.
                                </div>
                            </div>

                            <ul class="list-group list-group-flush">
                                <li class="list-group-item">README</li>
                                <li class="list-group-item">Note : <strong>20/20</strong></li>
                            </ul>
                            <div class="card-body">
                                <div><a href="#" class="card-link">Télécharger le projet</a></div>
                                <div><a href="#" class="card-link">Dépôt Git</a></div>
                            </div>

                            <!-- Actions de l'admin -->
                            <div class="card-body">
                                <button type="button" class="btn btn-primary">Edit</button>
                                <button type="button" class="btn btn-danger">Delete</button>       
                            </div>
                        </div>

                        <!------------------------------------------------------------------------->

                        <div class="card border-dark">
                            <!-- Images -->
                            <div id="carouselExampleControls2" class="carousel slide" data-ride="carousel">
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
                                <a class="carousel-control-prev" href="#carouselExampleControls2" role="button" data-slide="prev">
                                    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                                    <span class="sr-only">Previous</span>
                                </a>
                                <a class="carousel-control-next" href="#carouselExampleControls2" role="button" data-slide="next">
                                    <span class="carousel-control-next-icon" aria-hidden="true"></span>
                                    <span class="sr-only">Next</span>
                                </a>
                            </div>  
                            
                            <div class="card-body">
                                <h5 class="card-title text-center"><strong>Dora & Babouche</strong></h5>
                                
                                <ul class="list-group ">
                                    <li class="list-group-item">UE : <strong>Dessins animés</strong></li>
                                    <li class="list-group-item">Année : <strong>2020</strong></li>
                                </ul>

                                <div class="card-text mt-3">
                                    <p><u>Description :</u></p> 
                                    Cette image représente Dora ainsi que son meilleur ami Babouche. Ces deux tourtereaux ne peuvent se séparer.
                                </div>
                            </div>
                            <ul class="list-group list-group-flush">
                                <li class="list-group-item">README</li>
                                <li class="list-group-item">Note : <strong>20/20</strong></li>
                            </ul>
                            <div class="card-body">
                                <div><a href="#" class="card-link">Télécharger le projet</a></div>
                                <div><a href="#" class="card-link">Dépôt Git</a></div>
                            </div>

                            <!-- Actions de l'admin -->
                            <div class="card-body">
                                <button type="button" class="btn btn-primary">Edit</button>
                                <button type="button" class="btn btn-danger">Delete</button>       
                            </div>
                        </div>
                        
                        
                    
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
