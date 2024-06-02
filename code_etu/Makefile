CXX=g++
CFLAGS=-Wall -std=c++17 -g
INCLUDES=
LIBS=
TARGET=main
OBJ=main.o Personne.o Bulletin.o Electeur.o TableDeDecharge.o TableDeVote.o Election.o Isoloir.o EspaceIsoloirs.o Bureau.o

all : $(TARGET)

clean :
	rm -f $(TARGET) $(OBJ)

$(TARGET) : $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ -c $<
