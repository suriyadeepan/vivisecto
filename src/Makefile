all: 
	cd simulator; make
	cd map; make
	g++ simulator/*.o map/*.o init.cc `pkg-config opencv --libs` -o init

run:
	./init

clean:
	rm init

#all:
#	cd dissect; make
#	cd simulator; make
#	cd plot; make
