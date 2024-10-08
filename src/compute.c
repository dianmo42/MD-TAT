#include "mdtat.h"

#include <omp.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

Vec *dr;

void UpdateDr(int t0, int t)
{
    ALLOC_MEM(dr, natom, Vec);
    Vec dr_tmp;

    #pragma omp parallel for firstprivate(t0, box)
    for (int i = 0; i < natom; ++i)
    {
        dr[i].x = atom_cur[i].r.x - atom_ref[t0][i].r.x;
        dr[i].y = atom_cur[i].r.y - atom_ref[t0][i].r.y;
        dr[i].z = atom_cur[i].r.z - atom_ref[t0][i].r.z;

        // periodic boundary condition
        if (dr[i].x > 0.5)
            --dr[i].x;
        else if (dr[i].x < -0.5)
            ++dr[i].x;
        if (dr[i].y > 0.5)
            --dr[i].y;
        else if (dr[i].y < -0.5)
            ++dr[i].y;
        if (dr[i].z > 0.5)
            --dr[i].z;
        else if (dr[i].z < -0.5)
            ++dr[i].z;

        dr[i].x *= box.x;
        dr[i].y *= box.y;
        dr[i].z *= box.z;
    }

    return;
}

void ComputeMSD(int t)
{
    if (imsd == 0)
        return;
    
    real dr2_tmp = 0;
    real msd_tmp = 0;
    real ngp_tmp = 0;
    
    #pragma omp parallel for reduction(+ : msd_tmp, ngp_tmp)
    for (int i = 0; i < natom; ++i)
    {
        dr2_tmp = dr[i].x * dr[i].x + dr[i].y * dr[i].y + dr[i].z * dr[i].z;
        msd_tmp += dr2_tmp;
        ngp_tmp += dr2_tmp * dr2_tmp;
    }

    msd_tmp /= natom;
    ngp_tmp /= natom;
    msd[t] += msd_tmp;
    ngp[t] += ngp_tmp / ((1 + 2. / DIMENSION) * (msd_tmp * msd_tmp)) - 1;

    return;
}

void ComputeSISF(int t)
{
    if (isisf == 0)
        return;
    
    real sisf_tmp = 0;

    #pragma omp parallel for reduction(+: sisf_tmp)
    for (int i = 0; i < natom; ++i)
    {
        sisf_tmp += cos((dr[i].x + dr[i].y + dr[i].z) * vecq);
    }

    sisf_tmp /= natom;
    sisf[t] += sisf_tmp;
    xhi4[t] += sisf_tmp * sisf_tmp;

    return;
}

void Compute(int frame)
{
    if (frame == 0)
        return;

    int nref = frame / nfreq;
    for (int t0 = 0; t0 < nref; ++t0)
    {
        for (int t = 0; t < nrepeat; ++t)
        {
            if (frame != t0 + t * nevery)
                continue;
            UpdateDr(t0, t);
            ComputeMSD(t);
            ComputeSISF(t);
        }
    }

    return;
}