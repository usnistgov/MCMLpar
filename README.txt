MCMLpar: Parallelized Monte Carlo: Multi Layer
Version 1.0
4 August 2017


Written by:	
Richelle Streater, Colorado School of Mines, NIST SURF Student
Anne-Michelle Lieberson, Sherwood High School, NIST SHIP Student
Adam Pintar, National Institute of Standards and Technology, Gaithersburg, Maryland
Zachary Levine, National Institute of Standards and Technology, Gaithersburg, Maryland
	
Experimental data provided by Catherine Cooksey and Paul Lemaillet 

To display in vim:
:set linebreak


I. Overview

A. Program details

Language: C++ (0x and beyond)/OpenMP, Mathematica for Post-Processing (optional)
Contact details: zlevine@nist.gov
Companion program: MCSLinv [1, 2]. MCSLinv is a program which solves for the scattering parameters, mua and mus, of a single layer.
Compilers used:
  Windows: mingw32-g++ with compiler flags: -O3 -fopenmp -std=c++0x
  Linux: g++ version 4.4.7 20120313 (Red Hat 4.4.7-18) (GCC) with compiler flags -O3 -std=c++0x -fopenmp -DSPRNGFIVE

B. Summary:

MCMLpar is a parallelized version of MCML [3]. Like MCML, MCMLpar uses a Monte Carlo simulation to model photon propagation within a multi-layer optical sample. While MCML assumes an infinite detector radius around the optical sample, MCMLpar calculates photon paths given a finite radius by taking distance from the photon entry point into account. Unlike MCML, MCMLpar does not create two photons at a boundary and does not store the internal photon distribution in the sample. 


II. Directions for use:

A. Variables and units:

The only unit is an inverse length. While we prefer to enter the thickness in millimeters and get the scattering parameters in inverse millimeters, if the user chooses, e.g., to enter the length unit in centimeters, the scattering parameters will be output in inverse centimeters.

n- index of refraction
g- Henyey-Greenstein anisotropy parameter
t- thickness (mm)
mua- inverse interaction length for absorption
mus- inverse interaction length for scattering
mut- inverse interaction length for either absorption or scattering (total)

B. Input files:

1. input.txt: This file contains all user-defined parameter inputs. The
simulation inputs are number of particles (i.e., photons), number of ARS points, number of
processors, and radius of detector. For an infinite radius approximation, or if
the detector radius is unknown, set radius to some large value (such as 10000000).
The user may need to change number of particles to attain more precise or less
precise results. The user should change the number of processors to match those
of the computer.  The user should also specify all material parameters. Copy and paste the layer block of text to add more layers and update the number of layers entry.

2. inputExample.txt: This is an example input. With this input, the program should run for 10-60 seconds and should output the data in MCMLparOutputExampleS2.csv or MCMLparOutputExampleS5.csv, depending on which version of SPRNG is used.

C. Output files:

1. MCMLparOutput.csv: This file will include time elapsed and the Angle-Resolved Scattering (ARS) data to be graphed by Mathematica. This output will be in central-angle form, which is the typical form for experimental data. Each ARS count is divided by its corresponding solid angle. To convert any data to solid-angle form, collect ARS data for twice as many points as desired. For instance, if a 36-point ARS curve is desired (5 degree angle ranges), collect 72 points of ARS data, so that data is stored between 0 and 2.5 degrees, then 2.5 and 5 degrees, etc. Double the ARS count between 0 and 2.5, then add together consecutive counts in pairs to form the rest of the list. For instance, add together the contents from 2.5 to 5 degrees and from 5 to 7.5 degrees and store the sum as the second element. Then add together the contents from 7.5 to 10 degrees and from 10 to 12.5 degrees and store this sum as the third element. This should result in a total of 36 list elements. The fixARS.cpp function in the source code also will do this.

2. MCMLparOutput.nb: This Mathematica notebook will use output.csv (if it has been renamed, it will need to be changed by hand in the notebook). The notebook will plot the output ARS curve.

3. MCMLparOutputExampleS2.csv: Example output file. The program should output this file (possible speed change) if the input file is inputExample.txt and the SPRNG library is SPRNG 2.0b.

3. MCMLparOutputExampleS5.csv: Example output file. The program should output this file (possible speed change) if the input file is inputExample.txt and the SPRNG library is SPRNG 5.0.

D. External packages:

1a. SPRNG 2.0b: This is the best version of SPRNG to download for Windows, since a Windows package is available from NAADSM [4]. SPRNG 2.0b is also available for Linux and Mac [5]. SPRNG 2.0b is the default; no additional flags are necessary. libsprng.a or some other SPRNG library must be linked.

1b. SPRNG 5.0: Linux and Mac users may wish to download the latest version of SPRNG [5]. The flag -DSPRNGFIVE must be used if the user has SPRNG 5.0 instead of SPRNG 2.0b.

2. OpenMP: The code uses OpenMP for parallelization. OpenMP can generally be downloaded with MinGW. The OpenMP library must be linked and the flag -fopenmp must be included.

3. MinGW libraries: The following libraries must be in the same directory as the .exe for it to work: libgomp-1.dll, libstdc++-6.dll, and libgcc_s_dw2-1.dll. These are provided with the .exe, and can be found at: http://www.mingw.org/


III. Program contents

A. Directories:

1. bin: Contains executable program
2. dataIn: Contains user input files
           User should keep the example file and change input.txt
3. dataOut: Contains output files and Mathematica notebooks to graph results.
           Example files:  S2 from SPRNG2 (Windows) and S5 from SPRNG5 (Linux)


IV. Design

A. Design choices:

Style: Variables and functions use lowerCamelCase. Constants use UPPER_CASE. Class definitions use UpperCamelCase.

main.cpp: Particle and layer classes were introduced. The layer class is convenient because it stores all reference values for the layer that a particle is in. The particle class includes a layer as a data member because the particle constantly needs information about the layer that it exists in. This might create unboxing slow-down.

main.cpp: Vectors were used for almost all sets of values. This design was used because vectors can be resized more easily than arrays, but it is possible to change some vectors in the program into arrays.

main.cpp: Some functions were initialized in main, within the parallel for loop, to avoid race conditions. There may be other ways of accomplishing this.

detect.cpp: Instead of just collecting output angles, this function measures where the photon would intersect with a detector given a finite detector radius. To turn off this feature, the user only needs to set the detector radius to be very large.

fixARS.cpp: In most experiments, researchers set the detector at evenly spaced central angles (for example, 0, 5, 10, …). The program corrects for this by collecting data for twice as many angle slices and adding the slices up in the proper way to imitate central angle data. The program also switches the first and last elements in the ARS vector, the second and second-to last elements, etc. This resulted in the transmission angles ranging from 90-180, while the reflection angles ranged from 0-90. The only purpose of this was to create more intuitive ARS curves, based on the idea that most humans read from left to right and are most comfortable with light travelling from left to right.

roulette.cpp: This function uses the same design and values as the roulette function in MCML, including where and when it is called.

scattFunction.cpp: Here, the program takes advantage of the fact that it gains a degree of freedom from the problem’s phi-independence. The math operations in this function are equivalent to building an orthogonal triad, where the particle’s direction vector is the first column in the triad, and multiplying the triad by the Euler rotation matrix. The phi-independence allows for freedom in choosing one of three sets of math operations. By finding the index of the smallest element in the particle’s direction vector and using this index to decide which of the three sets of math operations to use, the program avoids roundoff error.

specularR.cpp: The presence of this function stays consistent with the MCML convention. It is important when MCMLpar is implemented in the companion inverse program, MCSLinv. 


V. Troubleshooting:

A. Possible program errors: 

1. "Error: File did not open (in setParameters.cpp)." or "File reading error (in setParameters.cpp)." An input file is probably incorrectly named or missing, or for some reason the program cannot find it. There could also be a problem with the format of the input file.

2. "Error: x actual out of y wanted streams spawned!": This means that the parallelization did not work. It is possible that something went wrong with SPRNG, or the user must change numProc in the input file.

3. Compiler not recognizing vector class: User must use a compiler that is compatible with C++ 0x or beyond.


VI. Works Cited:

[1]    Z.H. Levine, R.H. Streater, A.-M. R. Lieberson, A.L. Pintar, C.C. Cooksey, and P. Lemaillet, Algorithm for Rapid Determination of Optical Scattering Parameters, unpublished.

[2]    R.H Streater, A-M. R. Lieberson, A.L. Pintar, Z.H. Levine, MCMLpar and MCSLinv: Parallel MCML and an Inverse Monte Carlo Algorithm to Calculate Optical Scattering Parameters, unpublished

[3]    L. Wang, S.L. Jacques, L. Zheng, MCML-Monte Carlo modeling of light transport in multi layered tissues, Computer Methods and Programs in Biomedicine 47, 1995, pp. 131-146.

[4]    NAADSM Development Team, SPRNG for Microsoft Windows and NAADSM, http://www.naadsm.org/opensource/sprng, 2013, accessed 28 July 2017.

[5]    M. Mascagni, A. Srinivasan, Algorithm 806: SPRNG: a scalable library for pseudorandom number generation, ACM Transactions on Mathematica Software 26, 2000, pp. 436-461; http://sprng.org, accessed 28 July 2017.
