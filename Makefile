# User must select SPRNG 5 options or SPRNG 2 options by uncommenting.
# User must customize home directories by hand.
#
CPP = g++
CPPFLAGS_ALL = -O3 -std=c++0x -fopenmp
################################################################################
#               SPRNG 5 OPTIONS
 CPPFLAGS_SPRNG = -DSPRNGFIVE
 INCLUDE_SPRNG  = -I/home/zlevine/Code/SPRNG/Sprng5.0/sprng5/include/
 LIB            = -L/home/zlevine/Code/SPRNG/Sprng5.0/sprng5/lib/
################################################################################
#               SPRNG 2 OPTIONS
# INCLUDE_SPRNG = -I/home/zlevine/Code/SPRNG/Sprng2.0b/sprng2.0/include/
# LIB           = -L/home/zlevine/Code/SPRNG/Sprng2.0b/sprng2.0/lib/
################################################################################

CPPFLAGS = ${CPPFLAGS_ALL} ${CPPFLAGS_SPRNG}
INCLUDE = ${INCLUDE_SPRNG}

OBJ = addVec.o \
boundary.o \
dataOut.o detect.o dotProd.o \
fixARS.o \
HGDist.o \
initSPRNG.o intersect.o \
layer.o likelihood.o \
main.o medInterface.o \
newSegSize.o \
particle.o propagate.o \
roulette.o \
scatter.o scattFunction.o scoreParam.o setParameters.o specularR.o


MCMLpar.x : ${OBJ}
	${CPP} -o $@ ${CPPFLAGS} ${OBJ} ${INCLUDE} ${LIB} -lsprng

%.o : %.cpp
	${CPP} -c ${CPPFLAGS} ${INCLUDE} $<

clean :
	rm -f MCMLpar.x ${OBJ}
