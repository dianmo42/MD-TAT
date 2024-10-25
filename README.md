# MD-TAT: Molecular Dynamics Trajectory Analyzing Tool

Currently available:
- Raidial distribution function $g(r)$
- Static structure factor $S(q)$
- Mean-squared displacement $\Delta^2(t)$ and its non-Gaussian parameter $\alpha_2(t)$
- Self-intermediate scattering function $F_s(q,t)$
- Four-point dynamic susceptibility $\chi_4(t)$

Will be added:
- Overlap function

## Build
Clone the repository to your workspace and build from source code
```
    git clone git@github.com:dianmo42/MD-TAT.git MD-TAT
    cd MD-TAT/src
    make
```

## Run
Modify the input parameters within the file `TAT.in`, or create your own version, and specify the input file with command
```
    ./TAT -in <input_file>
```
