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
                            Pré-requis des projet à upload : 
                            <ul>
                                <li>Dossier au format .zip ou .rar</li>
                                <li>Un titre de dossier explicite (nom projet et noms étudiant)</li>
                                <li>Des images au format .png ou .jpg ou .jpeg</li>
                                <li>Un fichier README au format .txt ou .md</li>
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

                    <table class="table">

                        <thead>
                            <tr>
                                <th scope="col" >#</th>
                                <th scope="col">Title</th>
                                <th scope="col">Year</th>       
                                <th scope="col">UE</th>
                                <th scope="col">Description</th>
                                <th scope="col">README</th>
                                <th scope="col">Mark</th>
                                <th scope="col">Zip</th>
                                <th scope="col">Git</th>
                                <th scope="col">Path</th>
                                <th scope="col">Created at</th>
                                <th scope="col">Action</th>
                            </tr>
                        </thead>
                        
                        <tbody>
                            @foreach ($projects as $project)
                                <tr>
                                    <th scope="row">{{ $project->id }}</th>
                                    <td>{{ $project->title }}</td>
                                    <td>{{ $project->year }}</td>                                
                                    <td>{{ implode(', ', $project->ues()->pluck('name')->toArray()) }}</td>
                                    <td>{{ $project->description }}</td>
                                    <td>{{ $project->readme }}</td>
                                    <td>{{ $project->mark }}/20</td>
                                    <td>{{ $project->zip }}</td>
                                    <td>{{ $project->git }}</td>
                                    <td>{{ $project->path }}</td>
                                    <td>{{ $project->created_at }}</td>
                                    <td>
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
                                    </td>                    
                                </tr>
                        @endforeach
                        </tbody>

                    </table>

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
