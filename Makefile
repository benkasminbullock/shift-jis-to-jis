shift-jis-to-jis.h: shift-jis-to-jis.c
	cfunctions shift-jis-to-jis.c

c-tap-test.h: ../c-tap-test/$@
	copyafile ../c-tap-test/$@ $@

test: test.c shift-jis-to-jis.c c-tap-test.h shift-jis-to-jis.h
	$(CC) $(CFLAGS) -o $@ test.c shift-jis-to-jis.c
	prove ./test
