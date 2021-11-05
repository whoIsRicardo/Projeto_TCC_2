#include <iostream>
#include <cmath>
#include "eigen-master/Eigen/Dense"
#include <time.h>
using namespace Eigen;

typedef struct rede// Structure that store the optical network variables
{
    double** H, **B, **G;
    double* g_t, * Ltx_i, * F, *u, *p_out;
    double a_star,alfa,Gamp,Pn,Pmax,Pmin;
    double Vmax, Vmin,SNR_target, Rc, Rb, q, sigma_cc2;
    int K,M;
}REDE;



#include "aloca/aloca.c"
#include "CalculaH/CalculaH.c"
#include "rede.c"
#include "gravarTxt/gravarTxt.c"


using namespace std;

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

void calculaB(REDE* rede)
{
    int i,j;
    for(i = 0; i < rede->K; i ++)
    {
        for(j = 0; j < rede->K; j ++)
        {
            if(i ==  j)
            {
                rede->B[i][j] = 0.00;
            }
            else
            {
                rede->B[i][j] = 1.5259*pow(10,-5);
            }
        }
    }
}

void gravarEigenValues(REDE* rede, VectorXd eivals)
{

    FILE *pArq;
    if((pArq = fopen("C:/Users/Ricardo/Desktop/teste/test.txt", "wb")) == 0x0)
    {
        cout << "erro." << endl;
        exit(1);
    }

    for(int i = 0; i < rede->K ; i ++)
    {
        fprintf(pArq, "%f\n",eivals(i));
    }

    if(fclose(pArq))
    {
        cout << "erro." << endl;
        exit(1);
    }

}
int main()
{
    int i,j;
    REDE* rede = allocaREDE();
    calculaRede(rede);
    calculaG(rede);
    calcula_u(rede);
    calculaB(rede);
    double B[32][32];
    double soma = 0.00;
    clock_t tempo;
    for(i = 0; i < rede->K; i ++)
    {
        for(j = 0; j < rede->K; j ++)
        {
            B[i][j] = rede->B[i][j];
        }
    }
    Eigen::Map<Matrix<double,32,32,RowMajor> > mat(B[0]);

    VectorXcd eivals = mat.eigenvalues();
    cout <<"teste" << endl;

    for(int i = 0; i < 32; i ++)
    {
        if(abs(eivals(i))>= 1.00)
        {
            exit(0);
        }
    }

    for(int i  = 0; i < mat.rows(); i ++)
    {
        for(int j = 0; j < mat.cols(); j ++)
        {
            if(i == j)
            {
                mat(i,j) = 1 - mat(i,j);
            }
            else
            {
                mat(i,j) = 0 - mat(i,j);
            }
        }
    }
    tempo = clock();
    mat = mat.inverse();
    for(int i = 0; i < mat.rows(); i ++)
    {
        soma = 0.00;
        for(j = 0; j < mat.cols(); j ++)
        {
            soma += mat(i,j)* rede->u[j];
        }
        rede->p_out[i] = soma;
    }
    printf("Tempo:%e\n ",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    cout << "resultado" << endl;

    for(int i = 0; i < rede->K; i ++)
    {
        cout << rede->p_out[i]  << endl;
    }
    gravar_pOut(rede);
    return 0;
}
