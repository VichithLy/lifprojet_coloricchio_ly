#include <Grapic.h>
#include <time.h>
using namespace grapic;

const int DIMWX = 900;
const int DIMWY = 600;
const int SizePop = 1000;
const float DistConta = 25;
const float Virulence = 50;
const int NbSim = 5;

//Vecteur 2D
struct Vec2
{
    float x, y;
};

Vec2 make_Vec2(float x, float y)
{
    Vec2 res;
    res.x = x;
    res.y = y;
    return res;
}

Vec2 operator+ (Vec2 A, Vec2 B)
{
    Vec2 res;
    res.x = A.x + B.x;
    res.y = A.y + B.y;
    return res;
}


float distance(Vec2 A, Vec2 B)
{
    float res;
    res = sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
    return res;
}


//Individual
struct Individual
{
    Vec2 pos;
    char health;
};

Individual initialisation (Vec2 pos, char health)
{
    Individual id;
    id.pos = pos;
    id.health = health;
    return id;
}

void drawIdividual (Individual id)
{
    if(id.health == 'V')
    {
        color(0, 204, 0);         //Green
    }

    if(id.health =='N')
    {
        color(51, 51, 255);         //Blue
    }

    if(id.health == 'S')
    {
        color(204, 0, 0);         //Red
    }
    circleFill(id.pos.x, id.pos.y, 4);
}

//Population
struct Population
{
    Individual pop[SizePop];
};

void populationInit(Population & pop, float vaccination, Vec2 posSim, int dimSim)
{
    int i, x, y;
    Individual id;
    char health;
    Vec2 pos = posSim + make_Vec2(dimSim/2, dimSim/2);

    pop.pop[0] = initialisation(pos, 'S');       //patient 0

    for(i = 1; i < SizePop; i++)
    {
        if(rand()%100 < vaccination) {health = 'V';}
        else {health = 'N';}
        x = rand()%100*(dimSim)/100 + posSim.x;
        y = rand()%100*(dimSim)/100 + posSim.y;
        pos = make_Vec2(x, y);
        id = initialisation(pos, health);
        pop.pop[i] = id;
    }
}

void drawPop(Population pop)
{
    int i;
    for (i=0; i<SizePop; ++i)
    {
        drawIdividual(pop.pop[i]);
    }
}


//Simulation
struct Simulation
{
    int dim;
    Vec2 pos;
    Population pop;
    float vaccination;
    int s;
};

void simulationInit(Simulation & sim, int dim, Vec2 pos, float vaccination)
{
    sim.dim = dim;
    sim.pos = pos;
    sim.vaccination = vaccination;
    sim.s = 1;
    populationInit(sim.pop , sim.vaccination, sim.pos, sim.dim);
}

void drawSimulation(Simulation sim, int n)
{
    //Draw the dots
    drawPop(sim.pop);
    //Display sim info
    color(255,255,255);
    rectangleFill(sim.pos.x, sim.pos.y, sim.pos.x+60, sim.pos.y+15);
    color(0,0,0);
    print(sim.pos.x+2, sim.pos.y+2, int(sim.vaccination));
    if(n==0)
    {
        color(29,238,224);
    }
    if(n==1)
    {
        color(0,255,0);
    }
    if(n==2)
    {
        color(0,0,255);
    }
    if(n==3)
    {
        color(255,255,59);
    }
    if(n==4)
    {
        color(255,59,255);
    }
    line(sim.pos.x+20, sim.pos.y+7, sim.pos.x+50, sim.pos.y+7);
}

void updateSimulation(Simulation& sim, Plot& p, int n)
{
    int i, j;

    for(i=0; i<SizePop; ++i)
    {
        if(sim.pop.pop[i].health == 'S')
        {
            for(j=0; j<SizePop; ++j)
            {
                float d;
                d = distance(sim.pop.pop[i].pos, sim.pop.pop[j].pos);
                if(d < DistConta && sim.pop.pop[j].health == 'N' && rand()%100 < Virulence * (1 - d / DistConta))
                {
                    sim.pop.pop[j].health = 'S';
                    ++sim.s;
                }
            }
        }
    }
    plot_add(p, elapsedTime(), sim.s, n);
}

struct World
{
    Simulation sim[NbSim];
    Plot plot;
};

int main(int , char** )
{
    srand (time(NULL));
    bool stop=false;
	winInit("Démo Immunité de troupeau", DIMWX, DIMWY);
	backgroundColor( 255, 255, 255 );

	int t=0;

	Simulation sim1;
	Simulation sim2;
	Simulation sim3;
	Simulation sim4;
	Simulation sim5;
	simulationInit(sim1, DIMWY/2, make_Vec2(0, DIMWY/2), 0);
	simulationInit(sim2, DIMWY/2, make_Vec2(0, 0), 25);
	simulationInit(sim3, DIMWY/2, make_Vec2(DIMWX/3,DIMWY/2), 50);
	simulationInit(sim4, DIMWY/2, make_Vec2(DIMWX/3, 0), 75);
	simulationInit(sim5, DIMWY/2, make_Vec2(2*DIMWX/3,DIMWY/2), 95);

	World w;
	w.sim[0]=sim1;
	w.sim[1]=sim2;
	w.sim[2]=sim3;
	w.sim[3]=sim4;
	w.sim[4]=sim5;

	Plot p;
	plot_clear(p);
	plot_setSize(p, -1);
	w.plot = p;


	while( !stop )
    {
        winClear();

        drawSimulation(w.sim[0], 0);
        drawSimulation(w.sim[1], 1);
        drawSimulation(w.sim[2], 2);
        drawSimulation(w.sim[3], 3);
        drawSimulation(w.sim[4], 4);
        color(0,0,0);
        grid(0, 0, DIMWX-1, DIMWY-1, 3, 2);

        plot_draw(w.plot, 2*DIMWX/3+1, 0, DIMWX, DIMWY/2-1);
        color(0,0,0);
        print(DIMWX-250, 0, "Nombres de personnes infectees vs temps");

        if(t%50 == 0)
        {
            updateSimulation(w.sim[0], w.plot, 0);
            updateSimulation(w.sim[1], w.plot, 1);
            updateSimulation(w.sim[2], w.plot, 2);
            updateSimulation(w.sim[3], w.plot, 3);
            updateSimulation(w.sim[4], w.plot, 4);
        }

        t++;
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

