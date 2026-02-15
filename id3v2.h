#ifndef ID3V2_H
#define ID3V2_H

#include <stdio.h>

void view_id3v2(FILE *fp);
int edit_id3v2(FILE *fp, char option, char *new_data);

#endif
