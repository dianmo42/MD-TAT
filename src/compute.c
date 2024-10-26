#include "mdtat.h"

#include <omp.h>
#include <math.h>

void Compute_dr(Vector *dr, Atom *atom1, Atom *atom2);

void ComputeMSD(Vector *dr, int t);

void ComputeSISF(Vector *dr, int t);

void ComputeOverlap(Vector *dr, int t);

void Compute(int frame)
{
    int iref = frame / nfreq;
    Vector *dr;
    dr = (Vector *)malloc(natom * sizeof(Vector));

    if ((frame % nfreq == 0) && (iref < nref))
    {
        memcpy(atom_ref[iref], atom_cur, natom * sizeof(Atom));
    }

    for (iref = 0; iref < nref; ++iref)
    {
        for (int i = 0; i < nrepeat; ++i)
        {
            if (frame == iref * nfreq + t_corr[i])
            {
                Compute_dr(dr, atom_ref[iref], atom_cur);
                ComputeMSD(dr, i);
                ComputeSISF(dr, i);
                ComputeOverlap(dr, i);
            }
        }
    }

    return;
}

void Compute_dr(Vector *dr, Atom *atom1, Atom *atom2)
{
    for (int i = 0; i < natom; ++i)
    {
        dr[i].x = atom1[i].r.x - atom2[i].r.x;
        dr[i].y = atom1[i].r.y - atom2[i].r.y;
        dr[i].z = atom1[i].r.z - atom2[i].r.z;

        // periodic boundary condition
        if (dr[i].x > 0.5) --dr[i].x;
        else if (dr[i].x < -0.5) ++dr[i].x;
        if (dr[i].y > 0.5) --dr[i].y;
        else if (dr[i].y < -0.5) ++dr[i].y;
        if (dr[i].z > 0.5) --dr[i].z;
        else if (dr[i].z < -0.5) ++dr[i].z;

        dr[i].x *= box.x;
        dr[i].y *= box.y;
        dr[i].z *= box.z;
    }

    return;
}

void ComputeMSD(Vector *dr, int t)
{
    if (imsd == 0)
        return;

    real dr2_tmp = 0;
    real msd_tmp = 0;
    real ngp_tmp = 0;

    #pragma omp parallel for private(dr2_tmp) reduction(+ : msd_tmp, ngp_tmp)
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

void ComputeSISF(Vector *dr, int t)
{
    if (isisf == 0)
        return;

    real sisf_tmp = 0;

    #pragma omp parallel for reduction(+ : sisf_tmp)
    for (int i = 0; i < natom; ++i)
    {
        sisf_tmp += cos((dr[i].x + dr[i].y + dr[i].z) * vecq);
    }

    sisf_tmp /= natom;
    sisf[t] += sisf_tmp;
    chi4[t] += sisf_tmp * sisf_tmp;

    return;
}

void ComputeOverlap(Vector *dr, int t)
{
    if (ioverlap == 0)
        return;

    real overlap_tmp = 0;
    real dr2_tmp = 0;

    #pragma omp parallel for private(dr2_tmp) reduction(+ : overlap_tmp)
    for (int i = 0; i < natom; ++i)
    {
        dr2_tmp = dr[i].x * dr[i].x + dr[i].y * dr[i].y + dr[i].z * dr[i].z;
        if (dr2_tmp < a0) overlap_tmp += 1;
    }

    overlap_tmp /= natom;
    overlap[t] += overlap_tmp;
    chi4_Q[t] += overlap_tmp * overlap_tmp;

    return;
}
