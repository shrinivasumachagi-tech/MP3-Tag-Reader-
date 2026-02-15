#ifndef MP3TAG_H
#define MP3TAG_H

#define TAG_SIZE 128

typedef struct
{
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    unsigned char genre;
} ID3v1Tag;

#endif
