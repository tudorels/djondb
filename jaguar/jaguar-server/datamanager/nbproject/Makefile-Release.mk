#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/entityMD.o \
	${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/attributeMD.o \
	${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/entity.o \
	${OBJECTDIR}/manager/transaction/transactionmanager.o \
	${OBJECTDIR}/manager/transaction/transaction.o \
	${OBJECTDIR}/manager/transaction/transactionentry.o \
	${OBJECTDIR}/datamanager.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/libdatamanager.so

dist/Release/GNU-Linux-x86/libdatamanager.so: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdatamanager.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/entityMD.o: nbproject/Makefile-${CND_CONF}.mk /home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/entityMD.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/entityMD.o /home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/entityMD.cpp

${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/attributeMD.o: nbproject/Makefile-${CND_CONF}.mk /home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/attributeMD.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/attributeMD.o /home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/attributeMD.cpp

${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/entity.o: nbproject/Makefile-${CND_CONF}.mk /home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/entity.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/entity.o /home/cross/workspace/jaguar/jaguar/jaguar-server/datamanager/manager/entity.cpp

${OBJECTDIR}/manager/transaction/transactionmanager.o: nbproject/Makefile-${CND_CONF}.mk manager/transaction/transactionmanager.cpp 
	${MKDIR} -p ${OBJECTDIR}/manager/transaction
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/manager/transaction/transactionmanager.o manager/transaction/transactionmanager.cpp

${OBJECTDIR}/manager/transaction/transaction.o: nbproject/Makefile-${CND_CONF}.mk manager/transaction/transaction.cpp 
	${MKDIR} -p ${OBJECTDIR}/manager/transaction
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/manager/transaction/transaction.o manager/transaction/transaction.cpp

${OBJECTDIR}/manager/transaction/transactionentry.o: nbproject/Makefile-${CND_CONF}.mk manager/transaction/transactionentry.cpp 
	${MKDIR} -p ${OBJECTDIR}/manager/transaction
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/manager/transaction/transactionentry.o manager/transaction/transactionentry.cpp

${OBJECTDIR}/datamanager.o: nbproject/Makefile-${CND_CONF}.mk datamanager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/datamanager.o datamanager.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/libdatamanager.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
