<?php

use Illuminate\Database\Seeder;
use App\Ue;

class UesTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        Ue::truncate();

        //Liste de tous les UE
        Ue::create(['name' => 'LIFAP1']);
        Ue::create(['name' => 'LIFASR1']);
        Ue::create(['name' => 'LIFASR3']);
        Ue::create(['name' => 'LIFAMI']);
        Ue::create(['name' => 'LIFAP2']);
        Ue::create(['name' => 'LIFASR2']);
        Ue::create(['name' => 'LIFAP3']);
        Ue::create(['name' => 'LIFBDW1']);
        Ue::create(['name' => 'LIFASR4']);
        Ue::create(['name' => 'LIFAP4']);
        Ue::create(['name' => 'LIFAP5']);
        Ue::create(['name' => 'LIFPROLOG']);
        Ue::create(['name' => 'LIFGRAPHIQUE']);
        Ue::create(['name' => 'LIFASR5']);
        Ue::create(['name' => 'LIFIHM']);
        Ue::create(['name' => 'LIFAP6']);
        Ue::create(['name' => 'LIFASR6']);
        Ue::create(['name' => 'LIFBDW2']);
        Ue::create(['name' => 'LIFLC']);
        Ue::create(['name' => 'LIFLF']);
        Ue::create(['name' => 'LIFAP7']);
        Ue::create(['name' => 'LIFPROJET']);
        Ue::create(['name' => 'LIFASR7']);
        Ue::create(['name' => 'LIFAlgoNum/Optim']);
        Ue::create(['name' => 'LIFDATA']);
        Ue::create(['name' => 'LIFSTAGE']);
    }
}
