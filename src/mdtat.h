#ifndef MDTAT_H
#define MDTAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define real float
#define DIMENSION 3
#define Maxlength 1024

// struct
typedef struct VECTOR
{
    real x;
    real y;
    real z;
} Vector;

typedef struct ATOM
{
    int id;
    int type;
    real mass;
    Vector r;
    Vector v;
    Vector f;
} Atom;

// variable
extern char *fn_dump;
extern int natom;
extern int nframe;
extern real dt;

extern int nfreq, nevery, nrepeat, nref;
extern int *t_corr;
extern Atom **atom_ref, *atom_cur;
extern Vector box, box_re;
extern int *fieldtype;

extern int imsd;
extern int isisf;
extern real vecq;

extern real *msd, *ngp;
extern real *sisf, *xhi4;

extern char *fn_msd;
extern char *fn_sisf;

// function
void ReadInput(int argc, char **argv);
void Initial();
void ErrorExit(char *ErrMsg);
int CheckFrame(int frame);
void ReadDump(FILE *fp, int mode);
void Compute(int frame);
void Output();

#endif