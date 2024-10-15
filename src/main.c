#include "mdtat.h"

int main(int argc, char **argv)
{
    ReadInput(argc, argv);
    Initial();

    FILE *fp = fopen(fn_dump, "r");
    if (fp == NULL)
        ErrorExit("Error: Can not open dumpfile\n");

    for (int i = 0; i < nframe + 1; ++i)
    {
        ReadDump(fp, CheckFrame(i));
        Compute(i);
    }

    Output();

    return 0;
}
