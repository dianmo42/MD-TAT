#include "mdtat.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    ReadInput(argc, argv);
    AllocMem();
    
    FILE *fp_dump = fopen(fn_dump, "r");
    if (fp_dump == NULL)
        ErrorExit("Error opening dumpfile\n");
    
    for (int i = 0; i < nframe; ++i)
    {
        ReadDump(fp_dump, i);
        Compute(i);
    }

    Output();

    return 0;
}