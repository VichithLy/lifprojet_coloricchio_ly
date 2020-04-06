<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateProjetTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('projet', function (Blueprint $table) {
            $table->bigIncrements('projet_id');
            $table->foreignId('ue_id');
            $table->string('nom');
            $table->string('lien_image'); // on met en base le lien de l'image enregistrée dans nos dossiers
            $table->text('readme');
            $table->binary('zip');
            $table->string('lien_github');
            $table->longText('description');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('projet');
    }
}
