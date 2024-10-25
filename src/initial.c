#include "mdtat.h"

#include <math.h>

char *fn_dump;
int natom;
int nframe;
real dt;

int nfreq, nevery, nrepeat, nref;
int *t_corr;
Atom **atom_ref, *atom_cur;
Vector box, box_re;
int *fieldtype;

int imsd;
int isisf;
real vecq;
int ioverlap;
real a0;

real *msd, *ngp;
real *sisf, *xhi4;
real *overlap;

char *fn_msd;
char *fn_sisf;
char *fn_overlap;

void Initial()
{   
    // check parameters
    if (nfreq < 1)
        ErrorExit("Error: nfreq must be positive\n");
    if (nevery < 0)
        ErrorExit("Error: nevery must be 0 or positive\n");
    if (nrepeat < 1)
        ErrorExit("Error: nrepeat must be positive\n");
    if (nframe - nevery * nrepeat < 0)
        ErrorExit("Error: nframe must be greater than nevery * nrepeat\n");
    if (nevery == 0)
        nref = (nframe - nrepeat) / nfreq;
    else
        nref = (nframe - nevery * nrepeat) / nfreq;

    // allocate array for dumpfile
    fieldtype = (int *)malloc(64 * sizeof(int));
    atom_cur = (Atom *)malloc(natom * sizeof(Atom));
    atom_ref = (Atom **)malloc(nref * sizeof(Atom *));
    for (int i = 0; i < nref; ++i)
        atom_ref[i] = (Atom *)malloc(natom * sizeof(Atom));

    // when nevery = 0, set correlation time on logarithmic scale
    // otherwise set correlation time on linear scale
    t_corr = (int *)malloc(nrepeat * sizeof(int));
    if (nevery == 0)
    {
        t_corr[0] = 1;
        int i = 1;
        while (1)
        {
            t_corr[i] = t_corr[i - 1] + pow(10, (int)((i - 1) / 9));
            if (t_corr[i] > nrepeat)
                break;
            ++i;
        }
        nrepeat = i;
    }
    else
    {
        for (int i = 0; i < nrepeat; ++i)
            t_corr[i] = (i + 1) * nevery;
    }

    // allocate array for correlation functions
    if (imsd)
    {
        msd = (real *)malloc(nrepeat * sizeof(real));
        ngp = (real *)malloc(nrepeat * sizeof(real));
    }
    if (isisf)
    {
        sisf = (real *)malloc(nrepeat * sizeof(real));
        xhi4 = (real *)malloc(nrepeat * sizeof(real));
    }
    if (ioverlap)
    {
        overlap = (real *)malloc(nrepeat * sizeof(real));
    }

    return;
}

void ErrorExit(char *ErrMsg)
{
    fprintf(stderr, "\033[31;1m\n%s\033[0m\n", ErrMsg);
    exit(1);
}
