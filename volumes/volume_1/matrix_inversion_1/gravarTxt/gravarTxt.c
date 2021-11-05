#include <stdio.h>
#include <stdlib.h>


void gravar_pOut(REDE* rede)
{

    FILE *pArq;
    if((pArq = fopen("/home/p1_out.txt", "wb")) == 0x0)
    {
        printf("erro.\n");
        exit(1);
    }

    for(int i = 0; i < rede->K ; i ++)
    {
        fprintf(pArq, "%e\n",rede->p_out[i]);
    }

    if(fclose(pArq))
    {
        printf("erro.\n");
        exit(1);
    }

}















