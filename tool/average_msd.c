#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxData     10000000

int main(int argc, char **argv)
{
    int T, ifile, nfile, ndata;
    char fn[256];
    double *t, *msd, *ngp;
    double t_tmp, msd_tmp, ngp_tmp;
    t = (double *)malloc(MaxData * sizeof(double));
    msd = (double *)malloc(MaxData * sizeof(double));
    ngp = (double *)malloc(MaxData * sizeof(double));

    for (int iarg = 1; iarg < argc; ++iarg)
    {
        if (strcmp(argv[iarg], "-T") == 0)
            T = atoi(argv[iarg + 1]);
        if (strcmp(argv[iarg], "-n") == 0)
            nfile = atoi(argv[iarg + 1]);
    }
    
    FILE *fp = NULL;
    for (ifile = 0; ifile < nfile; ++ifile)
    {
        sprintf(fn, "./raw_data/%dK-%d.dat", T, ifile + 1);
        fp = fopen(fn, "r");
        
        fscanf(fp, "%*[^\n]\n");
        int i;
        for (i = 0; i < MaxData; ++i)
        {
            if (fscanf(fp, "%lf %lf %lf\n", &t_tmp, &msd_tmp, &ngp_tmp) == EOF)
                break;
            t[i] += t_tmp;
            msd[i] += msd_tmp;
            ngp[i] += ngp_tmp;
        }
        ndata = i;
        fclose(fp);
    }

    sprintf(fn, "%dK.dat", T);
    fp = fopen(fn, "w");
    fprintf(fp, "t    MSD    NGP\n");
    for (int i = 0; i < ndata; ++i)
    {
        fprintf(fp, "%-10.3f    %-16.6g    %-16.6g\n", t[i] / nfile, msd[i] / nfile, ngp[i] / nfile);
        if (msd[i] / nfile > 100)
            break;
    }
    fclose(fp);

    return 0;
}