FLAGS=-Wall -pedantic -std=c++1z -iquote inc 
__start__:.//rpq

.//rpq: ./obj/program.o ./obj/operations.o ./obj/task.o
	g++ -o .//rpq ./obj/program.o ./obj/operations.o ./obj/task.o
./obj:
	mkdir ./obj

./obj/program.o: src/program.cpp inc/operations.h
	g++ -c ${FLAGS} -o ./obj/program.o src/program.cpp
./obj/operations.o: src/operations.cpp inc/operations.h inc/task.h
	g++ -c ${FLAGS} -o ./obj/operations.o src/operations.cpp
./obj/task.o: src/task.cpp inc/task.h
	g++ -c ${FLAGS} -o ./obj/task.o src/task.cpp

clean:
	rm -f .//rpq ./obj/*