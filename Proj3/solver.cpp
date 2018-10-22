//  ODE systems solver uses Forward Euler ( m = 0 ) or Velocity Verlet ( m = 1 )

#include "solver.h"

Solver::Solver(int N, double T_F, vector<CelestialBody> objects, int m)
{
    MeshPoints = N;
    TimeFinal = T_F;
    m_Objects = objects;
    Method = m;
}

void Solver::solve()
{
    double h = TimeFinal/double(MeshPoints);        //  Timestep h
    double h_Sq = h*h;                              //  Timestep squared
    double h_Half = h/2;                            //  Timestep halfed
    double h_SqHalf = h_Sq/2;                       //  Timestep squared halfed

    //  Temporary accelleration values
    double ax; double ay; double az; double axNew; double ayNew; double azNew;

    //  File for writing
    string filename;
    if (this->Method == 1) {
        filename = "ForwardEulerData_Class.txt";
    } else if (this->Method == 0) {
        filename = "VelocityVerletData_Class.txt";
    } else {
        filename = "MercuryData.txt";
    }

    ofstream outfile;
    outfile.open (filename);

    //  Integration loop
    if (this->Method == 0)
    {
        //  VelocityVerlet integration loop here
        for (int i = 0; i < MeshPoints; i++)
        {
            for (int obj = 0; obj < m_Objects.size(); obj++)
            {
                ax = ay = az = axNew = ayNew = azNew = 0;                    //  Initial accelleration values are all equal to zero
                for (unsigned int obj2 = 0; obj2 < m_Objects.size(); obj2++)
                {
                    ax += m_Objects[obj].accelleration(m_Objects[obj2],0);
                    ay += m_Objects[obj].accelleration(m_Objects[obj2],1);
                    az += m_Objects[obj].accelleration(m_Objects[obj2],2);
                }
                outfile << setw(30) << setprecision(15) << m_Objects[obj].position[0];
                outfile << setw(30) << setprecision(15) << m_Objects[obj].position[1];
                outfile << setw(30) << setprecision(15) << m_Objects[obj].position[2];

                //x[i+1]  = x[i]  + h*vx[i] + h*h/2*ax[i]; in three dimensions
                m_Objects[obj].position[0] = m_Objects[obj].position[0] + h*m_Objects[obj].velocity[0] + ax*h_SqHalf;
                m_Objects[obj].position[1] = m_Objects[obj].position[1] + h*m_Objects[obj].velocity[1] + ay*h_SqHalf;
                m_Objects[obj].position[2] = m_Objects[obj].position[2] + h*m_Objects[obj].velocity[2] + az*h_SqHalf;

                //a[i+1] = -GMo/(r*r*r)*x[i+1];
                for (int obj2 = 0; obj2 < m_Objects.size(); obj2++){
                    axNew += m_Objects[obj].accelleration(m_Objects[obj2],0);
                    ayNew += m_Objects[obj].accelleration(m_Objects[obj2],1);
                    azNew += m_Objects[obj].accelleration(m_Objects[obj2],2);
                }

                //vx[i+1] = vx[i] + h/2*(ax[i+1] + ax[i]);
                m_Objects[obj].velocity[0] = m_Objects[obj].velocity[0] + h_Half*(axNew + ax);
                m_Objects[obj].velocity[1] = m_Objects[obj].velocity[1] + h_Half*(ayNew + ay);
                m_Objects[obj].velocity[2] = m_Objects[obj].velocity[2] + h_Half*(azNew + az);
            }
            outfile << endl;
            //  Fixin the sun in origo for three body problem
//            m_Objects[0].position[0] = 0;
//            m_Objects[0].position[1] = 0;
//            m_Objects[0].position[2] = 0;
        }
        outfile.close();

    } else if (this->Method == 1){
        //  ForwardEuler here
        for (int i = 0; i < MeshPoints; i++) {
            for (int obj = 0; obj < m_Objects.size(); obj++) {
                ax = ay = az = 0;

                for (int obj2 = 0; obj2 < m_Objects.size(); obj2++){
                    ax += m_Objects[obj].accelleration(m_Objects[obj2],0);
                    ay += m_Objects[obj].accelleration(m_Objects[obj2],1);
                    az += m_Objects[obj].accelleration(m_Objects[obj2],2);
                }

                m_Objects[obj].velocity[0] = m_Objects[obj].velocity[0] + h*ax;
                m_Objects[obj].velocity[1] = m_Objects[obj].velocity[1] + h*ay;
                m_Objects[obj].velocity[2] = m_Objects[obj].velocity[2] + az;

                m_Objects[obj].position[0] = m_Objects[obj].position[0] + h*m_Objects[obj].velocity[0];
                m_Objects[obj].position[1] = m_Objects[obj].position[1] + h*m_Objects[obj].velocity[1];
                m_Objects[obj].position[2] = m_Objects[obj].position[2] + h*m_Objects[obj].velocity[2];

                // Storing position
                outfile << setw(30) << setprecision(15) << m_Objects[obj].position[0];
                outfile << setw(30) << setprecision(15) << m_Objects[obj].position[1];
                outfile << setw(30) << setprecision(15) << m_Objects[obj].position[2];
            }
            outfile << endl;
        }

        outfile.close();

    } else if (this->Method == 2) {
        //  Relativistic method begin here

        double r = 0; double rNew = 0; double rOld = 0; double precession = 0;


        for ( int i = 0; i < MeshPoints; i++ ){

            r = m_Objects[1].distance(m_Objects[0]);
            precession = m_Objects[1].PerihelionPrecession();

            ax = ay = az = axNew = ayNew = azNew = 0;

            for ( CelestialBody &other : m_Objects ){
                ax += m_Objects[1].accellerationRel(other, 0);
                ay += m_Objects[1].accellerationRel(other, 1);
                az += m_Objects[1].accellerationRel(other, 2);
            } // End of forloop accelleration

            m_Objects[1].position[0] = m_Objects[1].position[0] + h*m_Objects[1].velocity[0] + ax*h_SqHalf;
            m_Objects[1].position[1] = m_Objects[1].position[1] + h*m_Objects[1].velocity[1] + ay*h_SqHalf;
            m_Objects[1].position[2] = m_Objects[1].position[2] + h*m_Objects[1].velocity[2] + az*h_SqHalf;

            for ( CelestialBody &other : m_Objects ){
                axNew += m_Objects[1].accellerationRel(other, 0);
                ayNew += m_Objects[1].accellerationRel(other, 1);
                azNew += m_Objects[1].accellerationRel(other, 2);
            } // End of forloop new accelleration


            m_Objects[1].velocity[0] = m_Objects[1].velocity[0] + h_Half*( axNew + ax );
            m_Objects[1].velocity[1] = m_Objects[1].velocity[1] + h_Half*( ayNew + ay );
            m_Objects[1].velocity[2] = m_Objects[1].velocity[2] + h_Half*( azNew + az );

            rNew = m_Objects[1].distance(m_Objects[0]);

            if ( r < rNew && r < rOld){
                outfile << setw(30) << setprecision(15) << i*h;
                outfile << setw(30) << setprecision(15) << precession << endl;
            } // End of if-test

            rOld = r;
        } // End of big for-loop

    } // End of Method 2 (relativistic)
} // End of solver
