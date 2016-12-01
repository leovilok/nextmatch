CFLAGS+=-D LEV_CASE_INSENSITIVE

nextmatch: levenshtein/levenshtein.o

clean:
	-$(RM) nextmatch levenshtein/levenshtein.o

