SUBDIRS:= . condition_parser \
		condition_parser \
		database \
		date \
		node \
		token \
		../include

OBJECTS:= condition_parser/condition_parser.o \
		condition_parser/condition_parser_test.o \
		database/database.o \
		database/database_test.o \
		date/date.o \
		node/node.o \
		token/token.o \
		../include/test_runner.o \
		main.o

CCFLAGS:= -std=c++17


.PHONY: all clean yellow_db

all: clean yellow_db

yellow_db: $(OBJECTS)
	$(MAKE) $(OBJECTS)
	g++ -I../include -lstdc++ -g -Wall -o $@ $(OBJECTS)

SUBDIRSCLEAN=$(addsuffix clean,$(SUBDIRS))

clean: $(SUBDIRSCLEAN)

clean_curdir:
	rm -rfv *.o *~ core .depend .*.cmd *.ko *.mod.c

%clean: %
	$(MAKE) -C $< -f $(PWD)/Makefile clean_curdir

$(OBJECTS):
	g++ $(CCFLAGS) -g -Wall -c ${@:.o=.cpp} -o $@

-include $(DEP_FILES)
