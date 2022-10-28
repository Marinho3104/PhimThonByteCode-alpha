
outPutName := test

all: ownFileObjectFile
	g++ -o $(outPutName) ./*.o -g
	$(MAKE) clean

ownFileObjectFile:
	g++ -c $(ownFile)*.cpp -g

clean:
	rm -f *.o