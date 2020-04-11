@extends('layouts.app')

@section('content')
    <div class="row justify-content-center">
        <div class="col-md-12">


            <div class="card">
                
                <div class="card-header">Projects management</div>

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
                                    <option>LIFAP6</option>
                                    <option>LIFPROJET</option>                         
                                </select>
                            </div>

                            <div class="input-group-prepend mb-2">
                                <span class="input-group-text rounded" id="inputGroup-sizing-sm">Année</span>
                            </div>
                            <div class="mr-sm-5">
                                <select class="form-control form-control-sm">
                                    <option>Aucune</option>
                                    <option>2020</option>
                                    <option>2019</option>
                                    <option>2018</option>                  
                                </select>
                            </div>

                        </div>

                        <div class="custom-file mb-5">
                            <input type="file" class="custom-file-input" id="customFile">
                            <label class="custom-file-label" for="customFile">Upload a project</label>
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
                                                <form action="{{ route('author.projects.destroy', $project) }}" method="POST">
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


                    </nav>

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
