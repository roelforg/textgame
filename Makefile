DIR=`pwd`

all:
	find . | grep "\.o" | xargs rm 2>/dev/null || true
	@make -C src DIR=$(DIR)

run: all
	./bin/textgame

