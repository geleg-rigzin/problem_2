.PHONY: all test plot
	
all: gen cntrl sspp

clean:
	rm -rf gen cntrl tim sspp *.bin
gen: gen.cpp
	g++ gen.cpp -o gen
cntrl: cntrl.cpp
	g++ cntrl.cpp -o cntrl
sspp: sspp.cpp
	g++ -Wall -Werror -O0 sspp.cpp -lpapi -o sspp
test: gen cntrl
	g++ -Wall -Werror -O0 sspp.cpp -lpapi -fsanitize=address -o sspp
	./test.sh sspp
