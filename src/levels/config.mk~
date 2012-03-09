#include '$(DIR)/config.mk'

CXX=g++
CXXFLAGS:=-fPIC -g

all:
	@for file in *.cpp; do echo -e "[CXX]\t"$$file && g++ $(CXXFLAGS) $$file -c ; done
	@echo -e "[LD]\tLinking "$(LEVEL)
	@g ++ -rdynamic -o $(DIR)/lib/$(LEVEL)

