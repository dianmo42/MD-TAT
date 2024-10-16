// get static structure factor S(q) 
// by performing Fourier transform to radial distribution function g(r)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define real        double
#define Maxlength   1024


int main(int argc, char **argv)
{
    char buff[Maxlength], *token;
    char fn_rdf[256] = "rdf.dat";
    char fn_sq[256] = "sq.dat";
    real *r, *gr, sq, dr;
    real q_min = 1, q_max = 10, dq = 0.01;
    int nline, nq;
    real rho = 1;
    
    // read arguments
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-in") == 0) strcpy(fn_rdf, argv[i + 1]);
        if (strcmp(argv[i], "-out") == 0) strcpy(fn_sq, argv[i + 1]);
        if (strcmp(argv[i], "-q") == 0)
        {
            q_min = atof(argv[i + 1]);
            q_max = atof(argv[i + 2]);
            dq = atof(argv[i + 3]);
        }
    }
    nq = (q_max - q_min) / dq;

    // open files
    FILE *fp_rdf = fopen(fn_rdf, "r");
    if (fp_rdf == NULL)
    {
        fprintf(stderr, "Error: Can not open RDF file\n");
        exit(1);
    }
    FILE *fp_sq = fopen(fn_sq, "w");

    // read header
    for (int i = 0; i < 4; ++i)
        fgets(buff, Maxlength, fp_rdf);
    token = strtok(buff, " \t\n");
    nline = atoi(strtok(NULL, " \t\n"));
    
    r = (real *)malloc(nline * sizeof(real));
    gr = (real *)malloc(nline * sizeof(real));

    // read rdf
    for (int i = 0; i < nline; ++i)
    {
        fgets(buff, Maxlength, fp_rdf);
        token = strtok(buff, " \t\n");
        r[i] = atof(strtok(NULL, " \t\n"));
        gr[i] = atof(strtok(NULL, " \t\n"));
    }
    dr = r[1] - r[0];
    fgets(buff, Maxlength, fp_rdf);
    if (! feof(fp_rdf))
        rho = atof(buff);

    // Fourier transform
    for (real q = q_min; q < q_max; q += dq)
    {
        sq = 0;
        for (int i = 0; i < nline; ++i)
            sq += dr * (gr[i] - 1) * r[i] * sin(q * r[i]) / q;
        
        fprintf(fp_sq, "%f  %f\n", q, 4 * M_PI * rho * sq + 1);
    }

    return 0;
}