<?php

namespace App\Http\Requests;

use Illuminate\Foundation\Http\FormRequest;

class ProjectsRequest extends FormRequest
{
    /**
     * Determine if the user is authorized to make this request.
     *
     * @return bool
     */
    public function authorize()
    {
        return true;
    }

    /**
     * Get the validation rules that apply to the request.
     *
     * @return array
     */
    public function rules()
    {
        return [
            'title' => 'bail|required|string|max:254',
            'year' => 'bail|required|integer|min:1950',
            'description' => 'max:499',
            'mark' => 'min:0|max:20',
            'git' => 'max:254'
        ];
    }
}
