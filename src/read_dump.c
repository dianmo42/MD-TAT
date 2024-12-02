#include "mdtat.h"

char *Field[] = {"id", "type", "mass", 
                 "xs", "ys", "zs", 
                 "xu", "yu", "zu", 
                 "vx", "vy", "vz", 
                 "fx", "fy", "fz"};

int nfield, nline, ntype = sizeof(Field) / sizeof(char *);

void ReadHeader(gzFile fp);

void ReadAtoms(gzFile fp, int mode);

void ReadDump(gzFile fp, int mode)
{    
    ReadHeader(fp);
    ReadAtoms(fp, mode);
    
    return;
}

// header information in dumpfile
void ReadHeader(gzFile fp)
{
    char *buff, *token;
    buff = (char *)malloc(Maxlength * sizeof(char));    
    token = (char *)malloc(Maxlength * sizeof(char));    

    int timestep = 0;
    real lo_tmp, hi_tmp;
    
    gzgets(fp, buff, Maxlength);
    if (gzeof(fp))
        ErrorExit("Error: End of dumpfile\n");

    gzgets(fp, buff, Maxlength);
    timestep = atoi(buff);

    gzgets(fp, buff, Maxlength);
    gzgets(fp, buff, Maxlength);
    nline = atoi(buff);

    // box information
    gzgets(fp, buff, Maxlength);
    gzgets(fp, buff, Maxlength);
    lo_tmp = atof(strtok(buff, " \t\n"));
    hi_tmp = atof(strtok(NULL, " \t\n"));
    box.x = hi_tmp - lo_tmp;
    box_re.x = 1. / box.x;
    
    gzgets(fp, buff, Maxlength);
    lo_tmp = atof(strtok(buff, " \t\n"));
    hi_tmp = atof(strtok(NULL, " \t\n"));
    box.y = hi_tmp - lo_tmp;
    box_re.y = 1. / box.y;

    gzgets(fp, buff, Maxlength);
    lo_tmp = atof(strtok(buff, " \t\n"));
    hi_tmp = atof(strtok(NULL, " \t\n"));
    box.z = hi_tmp - lo_tmp;
    box_re.z = 1. / box.z;

    // loop all fields in dumpfile
    // field type is saved in fieldtype[], set fieldtype = -1 if not specified
    gzgets(fp, buff, Maxlength);
    token = strtok(buff, " \t\n");
    token = strtok(NULL, " \t\n");
    token = strtok(NULL, " \t\n");
    int j = 0;
    while (token != NULL)
    {
        for (int i = 0; i < ntype; ++i)
        {
            if (strcmp(token, Field[i]) == 0)
            {
                fieldtype[j] = i;
                break;
            }
            fieldtype[j] = -1;
        }

        token = strtok(NULL, " \t\n");
        ++j;
    }
    nfield = j;

    if (fieldtype[0] != 0)
        ErrorExit("Error: The first field must be ID\n");

    return;    
}

// read current frame
// skip all lines if the frame won't be used in further calculation
void ReadAtoms(gzFile fp, int mode)
{
    char *buff, *token;
    buff = (char *)malloc(Maxlength * sizeof(char));    
    token = (char *)malloc(Maxlength * sizeof(char));    
    
    int id = 0;

    for (int line = 0; line < nline; ++line)
    {
        gzgets(fp, buff, Maxlength);
        if (mode == 0)
            continue;

        id = atoi(strtok(buff, " \t")) - 1;
        for (int i = 1; i < nfield; ++i)
        {
            token = strtok(NULL, " \t");
            if (fieldtype[i] == 1) atom_cur[id].type = atoi(token);
            else if (fieldtype[i] == 2) atom_cur[id].mass = atof(token);
            else if (fieldtype[i] == 3) atom_cur[id].r.x = atof(token);
            else if (fieldtype[i] == 4) atom_cur[id].r.y = atof(token);
            else if (fieldtype[i] == 5) atom_cur[id].r.z = atof(token);
            else if (fieldtype[i] == 6) atom_cur[id].r.x = atof(token) * box_re.x;      // scale the coordinates
            else if (fieldtype[i] == 7) atom_cur[id].r.y = atof(token) * box_re.y;
            else if (fieldtype[i] == 8) atom_cur[id].r.z = atof(token) * box_re.z;
            else if (fieldtype[i] == 9) atom_cur[id].v.x = atof(token);
            else if (fieldtype[i] == 10) atom_cur[id].v.y = atof(token);
            else if (fieldtype[i] == 11) atom_cur[id].v.z = atof(token);
            else if (fieldtype[i] == 12) atom_cur[id].f.x = atof(token);
            else if (fieldtype[i] == 13) atom_cur[id].f.y = atof(token);
            else if (fieldtype[i] == 14) atom_cur[id].f.z = atof(token);
        }
    }

    return;
}
