#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calculaRede(REDE* rede)
{
    int i;
    rede->Gamp = 100.00;
    rede->alfa = 0.0461;
    rede->a_star = 0.0016;
    rede->K = 32;
    rede->M = 64;
    rede->Pmax = 0.0100;
    rede->Pmin = 1.0 * pow(10,-10);
    rede->Vmax = 0.0020;
    rede->Vmin = - 0.0020;
    rede->SNR_target = 1.5259 * pow(10,-5);
    rede->sigma_cc2 = 0.01;
    rede->q = 256.00;

    rede->Rc = 1.00;
    rede->Rb = 1.00;
    rede->Pn = 2.00 * (rede->Gamp - 1.0) * 193.0 * pow(10,12) * 100.0* pow(10,9) * 6.63 * pow(10,-34);
    rede->g_t = alloca1DD(rede->K);
    rede->Ltx_i = alloca1DD(rede->K);
    rede->p_out = alloca1DD(rede->K);
    rede->F = alloca1DD(rede->K);
    rede->u = alloca1DD(rede->K);
    rede->H = alloca2DD(rede->K,rede->K);
    rede->B = alloca2DD(rede->K,rede->K);
    rede->G = alloca2DD(rede->K,rede->K);

     rede->Ltx_i[0] = 50.0000;
    rede->Ltx_i[1] = 50.0000;
    rede->Ltx_i[2] = 50.0000;
    rede->Ltx_i[3] = 50.0000;
    rede->Ltx_i[4] = 50.0000;
    rede->Ltx_i[5] = 50.0000;
    rede->Ltx_i[6] = 50.0000;
    rede->Ltx_i[7] = 50.0000;
    rede->Ltx_i[8] = 50.0000;
    rede->Ltx_i[9] = 50.0000;
    rede->Ltx_i[10] = 50.0000;
    rede->Ltx_i[11] = 50.0000;
    rede->Ltx_i[12] = 50.0000;
    rede->Ltx_i[13] = 50.0000;
    rede->Ltx_i[14] = 50.0000;
    rede->Ltx_i[15] = 50.0000;
    rede->Ltx_i[16] = 50.0000;
    rede->Ltx_i[17] = 50.0000;
    rede->Ltx_i[18] = 50.0000;
    rede->Ltx_i[19] = 50.0000;
    rede->Ltx_i[20] = 50.0000;
    rede->Ltx_i[21] = 50.0000;
    rede->Ltx_i[22] = 50.0000;
    rede->Ltx_i[23] = 50.0000;
    rede->Ltx_i[24] = 50.0000;
    rede->Ltx_i[25] = 50.0000;
    rede->Ltx_i[26] = 50.0000;
    rede->Ltx_i[27] = 50.0000;
    rede->Ltx_i[28] = 50.0000;
    rede->Ltx_i[29] = 50.0000;
    rede->Ltx_i[30] = 50.0000;
    rede->Ltx_i[31] = 50.0000;
    for(i = 0; i < rede->K; i ++)
    {
        rede->g_t[i] = rede->a_star * pow(2.7183,-rede->alfa * rede->Ltx_i[i]) * rede->Gamp * 0.0025;
    }
    calculaH(rede);
}
