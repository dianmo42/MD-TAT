#ifndef _MDTAT_H
#define _MDTAT_H

#include <stdio.h>

#define real    double
#define DIMENSION   3

// struct
typedef struct Vector
{
    real x;
    real y;
    real z;
} Vec;

typedef struct AtomInfo
{
    int id;
    int type;
    real mass;
    Vec r;
    Vec v;
    Vec f;
} Atom;

// variable
extern char *fn_dump;
extern int nframe;
extern int natom;
extern real dt;

extern int irdf;
extern real rcut;
extern int imsd;
extern int isisf;
extern real vecq;

extern int nfreq, nevery, nrepeat, nref;
extern Atom **atom_ref, *atom_cur;
extern Vec box, box_re;

extern real *msd, *ngp;
extern real *sisf, *xhi4;

// function
void ReadInput(int argc, char **argv);
void AllocMem();
void ReadDump(FILE *fp, int frame);
void Compute(int frame);
void ErrorExit(char *str);
void Output();


// macro
#define ALLOC_MEM(var, num, type)                       \
            var = (type *)malloc((num) * sizeof(type))
#define ALLOC_MEM2(var, num1, num2, type)               \
            ALLOC_MEM(var, num1, type *);               \
            ALLOC_MEM(var[0], (num1) * (num2), type);   \
            for (int i = 1; i < num1; ++i)              \
                var[i] = var[i - 1] + num2

#endif