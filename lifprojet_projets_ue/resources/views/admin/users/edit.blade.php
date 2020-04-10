@extends('layouts.app')

@section('content')
<div class="container">
    <div class="row justify-content-center">
        <div class="col-md-8">
            <div class="card">
            <div class="card-header">Edit user - <strong>{{ $user->name }}</strong></div>

                <div class="card-body">
                    
                    <a href="{{ route('admin.users.index') }}" class="btn btn-secondary active mb-5" role="button" aria-pressed="true">Back</a>

                    <form action="{{ route('admin.users.update', $user) }}" method="POST">

                        @csrf
                            <!-- Laravel reconnait la méthode PUT pour update -->
                        {{ method_field('PUT') }}

                        <!-- ====== Champs email ====== -->
                        <div class="form-group row">
                            <label for="email" class="col-md-2 col-form-label text-md-right"><strong>Email</strong></label>

                            <div class="col-md-6">
                                <input id="email" type="email" class="form-control @error('email') is-invalid @enderror" name="email" value="{{ $user->email }}" required autocomplete="email" autofocus>

                                @error('email')
                                    <span class="invalid-feedback" role="alert">
                                        <strong>{{ $message }}</strong>
                                    </span>
                                @enderror
                            </div>
                        </div>

                        <!-- ====== Champs nom ====== -->
                        <div class="form-group row">
                            <label for="name" class="col-md-2 col-form-label text-md-right"><strong>Name</strong></label>

                            <div class="col-md-6">
                                <input id="name" type="text" class="form-control @error('name') is-invalid @enderror" name="name" value="{{ $user->name }}" required autofocus>

                                @error('name')
                                    <span class="invalid-feedback" role="alert">
                                        <strong>{{ $message }}</strong>
                                    </span>
                                @enderror
                            </div>
                        </div>

                        <!-- ====== Champs rôles ====== -->

                        <div class="form-group row">
                            <label for="roles" class="col-md-2 col-form-label text-md-right"><strong>Roles</strong></label>

                            <div class="col-md-6">
                                @foreach ($roles as $role)
                                    <div class="form-check">
                                        <input type="checkbox" name="roles[]" value="{{ $role->id }}"
                                        @if($user->roles->pluck('id')->contains($role->id)) checked @endif>
                                        <label>{{ $role->name }}</label>
                                    </div>
                                @endforeach
                            </div>
                        </div>

                        <div class="form-group row">
                            <label for="roles" class="col-md-2 col-form-label text-md-right"><strong>UE</strong></label>

                            <div class="col-md-6">
                                @foreach ($ues as $ue)
                                    <div class="form-check">
                                        <input type="checkbox" name="ues[]" value="{{ $ue->id }}"
                                        @if($user->ues->pluck('id')->contains($ue->id)) checked @endif>
                                        <label>{{ $ue->name }}</label>
                                    </div>
                                @endforeach
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
