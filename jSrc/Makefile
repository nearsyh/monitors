TYPE:=EXT

CXX = u++										# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD -DIMPLTYPE_${TYPE}
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = q1tallyVotes.o	q1printer.o q1voter.o q1main.o# object files forming 1st executable with prefix "q1"
DEPENDS = ${OBJECTS:.o=.d}						# substitute ".o" with ".d"
EXEC = vote

.PHONY : clean

all : ${EXEC} q1Driver.class					# build all executables

-include ImplType

ifeq (${IMPLTYPE},${TYPE})						# same implementation type as last time ?
${EXEC} : ${OBJECTS}
	${CXX} $^ -o $@
else
ifeq (${TYPE},)									# no implementation type specified ?
# set type to previous type
TYPE=${IMPLTYPE}
${EXEC} : ${OBJECTS}
	${CXX} $^ -o $@
else											# implementation type has changed
.PHONY : ${EXEC}
${EXEC} :
	rm -f ImplType
	touch q1tallyVotes.h
	${MAKE} ${EXEC} TYPE="${TYPE}"
endif
endif

ImplType :
	echo "IMPLTYPE=${TYPE}" > ImplType

${OBJECTS} : ${MAKEFILE_NAME}					# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}

q1Driver.class : q1TallyVotes.class q1PRNG.class q1Voter.class q1Printer.class # class files forming 2nd executable with prefix "q1"

%.class : %.java ${MAKEFILE_NAME}
	javac $<

clean :											# remove files that can be regenerated
	rm -f *.d *.o ${EXEC} *.class ImplType
