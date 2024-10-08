#include "mdtat.h"

#include <stdio.h>
#include <stdlib.h>

void AllocMem()
{
    // check parameters
    if (nframe < 1)
        ErrorExit("Error: nframe must be positive\n");
    
    ALLOC_MEM(atom_cur, natom, Atom);
    ALLOC_MEM2(atom_ref, nref, natom, Atom);
    
    if (imsd)
    {
        ALLOC_MEM(msd, nrepeat, real);
        ALLOC_MEM(ngp, nrepeat, real);
    }

    if (isisf)
    {
        ALLOC_MEM(sisf, nrepeat, real);
        ALLOC_MEM(xhi4, nrepeat, real);
    }

    return;
}