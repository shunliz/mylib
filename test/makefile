OBJS = main.o dlist.o Locker.o locker_pthread.o nested_locker.o BiTree.o


main:$(OBJS)
	gcc -o linux-main $(OBJS)

main.o: dlist.h Locker.h locker_pthread.h nested_locker.h
	gcc -c linux-main.c

dlist.o: dlist.h
	gcc -c dlist.c
	
Locker.o: Locker.h
	gcc -c Locker.c
	
locker_pthread.o:Locker.h
	gcc -c locker_pthread.c
	
nested_locker.o: nested_locker.h Locker.h
	gcc -c nested_locker.c
		
BiTree.o: BiTree.h 
	gcc -c BiTree.c
	