#include "mdtat.h"

// return 1 if current frame is 
// 1) a reference frame or 
// 2) a correlation frame
int CheckFrame(int frame)
{
    int mode = 0;

    if ((frame % nfreq == 0) && (frame / nfreq < nref))
        mode = 1;
    
    for (int i = 0; i < nref; ++i)
    {
        for (int j = 0; j < nrepeat; ++j)
            if (frame == i * nfreq + t_corr[j]) mode = 1;
    }

    return mode;
}