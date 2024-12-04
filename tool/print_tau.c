#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int T;
    double e_th = exp(-1);
    double t, e_cur;
    char fn[256];

    for (int iarg = 1; iarg < argc; ++iarg)
    {
        if (strcmp(argv[iarg], "-T") == 0)
            T = atoi(argv[iarg + 1]);
    }
    sprintf(fn, "%dK.dat", T);
    FILE *fp = fopen(fn, "r");

    fscanf(fp, "%*[^\n]\n");
    while (fscanf(fp, "%lf %lf %*lf\n", &t, &e_cur) != EOF)
    {
        if (e_cur < e_th)
            break;
    }
    fclose(fp);

    fprintf(stdout, "%-10.3d    %-16.6g\n", T, t);

    return 0;
}