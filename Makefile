build: 2048.c dont_open_till_Christmas.h menuanim.h
	gcc 2048.c -o 2048 -lncurses

run: 2048
	./2048

clean:
	-rm 2048 save.txt 2>/dev/null || true

delsave: save.txt
	rm save.txt
