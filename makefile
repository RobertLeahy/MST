SUFFIXES+=.mk


#OPTIMIZATION:=-O0 -g -fno-inline -fno-elide-constructors -DDEBUG -fno-omit-frame-pointer
OPTIMIZATION=-O3
OPTS_SHARED:=-Wall -Wpedantic -Werror -fno-rtti -std=gnu++1y -I include
GPP:=..\MCPP\gcc49\bin\g++.exe $(OPTS_SHARED) $(OPTIMIZATION)
MKDIR=@mkdir_nofail.bat $(subst /,\,$(dir $(1)))


#	DEFAULT

.PHONY: all
all: bin/test.exe

.PHONY: clean
clean: cleandeps
	@rmdir_nofail.bat obj

.PHONY: cleanall
cleanall: clean
	@rmdir_nofail.bat bin
	
.PHONY: cleandeps
cleandeps:
	@rmdir_nofail.bat makefiles
	
	
#	DIRECTORIES

bin:
	@mkdir_nofail.bat bin
	
	
NODEPS:=clean cleanall cleandeps
	
	
ifeq (0,$(words $(findstring $(MAKECMDGOALS),$(NODEPS))))

	-include $(subst .cpp,.mk,$(subst src,makefiles,$(subst \,/,$(subst $(shell echo %CD%)\,,$(shell dir /b /s src\*.cpp)))))

endif


#	COMMON LIBRARIES AND OBJECTS
	
	
obj/%.o:
	$(call MKDIR,$(patsubst obj/%.o,makefiles/%.mk,$@))
	$(GPP) -MM -MT "$@" $(patsubst obj/%.o,src/%.cpp,$@) -MF $(patsubst obj/%.o,makefiles/%.mk,$@)
	$(call MKDIR,$@)
	$(GPP) -c -o $@ $(patsubst obj/%.o,src/%.cpp,$@)
	
	
bin/test.exe: \
obj/test.o | \
bin
	$(GPP) -o $@ $^