#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int T, ifile, nfile, nline;
    char fn[256], buff[1024];
    double rho = 0, rho_tmp;
    double *r, *rdf;
    double r_tmp, rdf_tmp;

    for (int iarg = 1; iarg < argc; ++iarg)
    {
        if (strcmp(argv[iarg], "-T") == 0)
            T = atoi(argv[iarg + 1]);
        if (strcmp(argv[iarg], "-n") == 0)
            nfile = atoi(argv[iarg + 1]);
        if (strcmp(argv[iarg], "-l") == 0)
            nline = atoi(argv[iarg + 1]);
    }

    r = (double *)malloc(nline * sizeof(double));
    rdf = (double *)malloc(nline * sizeof(double));
    
    FILE *fp = NULL;
    for (ifile = 0; ifile < nfile; ++ifile)
    {
        sprintf(fn, "./raw_data/%dK-%d.dat", T, ifile + 1);
        fp = fopen(fn, "r");
        
        for (int i = 0; i < 4; ++i) fscanf(fp, "%*[^\n]\n");
        for (int i = 0; i < nline; ++i)
        {
            fscanf(fp, "%*d %lf %lf\n", &r_tmp, &rdf_tmp);
            r[i] += r_tmp;
            rdf[i] += rdf_tmp;
        }
        fscanf(fp, "%lf\n", &rho_tmp);
        rho += rho_tmp;
        fclose(fp);
    }

    sprintf(fn, "%dK.dat", T);
    fp = fopen(fn, "w");
    fprintf(fp, "rho = %-16.6f\n", rho / nfile);
    for (int i = 0; i < nline; ++i)
        fprintf(fp, "%-10.3f    %-16.6g\n", r[i] / nfile, rdf[i] / nfile);
    fclose(fp);

    return 0;
}