#include "mdtat.h"

void PrintMSD();

void PrintSISF();

void PrintOverlap();

void Output()
{
    if (imsd)
        PrintMSD();
    if (isisf)
        PrintSISF();
    if (ioverlap)
        PrintOverlap();

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
    
    fprintf(fp, "#  t    SISF    chi4\n");
    for (int t = 0; t < nrepeat; ++t)
    {
        sisf[t] /= nref;
        chi4[t] /= nref;
        chi4[t] -= sisf[t] * sisf[t];

        fprintf(fp, "%.3f  %-10.6g  %-10.6g\n", t_corr[t] * dt, sisf[t], natom * chi4[t]);
    }
    fclose(fp);

    return;
}

void PrintOverlap()
{
    FILE *fp = fopen(fn_overlap, "w");

    fprintf(fp, "#  t    Overlap\n");
    for (int t = 0; t < nrepeat; ++t)
    {
        overlap[t] /= nref;
        chi4_Q[t] /= nref;
        chi4_Q[t] -= overlap[t] * overlap[t];
        
        fprintf(fp, "%.3f  %-10.6g  %-10.6g\n", t_corr[t] * dt, overlap[t], natom * chi4_Q[t]);
    }
    fclose(fp);

    return;
}
