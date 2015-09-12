all: 
	cd simulator; make
	g++ simulator/*.o init.cc `pkg-config opencv --libs` -o init

run:
	./init

clean:
	rm init

#all:
#	cd dissect; make
#	cd simulator; make
#	cd plot; make
