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
        DB::table('project_ue')->truncate();

        $projectUe1 = Ue::where('name', 'LIFAP1')->first();
        $projectUe2 = Ue::where('name', 'LIFASR1')->first();
        $projectUe3 = Ue::where('name', 'LIFASR3')->first();

        $project1 = Project::create([
            'name' => 'Projet 1',
            'title' => 'Projet 1',
            'year' => 2018,
            'description' => 'Numquam amicitia ut ordinis quaedam esse tamquam parem Saepe Maximum nostro Scipionis Saepe ita parem amicitia dicam ut posse is Numquam nequaquam dicam numquam ampliores anteposuit esse numquam colebat sunt.',
            'readme' => 'Lien readme Projet 1',
            'mark' => 10,
            'zip' => 'Lien zip Projet 1',
            'git' => 'Lien git Projet 1',
            'path' => 'Chemin dossier Projet 1',
        ]);

        $project2 = Project::create([
            'name' => 'Projet 2',
            'title' => 'Projet 2',
            'year' => 2019,
            'description' => 'Sunt qui etiam Sunt in opere putant putant ii contemni ut sunt se se modo putant ii hac quod non fere superiores non non superiores rem ut in putant modo.',
            'readme' => 'Lien readme Projet 2',
            'mark' => 15,
            'zip' => 'Lien zip Projet 2',
            'git' => 'Lien git Projet 2',
            'path' => 'Chemin dossier Projet 2'
        ]);

        $project3 = Project::create([
            'name' => 'Projet 3',
            'title' => 'Projet 3',
            'year' => 2020,
            'description' => 'Caritas autem amicitiae ipsa adducta adducta ex ipsa quod hoc maxime iungeretur sit societate generis adducta natura omnis et ex generis sit et contracta ipsa ut conciliavit ex vis in.',
            'readme' => 'Lien readme Projet 3',
            'mark' => 20,
            'zip' => 'Lien zip Projet 3',
            'git' => 'Lien git Projet 3',
            'path' => 'Chemin dossier Projet 3'
        ]);

        $project4 = Project::create([
            'name' => 'Projet 4',
            'title' => 'Projet 4',
            'year' => 2018,
            'description' => 'Description projet 4',
            'readme' => 'Lien readme Projet 4',
            'mark' => 16,
            'zip' => 'Lien zip Projet 4',
            'git' => 'Lien git Projet 4',
            'path' => 'Chemin dossier Projet 4'
        ]);

        $project5 = Project::create([
            'name' => 'Projet 5',
            'title' => 'Projet 5',
            'year' => 2017,
            'description' => 'Description projet 5',
            'readme' => 'Lien readme Projet 5',
            'mark' => 17,
            'zip' => 'Lien zip Projet 5',
            'git' => 'Lien git Projet 5',
            'path' => 'Chemin dossier Projet 5'
        ]);

        $project6 = Project::create([
            'name' => 'Projet 5',
            'title' => 'Projet 6',
            'year' => 2020,
            'description' => 'Description projet 6',
            'readme' => 'Lien readme Projet 6',
            'mark' => 12,
            'zip' => 'Lien zip Projet 6',
            'git' => 'Lien git Projet 6',
            'path' => 'Chemin dossier Projet 6'
        ]);

        $project1->ues()->attach($projectUe1);
        $project2->ues()->attach($projectUe2);
        $project3->ues()->attach($projectUe3);

        $project4->ues()->attach($projectUe1);
        $project5->ues()->attach($projectUe2);
        $project6->ues()->attach($projectUe3);
    }
}
