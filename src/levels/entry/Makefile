LEVEL=entry
CXX=g++
CXXFLAGS:=-fPIC -g -I$(DIR)/include

all:
	@for file in *.cpp; do echo "[CXX]\t"$$file && g++ $(CXXFLAGS) $$file -c ; done
	@echo "[LD]\tLinking "$(LEVEL)
	@g++ -rdynamic *.o -o $(DIR)/lib/$(LEVEL).so -shared

