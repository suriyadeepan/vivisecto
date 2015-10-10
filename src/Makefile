all: 
	cd simulator; make
	cd map; make
	g++ simulator/*.o map/*.o *.cc  -lopencv_core -lopencv_imgproc -lopencv_highgui -o init

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
