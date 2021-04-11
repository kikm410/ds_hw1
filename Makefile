cc=gcc
target1=hw1_naive
object1=hw1_naive.o
target2=hw1_kmp
object2=hw1_kmp.o

all: $(target1) $(target2)

$(target1) : hw1_naive.o
	$(cc) -o $(target1) $(object1)

$(target2) : hw1_kmp.o
	$(cc) -o $(target2) $(object2)

.PHONY : clean

clean :
	rm $(target1) $(target2) $(object1) $(object2)
