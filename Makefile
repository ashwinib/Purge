all: dpurge mpurge

dpurge: purge.cpp
	g++ -o dpurge purge.cpp

mpurge: mpurge.cpp btree.cpp
	g++ -o mpurge mpurge.cpp btree.cpp

clean:
	rm -rf dpurge mpurge
