COPTS += -DMAKE_EV3
COPTS += -DMAKE_EV3
mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += \

APPL_CXXOBJS += \
				FileIO.o\
				SceneInfo.o\
#
SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries


#include $(mkfile_path)/workspace/library/RyujiEv3/Makefile

endif 

# COPTS += -DMAKE_BT_DISABLE

APPL_DIRS +=\
	$(mkfile_path)workspace/src/FileOp\
	$(mkfile_path)workspace/src/SceneInfo\


INCLUDES +=\
	-I$(mkfile_path)workspace/include/FileOp\
	-I$(mkfile_path)workspace/include/SceneInfo\

COPTS += -I$(ETROBO_HRP3_WORKSPACE)/etroboc_common
COPTS += -DMAKE_EV3
COPTS += -std=gnu++11

