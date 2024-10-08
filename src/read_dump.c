#include "mdtat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {ID, TYPE, MASS, XS, YS, ZS, XU, YU, ZU, VX, VY, VZ, FX, FY, FZ};
char *Field[] = {"id", "type", "mass", "xs", "ys", "zs", "xu", "yu", "zu", "vx", "vy", "vz", "fx", "fy", "fz"};
int field[64] = {0};
int nline, nfield;

void ReadHeader(FILE *fp)
{
    int timestep;
    int nline;
    double lo_tmp, hi_tmp;
    char *buff, *token;
    buff = (char *)malloc(1024 * sizeof(char));

    fgets(buff, 1024, fp);
    fgets(buff, 1024, fp);
    timestep = atoi(buff);
    
    // natom in input file must be greater than or equal to 'NUMBER OF ATOMS' in dumpfile
    fgets(buff, 1024, fp);
    fgets(buff, 1024, fp);
    nline = atoi(buff);
    if (nline > natom)
        ErrorExit("Invalid parameter: natom\n");

    // get box information
    fgets(buff, 1024, fp);
    fscanf(fp, "%lf %lf\n", &lo_tmp, &hi_tmp);
    box.x = hi_tmp - lo_tmp;
    box_re.x = 1. / box.x;
    fscanf(fp, "%lf %lf\n", &lo_tmp, &hi_tmp);
    box.y = hi_tmp - lo_tmp;
    box_re.y = 1. / box.y;
    fscanf(fp, "%lf %lf\n", &lo_tmp, &hi_tmp);
    box.z = hi_tmp - lo_tmp;
    box_re.z = 1. / box.z;

    // check fields in dumpfile
    fgets(buff, 1024, fp);
    for (int i = 0; i < 3; ++i)
        token = __strtok_r(buff, " \t", &buff);
    int j = 0;
    while (token != NULL)
    {
        for (int i = ID; i < FZ; ++i)
        {
            if (strcmp(token, Field[i]) == 0)
            {
                field[j] = i;
                break;
            }
            field[j] = -1;
        }
        ++j;
        token = __strtok_r(buff, " \t\n", &buff);
    }
    nfield = j;

    if (field[0] != 0)
        ErrorExit("Error: The first field must be ID\n");
    
    return;
}

void ReadAtom(FILE *fp)
{
    int id;
    char *buff, *token;
    buff = (char *)malloc(1024 * sizeof(char));

    for (int line = 0; line < nline; ++line)
    {
        fgets(buff, 1024, fp);
        for (int i = 0; i < nfield; ++i)
        {
            token = __strtok_r(buff, " \t\n", &buff);
            
            if (field[i] == 0) id = atoi(token) - 1;
            else if (field[i] == 1) atom_cur[id].type = atoi(token);
            else if (field[i] == 2) atom_cur[id].mass = atof(token);
            else if (field[i] == 3) atom_cur[id].r.x = atof(token);
            else if (field[i] == 4) atom_cur[id].r.y = atof(token);
            else if (field[i] == 5) atom_cur[id].r.z = atof(token);
            else if (field[i] == 6) atom_cur[id].r.x = atof(token) * box_re.x;
            else if (field[i] == 7) atom_cur[id].r.y = atof(token) * box_re.y;
            else if (field[i] == 8) atom_cur[id].r.z = atof(token) * box_re.z;
            else if (field[i] == 9) atom_cur[id].v.x = atof(token);
            else if (field[i] == 10) atom_cur[id].v.y = atof(token);
            else if (field[i] == 11) atom_cur[id].v.z = atof(token);
            else if (field[i] == 12) atom_cur[id].f.x = atof(token);
            else if (field[i] == 13) atom_cur[id].f.y = atof(token);
            else if (field[i] == 14) atom_cur[id].f.z = atof(token);
            else continue;
        }
    }

    return;
}

void ReadDump(FILE *fp, int frame)
{
    ReadHeader(fp);
    ReadAtom(fp);

    if (frame % nfreq == 0)
        memcpy(atom_ref[frame / nfreq], atom_cur, natom * sizeof(Atom));
    
    return;
}
