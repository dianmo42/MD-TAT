# MD-TAT: Molecular Dynamics Trajectory Analyzing Tool

Currently available:
- Raidial distribution function (RDF)
- Static structure factor (SSF)
- Mean-squared displacement (MSD) and its non-Gaussian parameter (NGP)
- Self-intermediate scattering function (SISF)
- Four-point dynamic susceptibility

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
