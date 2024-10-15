#include "mdtat.h"

#include <math.h>

void ReadLine(char *str);
void PrintPara();

void ReadInput(int argc, char **argv)
{
    char fn_in[256] = "TAT.in";
    char *buff;

    fn_dump = (char *)malloc(256 * sizeof(char));
    fn_msd = (char *)malloc(256 * sizeof(char));
    fn_sisf = (char *)malloc(256 * sizeof(char));
    buff = (char *)malloc(Maxlength * sizeof(char));

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-in") == 0)
        {
            strcpy(fn_in, argv[i + 1]);
            break;
        }
    }

    FILE *fp = fopen(fn_in, "r");
    if (fp == NULL)
        ErrorExit("Error: Can not open input file\n");

    while (1)
    {
        fgets(buff, 1024, fp);

        if (feof(fp))
            break;
        if (buff[0] == ' ' || buff[0] == '#' || buff[0] == '\n')
            continue;
        
        ReadLine(buff);
    }

    #ifdef DEBUG
        PrintPara();
    #endif

    return;
}

void ReadLine(char *str)
{
    char *token;

    token = __strtok_r(str, " \t\n", &str);
    if (strcmp(token, "dumpfile") == 0) strcpy(fn_dump, __strtok_r(NULL, " \t\n", &str));
    else if (strcmp(token, "natom") == 0) natom = atoi(__strtok_r(NULL, " \t\n", &str));
    else if (strcmp(token, "nframe") == 0) nframe = atoi(__strtok_r(NULL, " \t\n", &str));
    else if (strcmp(token, "dt") == 0) dt = atof(__strtok_r(NULL, " \t\n", &str));
    else if (strcmp(token, "nfreq") == 0) nfreq = atoi(__strtok_r(NULL, " \t\n", &str));
    else if (strcmp(token, "nevery") == 0) nevery = atoi(__strtok_r(NULL, " \t\n", &str));
    else if (strcmp(token, "nrepeat") == 0) nrepeat = atoi(__strtok_r(NULL, " \t\n", &str));
    else if (strcmp(token, "msd") == 0) 
    {
        imsd = atoi(__strtok_r(NULL, " \t\n", &str));
        strcpy(fn_msd, __strtok_r(NULL, " \t\n", &str));
    }
    else if (strcmp(token, "sisf") == 0)
    {
        isisf = atoi(__strtok_r(NULL, " \t\n", &str));
        strcpy(fn_sisf, __strtok_r(NULL, " \t\n", &str));
    }
    else if (strcmp(token, "vecq") == 0) vecq = atof(__strtok_r(NULL, " \t\n", &str)) / sqrt(3.);
    else fprintf(stderr, "\nWarning: Invalid parameter '%s'\n", token);

    return;
}

void PrintPara()
{
    fprintf(stdout, "dumpfile   %s\n", fn_dump);
    fprintf(stdout, "natom      %d\n", natom);
    fprintf(stdout, "nframe     %d\n", nframe);
    fprintf(stdout, "dt         %f\n", dt);
    fprintf(stdout, "nfreq      %d\n", nfreq);
    fprintf(stdout, "nevery     %d\n", nevery);
    fprintf(stdout, "nrepeat    %d\n", nrepeat);
    fprintf(stdout, "imsd       %d\n", imsd);
    fprintf(stdout, "msd file   %s\n", fn_msd);
    fprintf(stdout, "isisf      %d\n", isisf);
    fprintf(stdout, "sisf file  %s\n", fn_sisf);
    fprintf(stdout, "vecq       %f\n", vecq);
    fprintf(stdout, "\n");

    return;
}
