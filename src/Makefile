CXXFLAGS:=-I$(DIR)/include
LDFLAGS:=-ldl -rdynamic

all: level app
level:
	@make -C levels DIR=$(DIR)

app:
	@for file in *.cpp; do echo "[CXX]\t"$$file && g++ -c $(CXXFLAGS) $$file ; done
	@echo "[LD]\ttextgame"
	@g++ *.o $(LDFLAGS) -g -ggdb -o $(DIR)/bin/textgame

run: all
	$(DIR)/bin/textgame

