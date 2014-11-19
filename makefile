# Adding in a few variables to change up flags etc
CC = g++
CFLAGS = -g -Wall -std=c++0x $(shell root-config --cflags) -I/home/eepgdal/lib/local/include
LIBS = $(shell root-config --libs) -L/home/eepgdal/lib/local/lib -lconfig++ 
ROOTSYS = /cms/cmssw/slc5_amd64_gcc462/lcg/root/5.32.00/

default: tbZAnal

tbZAnal: analysisMain.o config_parser.o dataset.o AnalysisEvent.o cutClass.o plots.o histogramPlotter.o
	$(CC) $(CFLAGS) $(LIBS) -o tbZAnal analysisMain.o config_parser.o dataset.o AnalysisEvent.o cutClass.o plots.o histogramPlotter.o

analysisMain.o: analysisMain.cpp config_parser.h dataset.h cutClass.h
	$(CC) $(CFLAGS) $(LIBS) -c analysisMain.cpp

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