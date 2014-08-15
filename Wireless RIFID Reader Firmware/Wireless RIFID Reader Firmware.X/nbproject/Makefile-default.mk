#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Wireless_RIFID_Reader_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Wireless_RIFID_Reader_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../main.c ../Uart/Uart1.c ../XBee/XBee.c ../Delay/Delay.c ../DeviceID/DeviceID.c ../Rfid/Rfid.c ../Animations/Animations.c ../NeoPixels/NeoPixels.c ../SleepTimer/SleepTimer.c ../Uart/Uart2.c ../Battery/Battery.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/761528099/Uart1.o ${OBJECTDIR}/_ext/761468935/XBee.o ${OBJECTDIR}/_ext/2146845780/Delay.o ${OBJECTDIR}/_ext/617750912/DeviceID.o ${OBJECTDIR}/_ext/761612962/Rfid.o ${OBJECTDIR}/_ext/486401342/Animations.o ${OBJECTDIR}/_ext/1551418186/NeoPixels.o ${OBJECTDIR}/_ext/222419331/SleepTimer.o ${OBJECTDIR}/_ext/761528099/Uart2.o ${OBJECTDIR}/_ext/347092834/Battery.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/761528099/Uart1.o.d ${OBJECTDIR}/_ext/761468935/XBee.o.d ${OBJECTDIR}/_ext/2146845780/Delay.o.d ${OBJECTDIR}/_ext/617750912/DeviceID.o.d ${OBJECTDIR}/_ext/761612962/Rfid.o.d ${OBJECTDIR}/_ext/486401342/Animations.o.d ${OBJECTDIR}/_ext/1551418186/NeoPixels.o.d ${OBJECTDIR}/_ext/222419331/SleepTimer.o.d ${OBJECTDIR}/_ext/761528099/Uart2.o.d ${OBJECTDIR}/_ext/347092834/Battery.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/761528099/Uart1.o ${OBJECTDIR}/_ext/761468935/XBee.o ${OBJECTDIR}/_ext/2146845780/Delay.o ${OBJECTDIR}/_ext/617750912/DeviceID.o ${OBJECTDIR}/_ext/761612962/Rfid.o ${OBJECTDIR}/_ext/486401342/Animations.o ${OBJECTDIR}/_ext/1551418186/NeoPixels.o ${OBJECTDIR}/_ext/222419331/SleepTimer.o ${OBJECTDIR}/_ext/761528099/Uart2.o ${OBJECTDIR}/_ext/347092834/Battery.o

# Source Files
SOURCEFILES=../main.c ../Uart/Uart1.c ../XBee/XBee.c ../Delay/Delay.c ../DeviceID/DeviceID.c ../Rfid/Rfid.c ../Animations/Animations.c ../NeoPixels/NeoPixels.c ../SleepTimer/SleepTimer.c ../Uart/Uart2.c ../Battery/Battery.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Wireless_RIFID_Reader_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX470F512H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c   
	
${OBJECTDIR}/_ext/761528099/Uart1.o: ../Uart/Uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761528099 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761528099/Uart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/761528099/Uart1.o.d" -o ${OBJECTDIR}/_ext/761528099/Uart1.o ../Uart/Uart1.c   
	
${OBJECTDIR}/_ext/761468935/XBee.o: ../XBee/XBee.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761468935 
	@${RM} ${OBJECTDIR}/_ext/761468935/XBee.o.d 
	@${RM} ${OBJECTDIR}/_ext/761468935/XBee.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761468935/XBee.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/761468935/XBee.o.d" -o ${OBJECTDIR}/_ext/761468935/XBee.o ../XBee/XBee.c   
	
${OBJECTDIR}/_ext/2146845780/Delay.o: ../Delay/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2146845780 
	@${RM} ${OBJECTDIR}/_ext/2146845780/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/2146845780/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2146845780/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/2146845780/Delay.o.d" -o ${OBJECTDIR}/_ext/2146845780/Delay.o ../Delay/Delay.c   
	
${OBJECTDIR}/_ext/617750912/DeviceID.o: ../DeviceID/DeviceID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/617750912 
	@${RM} ${OBJECTDIR}/_ext/617750912/DeviceID.o.d 
	@${RM} ${OBJECTDIR}/_ext/617750912/DeviceID.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/617750912/DeviceID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/617750912/DeviceID.o.d" -o ${OBJECTDIR}/_ext/617750912/DeviceID.o ../DeviceID/DeviceID.c   
	
${OBJECTDIR}/_ext/761612962/Rfid.o: ../Rfid/Rfid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761612962 
	@${RM} ${OBJECTDIR}/_ext/761612962/Rfid.o.d 
	@${RM} ${OBJECTDIR}/_ext/761612962/Rfid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761612962/Rfid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/761612962/Rfid.o.d" -o ${OBJECTDIR}/_ext/761612962/Rfid.o ../Rfid/Rfid.c   
	
${OBJECTDIR}/_ext/486401342/Animations.o: ../Animations/Animations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/486401342 
	@${RM} ${OBJECTDIR}/_ext/486401342/Animations.o.d 
	@${RM} ${OBJECTDIR}/_ext/486401342/Animations.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/486401342/Animations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/486401342/Animations.o.d" -o ${OBJECTDIR}/_ext/486401342/Animations.o ../Animations/Animations.c   
	
${OBJECTDIR}/_ext/1551418186/NeoPixels.o: ../NeoPixels/NeoPixels.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1551418186 
	@${RM} ${OBJECTDIR}/_ext/1551418186/NeoPixels.o.d 
	@${RM} ${OBJECTDIR}/_ext/1551418186/NeoPixels.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1551418186/NeoPixels.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/1551418186/NeoPixels.o.d" -o ${OBJECTDIR}/_ext/1551418186/NeoPixels.o ../NeoPixels/NeoPixels.c   
	
${OBJECTDIR}/_ext/222419331/SleepTimer.o: ../SleepTimer/SleepTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/222419331 
	@${RM} ${OBJECTDIR}/_ext/222419331/SleepTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/222419331/SleepTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/222419331/SleepTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/222419331/SleepTimer.o.d" -o ${OBJECTDIR}/_ext/222419331/SleepTimer.o ../SleepTimer/SleepTimer.c   
	
${OBJECTDIR}/_ext/761528099/Uart2.o: ../Uart/Uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761528099 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761528099/Uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/761528099/Uart2.o.d" -o ${OBJECTDIR}/_ext/761528099/Uart2.o ../Uart/Uart2.c   
	
${OBJECTDIR}/_ext/347092834/Battery.o: ../Battery/Battery.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/347092834 
	@${RM} ${OBJECTDIR}/_ext/347092834/Battery.o.d 
	@${RM} ${OBJECTDIR}/_ext/347092834/Battery.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/347092834/Battery.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/347092834/Battery.o.d" -o ${OBJECTDIR}/_ext/347092834/Battery.o ../Battery/Battery.c   
	
else
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c   
	
${OBJECTDIR}/_ext/761528099/Uart1.o: ../Uart/Uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761528099 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761528099/Uart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/761528099/Uart1.o.d" -o ${OBJECTDIR}/_ext/761528099/Uart1.o ../Uart/Uart1.c   
	
${OBJECTDIR}/_ext/761468935/XBee.o: ../XBee/XBee.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761468935 
	@${RM} ${OBJECTDIR}/_ext/761468935/XBee.o.d 
	@${RM} ${OBJECTDIR}/_ext/761468935/XBee.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761468935/XBee.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/761468935/XBee.o.d" -o ${OBJECTDIR}/_ext/761468935/XBee.o ../XBee/XBee.c   
	
${OBJECTDIR}/_ext/2146845780/Delay.o: ../Delay/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2146845780 
	@${RM} ${OBJECTDIR}/_ext/2146845780/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/2146845780/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2146845780/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/2146845780/Delay.o.d" -o ${OBJECTDIR}/_ext/2146845780/Delay.o ../Delay/Delay.c   
	
${OBJECTDIR}/_ext/617750912/DeviceID.o: ../DeviceID/DeviceID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/617750912 
	@${RM} ${OBJECTDIR}/_ext/617750912/DeviceID.o.d 
	@${RM} ${OBJECTDIR}/_ext/617750912/DeviceID.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/617750912/DeviceID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/617750912/DeviceID.o.d" -o ${OBJECTDIR}/_ext/617750912/DeviceID.o ../DeviceID/DeviceID.c   
	
${OBJECTDIR}/_ext/761612962/Rfid.o: ../Rfid/Rfid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761612962 
	@${RM} ${OBJECTDIR}/_ext/761612962/Rfid.o.d 
	@${RM} ${OBJECTDIR}/_ext/761612962/Rfid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761612962/Rfid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/761612962/Rfid.o.d" -o ${OBJECTDIR}/_ext/761612962/Rfid.o ../Rfid/Rfid.c   
	
${OBJECTDIR}/_ext/486401342/Animations.o: ../Animations/Animations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/486401342 
	@${RM} ${OBJECTDIR}/_ext/486401342/Animations.o.d 
	@${RM} ${OBJECTDIR}/_ext/486401342/Animations.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/486401342/Animations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/486401342/Animations.o.d" -o ${OBJECTDIR}/_ext/486401342/Animations.o ../Animations/Animations.c   
	
${OBJECTDIR}/_ext/1551418186/NeoPixels.o: ../NeoPixels/NeoPixels.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1551418186 
	@${RM} ${OBJECTDIR}/_ext/1551418186/NeoPixels.o.d 
	@${RM} ${OBJECTDIR}/_ext/1551418186/NeoPixels.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1551418186/NeoPixels.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/1551418186/NeoPixels.o.d" -o ${OBJECTDIR}/_ext/1551418186/NeoPixels.o ../NeoPixels/NeoPixels.c   
	
${OBJECTDIR}/_ext/222419331/SleepTimer.o: ../SleepTimer/SleepTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/222419331 
	@${RM} ${OBJECTDIR}/_ext/222419331/SleepTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/222419331/SleepTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/222419331/SleepTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/222419331/SleepTimer.o.d" -o ${OBJECTDIR}/_ext/222419331/SleepTimer.o ../SleepTimer/SleepTimer.c   
	
${OBJECTDIR}/_ext/761528099/Uart2.o: ../Uart/Uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761528099 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761528099/Uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/761528099/Uart2.o.d" -o ${OBJECTDIR}/_ext/761528099/Uart2.o ../Uart/Uart2.c   
	
${OBJECTDIR}/_ext/347092834/Battery.o: ../Battery/Battery.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/347092834 
	@${RM} ${OBJECTDIR}/_ext/347092834/Battery.o.d 
	@${RM} ${OBJECTDIR}/_ext/347092834/Battery.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/347092834/Battery.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -I"../" -MMD -MF "${OBJECTDIR}/_ext/347092834/Battery.o.d" -o ${OBJECTDIR}/_ext/347092834/Battery.o ../Battery/Battery.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Wireless_RIFID_Reader_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Wireless_RIFID_Reader_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC0275F  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Wireless_RIFID_Reader_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Wireless_RIFID_Reader_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Wireless_RIFID_Reader_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
