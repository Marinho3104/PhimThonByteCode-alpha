
byteCodePath := ./../byteCode/
objectsPath := ./../objects/
utilsPath := ./../utils/
vmPath := ./../vm/

outPutName := test

all: ownFileObjectFile byteCodeObjectFile objectsObjectFile vmObjectFile utilsObjectFile
	g++ -o $(outPutName) ./*.o -g
	$(MAKE) clean

ownFileObjectFile:
	g++ -c $(ownFile)*.cpp -g

byteCodeObjectFile:
	$(MAKE) -C $(byteCodePath) objectFile
	mv $(byteCodePath)*.o ./

utilsObjectFile:
	$(MAKE) -C $(utilsPath) objectFile
	mv $(utilsPath)*.o ./

objectsObjectFile:
	$(MAKE) -C $(objectsPath) objectFile
	mv $(objectsPath)*.o ./

vmObjectFile:
	$(MAKE) -C $(vmPath) objectFile
	mv $(vmPath)*.o ./

clean:
	rm -f *.o