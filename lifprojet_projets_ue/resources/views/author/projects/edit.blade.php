@extends('layouts.app')

@section('content')
<div class="container">
    <div class="row justify-content-center">
        <div class="col-md-10">
            <div class="card">
            <div class="card-header">Edit project - <strong>{{ $project->title }}</strong></div>

                <div class="card-body">
                    
                    <a href="{{ route('author.projects.index') }}" class="btn btn-secondary active mb-5" role="button" aria-pressed="true">Back</a>

                    <form action="{{ route('author.projects.update', $project) }}" method="POST">
                        @csrf
                            <!-- Laravel reconnait la méthode PUT pour update -->
                        {{ method_field('PUT') }}

                        <!-- ====== Champ titre ====== -->

                        <div class="form-group row">
                            <label for="title" class="col-md-3 col-form-label text-md-right"><strong>Title</strong></label>

                            <div class="col-md-6">
                                <input id="title" type="text" class="form-control @error('title') is-invalid @enderror" name="title" value="{{ $project->title }}" required autofocus>

                                @error('title')
                                    <span class="invalid-feedback" role="alert">
                                        <strong>{{ $message }}</strong>
                                    </span>
                                @enderror
                            </div>
                        </div>

                        <!-- ====== Champ année ====== -->

                        <div class="form-group row">
                            <label for="year" class="col-md-3 col-form-label text-md-right"><strong>Year</strong></label>

                            <div class="col-md-6">
                                <input id="year" type="number" class="form-control" name="year" value="{{ $project->year }}" min="1950" max="{{ date('Y') }}" required autofocus>

                                @error('year')
                                    <p class="help is-invalid">{{ $message }}</p>
                                 @enderror
                            </div>
                        </div>

                        <!-- ====== Champ UE ====== -->

                        <div class="form-group row">
                            <label for="ue" class="col-md-3 col-form-label text-md-right"><strong>UE</strong></label>

                            <div class="col-md-6">
                                <div class="select">
                                    <select name="ue" class="form-control">
                                        @foreach($ues as $ue)
                                            <option value="{{ $ue->id }}">{{ $ue->name }}</option>
                                        @endforeach
                                    </select>
                                </div>
                            </div>
                        </div>
        
    
                        <!-- ====== Champ description ====== -->

                        <div class="form-group row">
                            <label for="description" class="col-md-3 col-form-label text-md-right"><strong>Description</strong></label>

                            <div class="col-md-6">
                                <textarea id="description" class="form-control" name="description" maxlength="499" autofocus rows="3">{{ $project->description }}</textarea>
                                @error('description')
                                    <p class="help is-invalid">{{ $message }}</p>
                                @enderror
                            </div>
                        </div>

                        <!-- ====== Champ année ====== -->
                        <div class="form-group row">
                            <label for="mark" class="col-md-3 col-form-label text-md-right"><strong>Mark</strong></label>

                            <div class="col-md-6">
                                <input id="mark" type="number" class="form-control" name="mark" value="{{ $project->mark }}" min="0" max="20" autofocus>

                                @error('mark')
                                    <p class="help is-invalid">{{ $message }}</p>
                                @enderror
                            </div>
                        </div>

                        <!-- ====== Champ Git ====== -->

                        <div class="form-group row">
                            <label for="git" class="col-md-3 col-form-label text-md-right"><strong>Git repository :</strong></label>
                            
                            <div class="col-md-6">
                                <input id="git" type="text" class="form-control @error('git') is-invalid @enderror" name="git" value="{{ $project->git }}" autofocus>

                                @error('git')
                                    <span class="invalid-feedback" role="alert">
                                        <strong>{{ $message }}</strong>
                                    </span>
                                @enderror
                            </div>
                        </div>

                        <!-- ====== Champ README ====== -->

                        <div class="form-group row">
                            <label for="readme" class="col-md-3 col-form-label text-md-right"><strong>README file path :</strong></label>
                            
                            <div class="col-md-6">
                                Chemin vers le README
                            </div>
                        </div>
                        
                        <!-- ====== Champ Zip ====== -->

                        <div class="form-group row">
                            <label for="zip" class="col-md-3 col-form-label text-md-right"><strong>Zip file path :</strong></label>
                            
                            <div class="col-md-6">
                                Chemin vers le fichier zip
                            </div>
                        </div>               

                        <!-- ====== Champ Path ====== -->

                        <div class="form-group row">
                            <label for="path" class="col-md-3 col-form-label text-md-right"><strong>Project path :</strong></label>
                            
                            <div class="col-md-6">
                                Chemin vers le dossier projet
                            </div>
                        </div>

                        <button type="submit" class="btn btn-primary float-right">
                            Update
                        </button>
                                        
                    </form>
                    
                </div>

            </div>
        </div>
    </div>
</div>
@endsection
