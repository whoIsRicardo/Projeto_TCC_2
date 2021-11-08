#include <stdio.h>
#include <stdlib.h>


void speed(PSO* pso)
{
    int i,j;
    double** rand1 = NULL;
    double** rand2 = NULL;
    rand1 = randomica(pso->K,pso->M);
    rand2 = randomica(pso->K,pso->M);
    for(i = 0; i < pso->K; i ++)
    {
        for(j = 0; j < pso->M; j ++)
        {
            pso->v[i][j] = pso->Wadp * pso->v[i][j] + pso->c1 * rand1[i][j]*(pso->Pibest[i][j]
            - pso->P[i][j]) +  pso->c2*rand2[i][j]*(pso->Pgbest[i] - pso->P[i][j]);
        }
    }
    rand1 = libera2DD(rand1,pso->K);
    rand2 = libera2DD(rand2,pso->K);
}
void bestLocal(PSO* pso)
{
    int i,j;
    for(i = 0; i < pso->M; i ++)
    {
        if(pso->jP[i] > pso->jPibest[i])
        {
            for(j = 0; j < pso->K; j ++)
            {
                pso->Pibest[j][i] = pso->P[j][i];
            }
            pso->jPibest[i] = pso->jP[i];
        }
    }
}

void bestGlobal(PSO* pso)
{
    int i;
    double* MaxJ = NULL;
    int * idx = NULL;
    MaxJ = alloca1DD(pso->M);
    idx = alloca1DI(pso->M);
    insertionSort(pso->jP,MaxJ,idx,pso->M);
    if(MaxJ[pso->M - 1] > pso->jPgbest)
    {
        pso->jPgbest = MaxJ[pso->M - 1];
        for(i = 0; i < pso->K; i ++)
        {
            pso->Pgbest[i] = pso->P[i][idx[pso->M - 1]];
        }
    }
    MaxJ = libera1DD(MaxJ);
    idx = libera1DI(idx);
}
void fitness(PSO* pso)
{
    int i,j;
    double** aux1 = alloca2DD(pso->K,pso->M);
    double aux2;
    Fth* aux3 = pso->fth;
    //zeros2DD(aux1,pso->K,pso->M);
    while(aux3 != NULL)
    {
        aux1[aux3->x][aux3->y] = (1.00 - (pso->P[aux3->x][aux3->y] / pso->Pmax));
        aux3 = aux3->prox;
    }
    for(i = 0; i < pso->M; i ++)
    {
        aux2 = 0.00;
        for(j = 0; j < pso->K; j ++)
        {
            aux2 = aux2 + aux1[j][i];
        }
        pso->jP[i] = (1.00 / pso->K) * aux2;
    }
    pso->fth = liberaFth(pso->fth);
    aux1 = libera2DD(aux1,pso->K);
}
void SNIR(PSO* pso)
{
    int i,j,z;
    double aux1;
    for(z = 0; z < pso->M; z ++)
    {
        for(i= 0; i < pso->K; i ++)
        {
            aux1 = 0.00;
            for(j = 0; j < pso->K; j ++)
            {
                aux1 = aux1 + (pso->P[i][z] * pso->G[i][j]);
            }
            pso->SNIR[i][z] = (pso->F[i] * (pso->P[i][z] / (aux1 - pso->P[i][z] + (pso->Pn / pso->Gii[i]))));
        }
    }
}
void speedBounds(PSO* pso)
{
    int i,j;
    for(i = 0; i < pso->K; i ++)
    {
        for(j = 0; j < pso->M; j ++)
        {
            if(pso->v[i][j] > pso->Vmax)
            {
                pso->v[i][j] = pso->Vmax;
            }
            else if(pso->v[i][j] < pso->Vmin)
            {
                pso->v[i][j] = pso->Vmin;
            }
        }
    }
}
void populationUpdate(PSO* pso)
{
    int i,j;
    for(i = 0; i < pso->K; i ++)
    {
        for(j = 0; j < pso->M; j ++)
        {
            pso->P[i][j] += pso->v[i][j];
        }
    }
}
void powerBounds(PSO* pso)
{
    int i,j;
    for(i = 0; i < pso->K; i ++)
    {
        for(j = 0; j < pso->M; j ++)
        {
            if(pso->P[i][j] < pso->Pmin)
            {
                pso->P[i][j] = pso->Pmin;
            }
            if(pso->P[i][j] > pso->Pmax)
            {
                pso->P[i][j] = pso->Pmax;
            }
        }
    }
}

void inserirPSO(PSO* pso, REDE* rede)
{
    /*time_t t;
    srand((unsigned) time(&t));
    pso->c1 = 1.00 + ((double)(rand()))/RAND_MAX;//1.8
    pso->c2 = 1.00 + ((double)(rand()))/RAND_MAX;//2.0
    pso->Wadp = ((double)(rand()))/RAND_MAX;//0.6

    /*
    pso->c1 = 1.930723;
    pso->c2 = 1.193487;
    pso->Wadp = 0.910062;*/

    pso->c1 = 1.526200;
    pso->c2 = 1.732994;
    pso->Wadp = 0.812214;
    pso->K = 32;
    pso->M = 64;
    pso->iteracoes = 1000;
    pso->Pmax = rede->Pmax;
    pso->jPgbest = 0.00;
    pso->SNIR = alloca2DD(pso->K,pso->M);
    pso->P = alloca2DD(pso->K,pso->M);
    pso->G = alloca2DD(pso->K,pso->K);
    pso->fth = NULL;
    pso->v = alloca2DD(pso->K,pso->M);
    pso->Pibest = alloca2DD(pso->K,pso->M);
    pso->Gii = alloca1DD(pso->K);
    pso->F = alloca1DD(pso->K);
    pso->SNR = alloca1DD(pso->K);
    pso->Pgbest = alloca1DD(pso->K);
    pso->jP = alloca1DD(pso->M);
    pso->jPibest = alloca1DD(pso->M);

    pso->Pn = rede->Pn;
    pso->Pmax = rede->Pmax;
    pso->Pmin = rede->Pmin;
    pso->Vmax = rede->Vmax;
    pso->Vmin = rede->Vmin;
    pso->Gii = rede->g_t;
    pso->F = rede->F;

}
