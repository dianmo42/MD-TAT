#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxData     10000000

int main(int argc, char **argv)
{
    int T, ifile, nfile, ndata;
    char fn[256];
    double *t, *sisf, *chi4;
    double t_tmp, sisf_tmp, chi4_tmp;
    t = (double *)malloc(MaxData * sizeof(double));
    sisf = (double *)malloc(MaxData * sizeof(double));
    chi4 = (double *)malloc(MaxData * sizeof(double));

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
            if (fscanf(fp, "%lf %lf %lf\n", &t_tmp, &sisf_tmp, &chi4_tmp) == EOF)
                break;
            t[i] += t_tmp;
            sisf[i] += sisf_tmp;
            chi4[i] += chi4_tmp;
        }
        ndata = i;
        fclose(fp);
    }

    sprintf(fn, "%dK.dat", T);
    fp = fopen(fn, "w");
    fprintf(fp, "t    SISF    Chi4\n");
    for (int i = 0; i < ndata; ++i)
    {
        fprintf(fp, "%-10.3f    %-16.6g    %-16.6g\n", t[i] / nfile, sisf[i] / nfile, chi4[i] / nfile);
        if (sisf[i] / nfile < 0.001)
            break;
    }
    fclose(fp);

    return 0;
}