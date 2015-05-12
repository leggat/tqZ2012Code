# Adding in a few variables to change up flags etc
CC = g++
CFLAGS = -g -Wall -std=c++0x $(shell root-config --cflags) -I/home/eepgdal/lib/local/include
LIBS = $(shell root-config --libs) -L/home/eepgdal/lib/local/lib -lconfig++ -lLHAPDF -lz
ROOTSYS = /cms/cmssw/slc5_amd64_gcc462/lcg/root/5.32.00/
LHAPDFLAGS = -I$(shell cd ${CMSSW_BASE}; scram tool tag lhapdffull INCLUDE) -L$(shell cd ${CMSSW_BASE}; scram tool tag lhapdffull LIBDIR) -lLHAPDF -lgfortran -lz
LHAP = -I/cms/cmssw/slc6_amd64_gcc472/external/lhapdf/5.9.1-cms/full/include -L/cms/cmssw/slc6_amd64_gcc472/external/lhapdf/5.9.1-cms/full/lib -lLHAPDF
INCLUDEFLAGS := -I/cms/cmssw/slc6_amd64_gcc472/external/lhapdf/5.9.1-cms/include/ =L/cms/cmssw/slc6_amd64_gcc472/external/lhapdf/5.9.1-cms/lib/ -lLHAPDF -lg

default: tbZAnal

tbZAnal: analysisMain.o config_parser.o dataset.o AnalysisEvent.o cutClass.o plots.o histogramPlotter.o
	$(CC) $(CFLAGS) $(LIBS) $(LHAP) -o tbZAnal analysisMain.o config_parser.o dataset.o AnalysisEvent.o cutClass.o plots.o histogramPlotter.o

analysisMain.o: analysisMain.cpp config_parser.h dataset.h cutClass.h
	$(CC) $(CFLAGS) $(LIBS) $(LHAP) -c analysisMain.cpp

config_parser.o: config_parser.h config_parser.cpp
	$(CC) $(CFLAGS) $(LIBS) -c config_parser.cpp

dataset.o: dataset.h dataset.cpp
	$(CC) $(CFLAGS) ${LIBS} -c dataset.cpp

AnalysisEvent.o: AnalysisEvent.C AnalysisEvent.h
	$(CC) $(CFLAGS) $(LIBS) -c AnalysisEvent.C

cutClass.o: cutClass.cpp cutClass.h
	$(CC) $(CFLAGS) $(LIBS) -c cutClass.cpp

plots.o: plots.cpp plots.h
	$(CC) $(CFLAGS) $(LIBS) -c plots.cpp

histogramPlotter.o: histogramPlotter.cpp histogramPlotter.h
	$(CC) $(CFLAGS) $(LIBS) -c histogramPlotter.cpp

clean:
	$(RM) tbZAnal *.o *~