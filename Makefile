# User must select SPRNG 5 options or SPRNG 2 options by uncommenting.
#
CPP = g++
CPPFLAGS_ALL = -std=c++0x -fopenmp
INCLUDE_EIGEN = -I/home/zlevine/Code/Eigen/eigen-eigen-5a0156e40feb/Eigen/
################################################################################
#               SPRNG 5 OPTIONS
 CPPFLAGS_SPRNG = -DSPRNGFIVE
 INCLUDE_SPRNG  = -I/home/zlevine/Code/SPRNG/Sprng5.0/sprng5/include/
 LIB            = -L/home/zlevine/Code/SPRNG/Sprng5.0/sprng5/lib/
################################################################################
#               SPRNG 2 OPTIONS
# INCLUDE_SPRNG = -I/home/zlevine/Code/SPRNG/Sprng2.0b/sprng2.0/include/
# LIB      = -L/home/zlevine/Code/SPRNG/Sprng2.0b/sprng2.0/lib/
################################################################################

CPPFLAGS = ${CPPFLAGS_ALL} ${CPPFLAGS_SPRNG}
INCLUDE = ${INCLUDE_SPRNG} ${INCLUDE_EIGEN}

OBJ = addVec.o \
boundary.o \
checkEigenVals.o constructA.o contour.o \
dataOut.o discMax.o detect.o dotProd.o \
evalMaxGrid.o \
fixARS.o fileToVec.o findRegion.o \
HGDist.o \
initSPRNG.o intersect.o \
layer.o leastSquares.o likelihood.o \
main.o medInterface.o \
newSegSize.o \
particle.o propagate.o \
roulette.o \
scatter.o scattFunction.o scoreParam.o searchRegion.o \
setParameters.o solveForMax.o specularR.o subFromMax.o \
updateInterval.o \
weight.o


MCSLinv.x : ${OBJ}
	${CPP} -o $@ ${CPPFLAGS} ${OBJ} ${INCLUDE} ${LIB} -lsprng

%.o : %.cpp
	${CPP} -c ${CPPFLAGS} ${INCLUDE} $<

clean :
	rm -f MCSLinv.x ${OBJ}
