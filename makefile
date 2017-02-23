.SILENT:
TMP = "default"
ALLOBJ=





all:
	clear
	clear
	echo make all
	make main
	make producteur
	make consomateur

main: main.o utils.o
	echo création de main
	$(CC) -o main main.o utils.o $(CFLAGS)

producteur: producteur.o utils.o
	echo création de producteur
	$(CC) -o producteur producteur.o utils.o $(CFLAGS)

consomateur: consomateur.o utils.o
	echo création de consomateur
	$(CC) -o consomateur consomateur.o utils.o $(CFLAGS)



main.o: main.cpp utils.h
	echo $@
	$(CC) -o main.o -c main.cpp $(CFLAGS)

producteur.o: producteur.cpp utils.h
	echo $@
	$(CC) -o producteur.o -c producteur.cpp $(CFLAGS)

consomateur.o: consomateur.cpp
	echo $@
	$(CC) -o consomateur.o -c consomateur.cpp $(CFLAGS)

utils.o: utils.cpp utils.h
	echo $@
	$(CC) -o utils.o -c utils.cpp $(CFLAGS)
	

#special compiler tout les cpp
%.o: %.c
	clear
	clear
	echo $@
	$(CC) -o $@ -c $< $(CFLAGS)




clean:
	clear
	clear
	echo clean
	rm -f *.o


git:
	clear
	clear
	git add -A
	git commit -m $(TMP)
	git push


ipcrm:
	clear
	ipcrm -Q 1234















