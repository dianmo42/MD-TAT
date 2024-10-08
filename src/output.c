#include "mdtat.h"

#include <stdio.h>
#include <stdlib.h>

int nref;

void OutputMSD()
{
    FILE *fp = fopen("msd.dat", "w");

    fprintf(fp, "#    t    MSD    NGP\n");
    for (int t = 0; t < nrepeat; ++t)
    {
        msd[t] /= nref;
        ngp[t] /= nref;
        fprintf(fp, "%lf  %lf  %lf\n", (t + 1) * nevery * dt, msd[t], ngp[t]);
    }
    fclose(fp);

    return;
}

void OutputSISF()
{
    FILE *fp = fopen("sisf.dat", "w");

    fprintf(fp, "#    t    SISF    Xhi4");
    for (int t = 0; t < nrepeat; ++t)
    {
        sisf[t] /= nref;
        xhi4[t] /= nref;
        xhi4[t] -= sisf[t];
        fprintf(fp, "%lf  %lf  %lf\n", (t + 1) * nevery * dt, sisf[t], xhi4[t]);
    }
    fclose(fp);

    return;
}

void Output()
{
    OutputMSD();
    OutputSISF();

    return;
}
