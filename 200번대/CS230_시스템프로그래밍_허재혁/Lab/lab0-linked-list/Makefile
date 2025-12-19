all: list.o test

.PHONY: test
test: list.o test.c
	gcc -o test list.o test.c
	timeout 2s ./test && $(MAKE) success

list.o: list.c list.h
	gcc -c list.c

clean:
	-rm *.o test

success:
	@echo
	@echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
	@echo "Passed the test, Everything worked!"
	@echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
	@echo
