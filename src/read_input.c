#include "mdtat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *fn_dump;
int nframe;
int natom;
real dt;

int irdf;
real rcut;
int imsd;
int isisf;
real vecq;

int nfreq, nevery, nrepeat;
Atom **atom_ref, *atom_cur;
Vec box, box_re;

real *msd, *ngp;
real *sisf, *xhi4;

void ReadInput(int argc, char **argv)
{
    FILE *fp_in = NULL;
    char fn_in[256] = "TAT.in";
    char *buff, *token;
    ALLOC_MEM(buff, 1024, char);

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-in") != 0)
            continue;
        strcpy(fn_in, argv[i + 1]);
        break;
    }

    fp_in = fopen(fn_in, "r");
    if (fp_in == NULL)
    {
        perror("Error openning input file");
        exit(1);
    }

    while (1)
    {
        fgets(buff, 1024, fp_in);
        if (feof(fp_in))
            break;
        if (buff[0] == '#' || buff[0] == '\n')
            continue;
        
        fprintf(stdout, "%s", buff);
        token = strtok(buff, " ");
        fprintf(stdout, "%s\n", token);
        if (strcmp(token, "dumpfile") == 0) strcpy(fn_dump, strtok(NULL, " "));
        else if (strcmp(token, "natom") == 0) natom = atoi(strtok(buff, " "));
        else if (strcmp(token, "nframe") == 0) nframe = atoi(strtok(buff, " "));
        else if (strcmp(token, "dt") == 0) dt = atof(strtok(buff, " "));
        else if (strcmp(token, "irdf") == 0) irdf = atoi(strtok(buff, " "));
        else if (strcmp(token, "rcut") == 0) rcut = atof(strtok(buff, " "));
        else if (strcmp(token, "imsd") == 0) imsd = atoi(strtok(buff, " "));
        else if (strcmp(token, "isisf") == 0) isisf = atoi(strtok(buff, " "));
        else if (strcmp(token, "vecq") == 0) vecq = atof(strtok(buff, " ")) / 3.;
        else if (strcmp(token, "nfreq") == 0) nfreq = atoi(strtok(buff, " "));
        else if (strcmp(token, "nevery") == 0) nevery = atoi(strtok(buff, " "));
        else if (strcmp(token, "nrepeat") == 0) nrepeat = atoi(strtok(buff, " "));
        else fprintf(stderr, "Warning: Invalid input arg '%s'\n", token);
    }

    nref = (nframe - nevery * nrepeat) / nfreq;
    if (nref < 1)
        ErrorExit("Error: nframe must be greater than nevery * nrepeat\n");

    // #ifdef DEBUG
    fprintf(stdout, "dumpfile: %s\n", fn_dump);
    fprintf(stdout, "natom: %d\n", natom);
    fprintf(stdout, "nframe: %d\n", nframe);
    fprintf(stdout, "dt: %lf\n", dt);
    fprintf(stdout, "irdf: %d\n", irdf);
    fprintf(stdout, "rcut: %lf\n", rcut);
    fprintf(stdout, "imsd: %d\n", imsd);
    fprintf(stdout, "isisf: %d\n", isisf);
    fprintf(stdout, "vecq: %lf\n", vecq);
    fprintf(stdout, "nfreq: %d\n", nfreq);
    fprintf(stdout, "nevery: %d\n", nevery);
    fprintf(stdout, "nrepeat: %d\n", nrepeat);
    exit(1);
    // #endif
    return;
}
