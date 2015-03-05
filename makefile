# Adding in a few variables to change up flags etc

CFLAGS = -g -O2 -pipe -Wall -W -Woverloaded-virtual -MMD -MP -fPIC -pthread -std=c++0x $(shell root-config --cflags) ${INCLUDE_PATH}

INCLUDE_PATH = 	-I$(shell root-config --incdir) \
		-Iinclude  \
		-I/home/eepgadm/lib/local/include \
		-I/user/include

LIBS = 	$(shell root-config --libs)\
	 -L/home/eepgadm/lib/local/lib\
	 -lconfig++


default: tbZAnal.exe MvaFilesEventWeightIntegral.exe

clean: _cleanall
_cleanall:
	rm -rf *.exe
	rm -rf *.o
	rm -rf *.d

tbZAnal.exe: analysisMain.o config_parser.o dataset.o AnalysisEvent.o cutClass.o plots.o histogramPlotter.o
	g++ $(CFLAGS) $(LIBS) -o tbZAnal.exe analysisMain.o config_parser.o dataset.o AnalysisEvent.o cutClass.o plots.o histogramPlotter.o

analysisMain.o: analysisMain.cpp config_parser.h dataset.h cutClass.h
	g++ $(CFLAGS) $(LIBS) -c analysisMain.cpp

config_parser.o: config_parser.h config_parser.cpp
	g++ $(CFLAGS) $(LIBS) -c config_parser.cpp

dataset.o: dataset.h dataset.cpp
	g++ $(CFLAGS) ${LIBS} -c dataset.cpp

AnalysisEvent.o: AnalysisEvent.C AnalysisEvent.h
	g++ $(CFLAGS) $(LIBS) -c AnalysisEvent.C

cutClass.o: cutClass.cpp cutClass.h
	g++ $(CFLAGS) $(LIBS) -c cutClass.cpp

plots.o: plots.cpp plots.h
	g++ $(CFLAGS) $(LIBS) -c plots.cpp

histogramPlotter.o: histogramPlotter.cpp histogramPlotter.h
	g++ $(CFLAGS) $(LIBS) -c histogramPlotter.cpp

MvaFilesEventWeightIntegral.exe: weightIntegralMacro.o SkimFileEvent.o
	g++ $(CFLAGS) $(LIBS) -o MvaFilesEventWeightIntegral.exe weightIntegralMacro.o SkimFileEvent.o

weightIntegralMacro.o: weightIntegralMacro.cpp SkimFileEvent.hpp
	g++ $(CFLAGS) $(LIBS) -c weightIntegralMacro.cpp

SkimFileEvent.o: SkimFileEvent.cpp SkimFileEvent.hpp
	g++ $(CFLAGS) $(LIBS) -c SkimFileEvent.cpp
