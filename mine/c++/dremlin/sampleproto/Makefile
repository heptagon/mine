LIB_DIR = /usr/local/lib
PROTOBUF_DIR = /usr/local/include/google/protobuf

default:	test
test:	test.c
	g++ -g -o test -I${PROTOBUF_DIR} -I. -L${LIB_DIR} -lprotobuf test.c test.pb.cc Cell.cpp
	

