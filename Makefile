CFLAGS+=-D LEV_CASE_INSENSITIVE

nextmatch: levenshtein/levenshtein.c

clean:
	-$(RM) nextmatch

