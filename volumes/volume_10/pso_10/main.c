#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Fth// Dynamic list where the position of the SNIR is bigger than the SNIR target is stored.
{
    int x,y;
    struct Fth* prox;
}Fth;


typedef struct rede// Structure that store the optical network variables
{
    double** H, **B, **G;
    double* g_t, * Ltx_i, * F, *u;
    double a_star,alfa,Gamp,Pn,Pmax,Pmin;
    double Vmax, Vmin,SNR_target, Rc, Rb, q, sigma_cc2;
    int K,M;
}REDE;
typedef struct pso// Structure that store dynamically the PSO algorithm variables.
{
    double** SNIR,** P, ** G, ** v, ** Pibest;
    double *Gii, * F, * jP, *Pgbest, * jPibest,*SNR;
    double Pn,Pmax, Pmin,jPgbest,c1,c2,Wadp,Vmin,Vmax;
    Fth* fth;
    int K, M,iteracoes;
}PSO;
typedef struct psoaux// This structure is utilized to store the PSO algorithm variables in each round.
{
    double Wadp,c1,c2;
    double** SNIR,** P, ** G,** Fth, ** v, ** Pibest, **Pgbest;
    double *Gii, * F, * jP, * jPibest,*SNR;
    int K,iteracoes,M;

}PSOAUX;
// This files are created separatelly, but belongs to the same folder.
#include "aloca/aloca.c"//This file contains the functions responsible for allocating the memory dynamically.
#include "InsertionSort/InsertSort.c"// This file contains the function InsertionSort, that is, ordenation by insertion.
#include "Randomica/randomica.c"// This file constains a function responsible for generate a matrix which contains numbers randomically generated.
#include "imprimir.c"// This file contains the functions responsible for shown the results in the prompt window.
#include "CalculaH/CalculaH.c"// This file contains the function responsible for generate the normalized matrix H of interference.
#include "CalculaF/CalculaF.c"// This file contais the function responsible for calculate the quocient of the bit rate by the chip rate.
#include "rede.c"// This file contains all the attributes related to the passive optical network, all the datas are generated mathematically.
#include "pso.c"// This file contains the functions related to the pso algorithm.
#include "CalculaP/CalculaP.c"// This file contains the function responsible for generate the surface of research of the pso algorithm.
#include "CalculaFth/CalculaFth.c"// This file contains the function responsible for providing guindace to the particle swarm of the algorithm.
#include "CalculaPibest/calculaPibest.c"// This file contains the function responsible for, initially, generate the best local positions, as a matrix.
#include "CalculaPgbest/CalculaPgbest.c"// This file contains the function responsible for, initially, generate the best global positions.
//#include "CalculaG/CalculaG.c"// This file contains the function responsible for calculating the gains of the star coupler.
#include "calculajPibest/calculajPibest.c"// This file contains the function responsible for, initially, generate the best local positions, as a vector.
#include "CalculaVelocidade/calculaVelocidade.c"// This file contains the function responsible for calculate the velocity of the particles.
#include "CalculaSNR/calculaSNR.c"// This file contains the function responsible for calculate the SNR, which will be evaluate as a final result.
#include "calculaSNIR_aux/calculaSNIR_aux.c"// This file contains the function responsible for store the path followed by the SNIR of each userof the network.
#include "calculaPgbest_aux/calculaPgbest_aux.c"// This file contains the function responsible for store the global positions of the particles along the path.
#include "calculaPSOAUX/calculaPSOAUX.c"// This file contains some functions which are twins of the functions belong to the original file of the PSO.
#include "gravarTxt/gravarTxt.c"// This file contains the functions responsible for storing all the datas generated during the simulation, in a txt file.


void calculaG(REDE* rede)
{
    int i,j;
    for(i = 0; i < rede->K; i ++)
    {
        for(j = 0; j < rede->K; j ++)
        {
                rede->G[i][j] = 1.00;
        }
    }
}
void calcula_u(REDE* rede)
{
    int i;
    for(i = 0; i < rede->K; i ++)
    {
        rede->u[i] = rede->Pn * ((1.5259*pow(10,-5))/rede->g_t[i]);
    }
}

int main()
{
    int i,j;
    REDE* rede = allocaREDE();
    calculaRede(rede);
    calculaG(rede);
    calcula_u(rede);
    /*double data[2][2];
    Eigen::Map<Matrix<double,2,2,RowMajor> > mat(data[0]);
    mat = mat.inverse();*/
    for(i =0; i < rede->K; i ++)
    {
        for(j = 0; j < rede->K; j ++)
        {
                printf("%f ",rede->G[i][j]);
        }
        printf("\n");
    }

    return 0;
}
