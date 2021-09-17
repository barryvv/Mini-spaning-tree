mstprimdriver: mst.cpp header.h mstprimtest.cpp operator.cpp
	g++ -std=c++11 operator.cpp mst.cpp mstprimtest.cpp -o mstprimdriver
clean:
	rm mstprimdriver