#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
#include "solver.h"
#include "celestialbody.h"
#include "vec3.h"

using namespace std;

void ForwardEuler(int N, int T, double *x, double *vx, double *y, double *vy);
void velocityVerlet(int N, int T, double *x, double *vx, double *y, double *vy, double *ax, double *ay );
void test_E_cons(int N, int T, double *x, double *vx, double *y, double *vy, double *ax, double *ay, string filename);
void write_to_file(int N, int T, double *x, double *vx, double *y, double *vy, double *ax, double *ay, string filename);

int main(int argc, char *argv[])
{

    int MeshPoints = 1e8;
    double TimeFinal = 100;
    int Method = 2; //  0 = VelocityVerlet, 1 = ForwardEuler, 2 = Relativistic solver for Mercury Precession
    int System = 2; //  0 = Solar system, 1 = Earth/Sun/Jupiter, 2 = Mercury Precession

    // Intialize all objects
    double solarMass = 1.9891e30;
    vector<CelestialBody> m_Objects;
    CelestialBody Sun = CelestialBody(1.0,0,0,0,0,0,0);

    if ( System == 0 ){
        CelestialBody Mercury = CelestialBody(1.307e22/solarMass,-3.294363957786441E-01,-2.928799526088138E-01,5.618346324205380E-03,365.25*1.320405892727915E-02, 365.25*-1.952252048338632E-02, 365.25*-2.807294373094382E-03);
        CelestialBody Venus   = CelestialBody(4.867E24/solarMass, 7.243545955158947E-01, -3.278712379892032E-02, -4.242728890559555E-02, 365.25*1.017391327967621E-03, 365.25* 2.010584861519629E-02, 365.25* 2.168289888508737E-04);
        CelestialBody Earth   = CelestialBody(5.972E24/solarMass,9.837576984919719E-01,1.889233809711713E-01,-8.631011464030984E-05,-3.406523137555859E-03*365.25,1.686035619678342E-02*365.25,-1.194254105980157E-06*365.25);
        CelestialBody Mars    = CelestialBody(6.39E23/solarMass, 1.349004548617385E+00, -2.975589233646888E-01, -3.956440841859040E-02, 365.25*3.610034965148588E-03, 365.25* 1.484808760059448E-02, 365.25* 2.224945616221949E-04);
        CelestialBody Jupiter = CelestialBody(1.898E27/solarMass,-2.724865762194714E+00,-4.624789318060123E+00,8.013249787610907E-02,6.411862928919486E-03*365.25,-3.471082490961821E-03*365.25,-1.290147901227175E-04*365.25);
        CelestialBody Saturn  = CelestialBody(5.683E26/solarMass, 1.497082568921199E+00, -9.943470921581483E+00,  1.132983557425057E-01, 365.25*5.209583578051823E-03, 365.25* 8.120803848912152E-04, 365.25*-2.211308505468577E-04);
        CelestialBody Uranus  = CelestialBody(8.681E25/solarMass, 1.719595695177778E+01,  9.965486713193039E+00, -1.857636424997038E-01, 365.25*-2.000761535443054E-03, 365.25* 3.219594226509228E-03, 365.25* 3.795711294500967E-05);
        CelestialBody Neptune = CelestialBody(1.024E26/solarMass, 2.891239407445751E+01, -7.753050308782163E+00, -5.066556247342422E-01, 365.25*7.926104454699854E-04, 365.25* 3.050689379330089E-03, 365.25*-8.139915196891708E-05);
        CelestialBody Pluto   = CelestialBody(1.30900E22/solarMass, 1.161374129179143E+01, -3.157937303069106E+01,  1.979427629835602E-02, 365.25*3.006977217402132E-03, 365.25* 4.205759240708480E-04, 365.25*-9.057561756443009E-04);
        m_Objects.push_back(Sun);
        m_Objects.push_back(Mercury);
        m_Objects.push_back(Venus);
        m_Objects.push_back(Earth);
        m_Objects.push_back(Mars);
        m_Objects.push_back(Jupiter);
        m_Objects.push_back(Saturn);
        m_Objects.push_back(Uranus);
        m_Objects.push_back(Neptune);
        m_Objects.push_back(Pluto);

    }

    //  Three Body Problem
    //  Fixing the z-values to zero in order to make 2D plots
    if ( System == 1){
        CelestialBody Sun_z0 = CelestialBody(1.0,0,0,0,0,0,0);
        CelestialBody Earth_z0   = CelestialBody(5.972E24/solarMass,9.837576984919719E-01,1.889233809711713E-01,0,-3.406523137555859E-03*365.25,1.686035619678342E-02*365.25,-1.194254105980157E-06*365.25);
        CelestialBody Jupiter_z0 = CelestialBody(1.898E27*1000/solarMass,-2.724865762194714E+00,-4.624789318060123E+00,0,6.411862928919486E-03*365.25,-3.471082490961821E-03*365.25,-1.290147901227175E-04*365.25);
        m_Objects.push_back(Sun_z0);
        m_Objects.push_back(Earth_z0);
        m_Objects.push_back(Jupiter_z0);

    }

    //  Perihelion of mercury, system chosen at top, method 2 uses relativistic accelleration
//    if ( System == 2 ){
//        CelestialBody SunRel = CelestialBody(1.0,0,0,0,0,0,0);
//        CelestialBody MercuryRel = CelestialBody(1.307e22/solarMass,0.3075,0,0,0,12.44,0);
//        m_Objects.push_back(SunRel);
//        m_Objects.push_back(MercuryRel);
//    }
//    Solver Solv = Solver( MeshPoints,TimeFinal,m_Objects,Method );
//    Solv.solve();

    //  Regular un-objectoriented code for the first couple assignments including energy conservation

    int N = 1000;
    int T = 1;
    double *x  = new double[N];double *vx = new double[N];
    double *y  = new double[N];double *vy = new double[N];
    double *ax = new double[N];double *ay = new double[N];

    clock_t start,end;
    start = clock();
    ForwardEuler(N, T,x,vx,y,vy);
    end = clock();
    double t_g = (double(end - start)/CLOCKS_PER_SEC)*1000;
    cout << t_g << " milliseconds to run Forward Euler when N = " << N << endl;

    write_to_file(N,T,x,vx,y,vy,ax,ay, "ForwardEuler_data.txt");
    test_E_cons(N,T,x,vx,y,vy,ax,ay, "energy_euler_data.txt");

    start = clock();
    velocityVerlet(N,T,x,vx,y,vy,ax,ay);
    end = clock();
    double t_v = (double(end - start)/CLOCKS_PER_SEC)*1000;
    cout << t_v << " milliseconds to run Velocity Verlet when N = " << N << endl;

    write_to_file(N,T,x,vx,y,vy,ax,ay, "velocityVerlet_data.txt");
    test_E_cons(N,T,x,vx,y,vy,ax,ay, "energy_verlet_data.txt");

    delete[]x;delete[]y;delete[]vx;delete[]vy;delete[]ax;delete[]ay;

    return 0;
}

void test_E_cons(int N, int T, double *x, double *vx, double *y, double *vy, double *ax, double *ay, string filename)
{
    double *K  = new double[N];double *P  = new double[N];
    double *dK = new double[N];double *dP = new double[N];
    double h = T / ( (double) N + 1 );
    for ( int i = 0; i < N; i++ )
    {
        K[i] = (vx[i]*vx[i] + vy[i]*vy[i])/2;               //  Calculates kinetic energy
        P[i] = 4*M_PI*M_PI/sqrt(x[i]*x[i] + y[i]*y[i]);     //  Calculates potential energy
    }

    for ( int i = 1; i < N-1; i++ )
    {
        dK[i] = (K[i+1] - K[i])/h;                        //  Differetiates kinetic energy
        dP[i] = (P[i+1] - P[i])/h;                        //  Differentiates potential energy
    }
    ofstream outfile;
    outfile.open(filename);
    for ( int i = 0; i < N; i++ )
    {
        outfile << setw(20) << setprecision(12) << K[i];
        outfile << setw(20) << setprecision(12) << P[i];
        outfile << setw(20) << setprecision(12) << dK[i];
        outfile << setw(20) << setprecision(12) << dP[i]<< endl;
    }
}
void write_to_file(int N, int T, double *x, double *vx, double *y, double *vy, double *ax, double *ay, string filename)
{
    double h = T / ( (double) N + 1 );
    ofstream outfile;
    outfile.open(filename);
    for (int i = 0; i < N; i++)
    {
        outfile << setw(20) << setprecision(12) << h*i;
        outfile << setw(20) << setprecision(12) << x[i];
        outfile << setw(20) << setprecision(12) << y[i];
        outfile << setw(20) << setprecision(12) << vx[i];
        outfile << setw(20) << setprecision(12) << vy[i]<< endl;
    }
}
void ForwardEuler(int N, int T, double *x, double *vx, double *y, double *vy){

    double GMo = 4*M_PI*M_PI; // = [AU^3/yr^2]
    double h = T / ((double) N + 1 );
    x[0] = 1.0; y[0] = 0.0; vx[0] = 0.0; vy[0] = 2*M_PI;

    for ( int i = 0; i < N; i++ )
    {
        double r  = sqrt(x[i]*x[i] + y[i]*y[i]);
        double GMorrr = GMo/(r*r*r);
        double ax = -GMorrr*x[i];
        double ay = -GMorrr*y[i];

        vx[i+1] = vx[i] + h*ax;
        vy[i+1] = vy[i] + h*ay;
        x[i+1]  = x[i]  + h*vx[i];
        y[i+1]  = y[i]  + h*vy[i];
    }
}
void velocityVerlet(int N, int T, double *x, double *vx, double *y, double *vy, double *ax, double *ay ){

    double GMo = 4*M_PI*M_PI;
    double h = T / ((double) N + 1);
    double hh = h*h;
    double h2 = h/2;
    double hh2 = h*h/2;

    x[0] = 1; y[0] = 0; vx[0] = 0; vy[0] = 2*M_PI;

    double r0 = sqrt(x[0]*x[0] + y[0]*y[0]);
    ax[0] = -GMo/(r0*r0*r0)*x[0]; ay[0] = -GMo/(r0*r0*r0)*y[0];

    for ( int i = 0; i < N; i++)
    {
        double r = sqrt(x[i]*x[i] + y[i]*y[i]);
        double GMorrr = GMo/(r*r*r);

        x[i+1]  = x[i]  + h*vx[i] + hh2*ax[i];
        y[i+1]  = y[i]  + h*vy[i] + hh2*ay[i];

        ax[i+1] = -GMorrr*x[i+1];
        ay[i+1] = -GMorrr*y[i+1];

        vx[i+1] = vx[i] + h2*(ax[i+1] + ax[i]);
        vy[i+1] = vy[i] + h2*(ay[i+1] + ay[i]);
    }
}
