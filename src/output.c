#include "mdtat.h"

void PrintMSD();

void PrintSISF();

void Output()
{
    if (imsd)
        PrintMSD();
    if (isisf)
        PrintSISF();

    return;
}

void PrintMSD()
{
    FILE *fp = fopen(fn_msd, "w");
    
    fprintf(fp, "#  t    MSD    NGP\n");
    for (int t = 0; t < nrepeat; ++t)
    {
        msd[t] /= nref;
        ngp[t] /= nref;

        fprintf(fp, "%.3f  %-10.6g  %-10.6g\n", t_corr[t] * dt, msd[t], ngp[t]);
    }
    fclose(fp);

    return;
}

void PrintSISF()
{
    FILE *fp = fopen(fn_sisf, "w");
    
    fprintf(fp, "#  t    SISF    Xhi4\n");
    for (int t = 0; t < nrepeat; ++t)
    {
        sisf[t] /= nref;
        ngp[t] /= nref;
        ngp[t] -= sisf[t] * sisf[t];

        fprintf(fp, "%.3f  %-10.6g  %-10.6g\n", t_corr[t] * dt, sisf[t], xhi4[t]);
    }
    fclose(fp);

    return;
}