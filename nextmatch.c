#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levenshtein/levenshtein.h"

#define MINSCORE 0.7

void replace(char **dest, const char *src) {
  if (*dest)
    free(*dest);
  *dest = strdup(src);
}

int main(int argc, char *argv[]) {
  FILE *fp;
  char *line = NULL, *key = NULL, *next = NULL;
  double best_score = MINSCORE;
  bool get_next = false;
  size_t len = 0;
  ssize_t read;

  if(argc >= 3)
	  fp = fopen(argv[2],"r");
  else
	  fp = stdin;

  key = argv[1];

  if (fp == NULL || argc < 2 || key == NULL)
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, fp)) != -1) {
    if (get_next) {
      replace(&next, line);
      get_next = false;
    }

    int dist = levenshtein(key, line) - 1; // -1 is for the trailing \n

    double score = (read - dist) / (double)read;

    if (score > best_score) {

      fprintf(stderr, "candidate (%lf = (%d-%d)/%d) : %s\n", score, read, dist,
              read, line);
      get_next = true;
    }
  }

  if (next) {
    printf("%s", next);
    free(next);
  }

  free(line);
  return EXIT_SUCCESS;
}
