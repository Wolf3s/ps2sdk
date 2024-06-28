if(DEFINED ENV{PS2DEV})
    SET(PS2DEV $ENV{PS2DEV})
else()
    message(FATAL_ERROR "The environment variable PS2DEV needs to be defined.")
endif()

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR mips)
SET(CMAKE_C_COMPILER mipsel-ps2-irx-gcc)
SET(CMAKE_CXX_COMPILER mipsel-ps2-irx-g++)
ADD_DEFINITIONS(-D_IOP -DPS2 -D__PS2__)
INCLUDE_DIRECTORIES($ENV{PS2SDK}/iop/include $ENV{PS2SDK}/common/include $ENV{PS2SDK}/ports_iop/include)
SET(CMAKE_C_FLAGS_INIT "-O2 -G0 -fno-builtin")
SET(CMAKE_CXX_FLAGS_INIT "-O2 -G0 -fno-builtin")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-T$ENV{PS2SDK}/iop/startup/linkfile -L$ENV{PS2SDK}/iop/lib -L$ENV{PS2DEV}/gsKit/lib -L$ENV{PS2SDK}/ports_iop/lib -Wl,-zmax-page-size=128 -nostdlib -Os -Wall")
#SET(CMAKE_SHARED_LINKER_FLAGS_INIT "...")
#SET(CMAKE_STATIC_LINKER_FLAGS_CONFIG_INIT "...")
#SET(CMAKE_STATIC_LINKER_FLAGS_INIT "...")
SET(CMAKE_TARGET_INSTALL_PREFIX $ENV{PS2DEV}/ports_iop)
SET(CMAKE_C_COMPILER_WORKS 1) #Hack by f0bes

SET(CMAKE_FIND_ROOT_PATH $ENV{PS2DEV} $ENV{PS2DEV}/iop $ENV{PS2DEV}/iop/iop $ENV{PS2SDK} $ENV{PS2SDK}/ports_iop)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(PLATFORM_PS2 TRUE)
SET(PS2IOP TRUE)
