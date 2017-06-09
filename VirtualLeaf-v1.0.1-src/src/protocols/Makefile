# $Id: Makefile,v bd77d1217180 2011/08/26 17:47:44 michael $

# Set an environment varible $(MAKE) to the name of the make command
# on your machine, e.g. 'make' on UNIX and 'mingw32-make' on windows.
# Fallback default is UNIX make.

ifeq ($(MAKE),)
	MAKE=make
endif

PROTOCOLS=\
 MyEmptyModel\
 MyGrowthModel\
 MyDiffusionModel\
 MyAuxinModel

all:
	@for p in $(PROTOCOLS); do $(MAKE) -C $$p; done;

clean:
	@for p in $(PROTOCOLS); do $(MAKE) -C $$p clean; done;

# finis
