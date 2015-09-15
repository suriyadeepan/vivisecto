all: 
	cd simulator; make
	cd map; make
	g++ -Wall -pg simulator/*.o map/*.o init.cc `pkg-config opencv --libs` -o init

run:
	./init

clean:
	rm init
	cd simulator; rm *.o
	cd map; rm *.o

#all:
#	cd dissect; make
#	cd simulator; make
#	cd plot; make
