#include <stdio.h>
#include <stdlib.h>



void gravarSNR(PSOAUX* psoaux)
{
    FILE *pArq;
    int i;
    if((pArq = fopen("/home/SNR.bin", "wb")) == 0x0)
    {
        printf("erro.");
        exit(1);
    }

    for(i = 0; i < psoaux->K ; i ++)
    {
        fprintf(pArq, "%f\n",psoaux->SNR[i]);
    }

    if(fclose(pArq))
    {
        printf("erro.");
        exit(1);
    }
}
void gravarP(PSOAUX* psoaux)
{
    FILE *pArq;
    int i,j;
    if((pArq = fopen("/home/P.bin", "wb")) == 0x0)
    {
        printf("erro.");
        exit(1);
    }

    for(i = 0; i < psoaux->K ; i ++)
    {
        for(j = 0; j < psoaux->M; j ++)
        {
            fprintf(pArq, "%e\t",psoaux->P[i][j]);
        }
        fprintf(pArq, "\n");
    }

    if(fclose(pArq))
    {
        printf("erro.");
        exit(1);
    }
}
void gravarjP(PSOAUX* psoaux)
{
    FILE *pArq;
    int i;
    if((pArq = fopen("/home/jPgbest.bin", "wb")) == 0x0)
    {
        printf("erro.");
        exit(1);
    }

    for(i = 0; i < psoaux->iteracoes; i ++)
    {

        fprintf(pArq, "%e\n",psoaux->jP[i]);
    }

    if(fclose(pArq))
    {
        printf("erro.");
        exit(1);
    }
}
void gravarSNIR(PSOAUX* psoaux)
{
    FILE *pArq;
    int i,j;
    if((pArq = fopen("/home/SNIR.bin", "wb")) == 0x0)
    {
        printf("erro.");
        exit(1);
    }

    for(i = 0; i < psoaux->iteracoes ; i ++)
    {
            for(j = 0; j < psoaux->K; j ++)
            {
                fprintf(pArq, "%e\t",psoaux->SNIR[i][j]);
            }
            fprintf(pArq, "\n");
    }

    if(fclose(pArq))
    {
        printf("erro.");
        exit(1);
    }
}
void gravarPgbest(PSOAUX* psoaux)
{
    FILE *pArq;
    int i,j;
    if((pArq = fopen("/home/Pgbest.bin", "wb")) == 0x0)
    {
        printf("erro.");
        exit(1);
    }

    for(i = 0; i < psoaux->iteracoes; i ++)
    {
            for(j = 0; j < psoaux->K ; j ++)
            {
                fprintf(pArq, "%e\t",psoaux->Pgbest[i][j]);
            }
            fprintf(pArq, "\n");
    }

    if(fclose(pArq))
    {
        printf("erro.");
        exit(1);
    }
}

void gravarConstantes(PSOAUX* psoaux)
{
    FILE *pArq;
    int i,j;
    if((pArq = fopen("/home/Constantes.txt", "w")) == 0x0)
    {
        printf("erro.");
        exit(1);
    }
    fprintf(pArq, "%f\t",psoaux->c1);
    fprintf(pArq, "\n");

    fprintf(pArq, "%f\t",psoaux->c2);
    fprintf(pArq, "\n");

    fprintf(pArq, "%f\t",psoaux->Wadp);
    fprintf(pArq, "\n");

    if(fclose(pArq))
    {
        printf("erro.");
        exit(1);
    }
}
void gravarTxt(PSOAUX* psoaux)
{
    gravarjP(psoaux);
    gravarSNIR(psoaux);
    gravarPgbest(psoaux);
    gravarSNR(psoaux);
    gravarConstantes(psoaux);
}
