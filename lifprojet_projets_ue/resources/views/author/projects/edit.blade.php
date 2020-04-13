<!-- Script permettant de rendre visible ou invisible les attributs -->

<script type="text/javascript">

function verifMark ()
{   
    var checkbox_mark = document.getElementById('checkbox_mark');

    // On vérifie l'état du checkbox (coché ou non)
    if (!checkbox_mark.checked)
    {   
        document.getElementById('mark').type = 'hidden';
        
    }
    else {
        document.getElementById('mark').type = 'text';
    }

}

function verifDescription ()
{
    var checkbox_description = document.getElementById('checkbox_description');

    // On vérifie l'état du checkbox (coché ou non)
    if (!checkbox_description.checked)
    {   
        document.getElementById('description').style = 'display:none';
        
    }
    else {
        document.getElementById('description').style = 'display:block';
    }
}

function verifGit() 
{
    var checkbox_git = document.getElementById('checkbox_git');

    // On vérifie l'état du checkbox (coché ou non)
    if (!checkbox_git.checked)
{   
    document.getElementById('git').type = 'hidden';
    
}
else {
    document.getElementById('git').type = 'text';
}

}

function verifReadme() 
{
    var checkbox_readme = document.getElementById('checkbox_readme');

    // On vérifie l'état du checkbox (coché ou non)
    if (!checkbox_readme.checked)
{   
    document.getElementById('readme').style = 'display:none';
    
}
    else 
{
        document.getElementById('readme').style = 'display:block';
}


}
</script>


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
                                            @if ( $ue->id  == $project->ues()->pluck('ue_id')->first() )
                                                <option value="{{ $ue->id }}" selected>{{ $ue->name }}</option>
                                            @else
                                                <option value="{{ $ue->id }}">{{ $ue->name }}</option>
                                            @endif       
                                        @endforeach
                                    </select>
                                </div>
                            </div>
                        </div>
        
    
                        <!-- ====== Champ description ====== -->

                        <div class="form-group row">
                            <input type="checkbox" id="checkbox_description" checked onChange="verifDescription();">
                            <label for="description" class="col-md-3 col-form-label text-md-right"><strong>Comment</strong></label>

                            <div class="col-md-6">
                                <textarea id="description" class="form-control" name="description" maxlength="499" autofocus rows="3">{{ $project->description }}</textarea>
                                @error('description')
                                    <p class="help is-invalid">{{ $message }}</p>
                                @enderror
                            </div>
                        </div>

                        <!-- ====== Champ Note ====== -->
                        <div class="form-group row">
                            <input type="checkbox" id="checkbox_mark" checked onChange="verifMark();">
                            <label for="mark" class="col-md-3 col-form-label text-md-right"><strong>Mark</strong></label>

                            <div class="col-md-6">
                                <input id="mark" type="number" class="form-control" name="mark" value="{{ $project->mark }}" min="0" max="20" step=".1" autofocus>

                                @error('mark')
                                    <p class="help is-invalid">{{ $message }}</p>
                                @enderror
                            </div>
                        </div>

                        <!-- ====== Champ Git ====== -->

                        <div class="form-group row">
                            <input type="checkbox" id="checkbox_git" checked onChange="verifGit();">
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
                            <input type="checkbox" id="checkbox_readme" checked onChange="verifReadme();">
                            <label for="readme" class="col-md-3 col-form-label text-md-right"><strong>README file path :</strong></label>
                            
                            <div id="readme" class="col-md-6">
                                {{ $project->readme }}
                            </div>
                        </div>
                        
                        <!-- ====== Champ Zip ====== -->

                        <div class="form-group row">
                            <label for="zip" class="col-md-3 col-form-label text-md-right"><strong>Zip file path :</strong></label>
                            
                            <div class="col-md-6">
                                {{ '/' . $project->zip }}
                            </div>
                        </div>               

                        <!-- ====== Champ Path ====== -->

                        <div class="form-group row">
                            <label for="path" class="col-md-3 col-form-label text-md-right"><strong>Project path :</strong></label>
                            
                            <div class="col-md-6">
                                {{ '/uploads/projects/' . $project->name }}
                            </div>
                        </div>

                        <h6>Lorsque les cases sont décochées, les attributs ne seront pas affichés dans la liste des projets</h6>

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
