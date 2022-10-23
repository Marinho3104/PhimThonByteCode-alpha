
byteCodePath := ./../byteCode/
objectsPath := ./../objects/
parserPath := ./../parser/
utilsPath := ./../utils/
vmPath := ./../vm/

outPutName := test

all: ownFileObjectFile byteCodeObjectFile objectsObjectFile parserObjectFile utilsObjectFile
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

parserObjectFile:
	$(MAKE) -C $(parserPath) objectFile
	mv $(parserPath)*.o ./

clean:
	rm -f *.o