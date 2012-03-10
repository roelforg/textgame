all:
	@for file in *.cpp; do echo "[CXX]\t"$$file; g++ -I$(DIR)/include -c $$file; done
	@for level in `find -maxdepth 1 -mindepth 1 -type d | grep -v "skel"`; do make -C $$level DIR=$(DIR); done

