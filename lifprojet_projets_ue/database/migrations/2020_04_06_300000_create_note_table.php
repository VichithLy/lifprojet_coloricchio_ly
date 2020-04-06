<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateNoteTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('note', function (Blueprint $table) {
            $table->bigIncrements('note_id');
            $table->foreignId('eleve_id');
            $table->foreignId('projet_id'); // a voir si 2 foreign key ca marche, sinon utiliser que celle de l'eleve
            $table->float('note_projet',6,3); // note du projet : 6 chiffres maximum, dont 3 apres la virgule
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('note');
    }
}
