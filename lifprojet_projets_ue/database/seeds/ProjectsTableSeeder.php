<?php

use Illuminate\Database\Seeder;
use App\Project;
use App\Ue;

class ProjectsTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        Project::truncate();
        DB::table('ue_project')->truncate();

        $projectUe1 = Ue::where('name', 'LIFAP1')->first();
        $projectUe2 = Ue::where('name', 'LIFASR1')->first();
        $projectUe3 = Ue::where('name', 'LIFASR3')->first();

        $project1 = Project::create([
            'title' => 'Projet 1',
            'year' => '2018',
            'description' => 'Numquam amicitia ut ordinis quaedam esse tamquam parem Saepe Maximum nostro Scipionis Saepe ita parem amicitia dicam ut posse is Numquam nequaquam dicam numquam ampliores anteposuit esse numquam colebat sunt.',
            'readme' => 'Lien readme Projet 1',
            'zip' => 'Lien zip Projet 1',
            'git' => 'Lien git Projet 1',
            'path' => 'Chemin dossier Projet 1'
        ]);

        $project2 = Project::create([
            'title' => 'Projet 2',
            'year' => '2019',
            'description' => 'Sunt qui etiam Sunt in opere putant putant ii contemni ut sunt se se modo putant ii hac quod non fere superiores non non superiores rem ut in putant modo.',
            'readme' => 'Lien readme Projet 2',
            'zip' => 'Lien zip Projet 2',
            'git' => 'Lien git Projet 2',
            'path' => 'Chemin dossier Projet 2'
        ]);

        $project2 = Project::create([
            'title' => 'Projet 3',
            'year' => '2020',
            'description' => 'Caritas autem amicitiae ipsa adducta adducta ex ipsa quod hoc maxime iungeretur sit societate generis adducta natura omnis et ex generis sit et contracta ipsa ut conciliavit ex vis in.',
            'readme' => 'Lien readme Projet 3',
            'zip' => 'Lien zip Projet 3',
            'git' => 'Lien git Projet 3',
            'path' => 'Chemin dossier Projet 3'
        ]);

        $project1->ues()->attach($projectUe1);
        $project2->ues()->attach($projectUe2);
        $project2->ues()->attach($projectUe3);

    }
}
