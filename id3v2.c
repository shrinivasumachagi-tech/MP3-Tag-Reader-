#include "id3v2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_size(unsigned char *b)
{
    /* ID3v2.3 uses normal big endian */
    return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
}

void view_id3v2(FILE *fp)
{
    char id[5] = {0};
    unsigned char size_bytes[4];
    int size;

    fseek(fp, 10, SEEK_SET);   // skip ID3 header

    printf("\nMP3 TAG READER AND EDITOR FOR ID3v2\n\n");

    while (1)
    {
        if (fread(id, 1, 4, fp) != 4)
            break;

        if (id[0] == '\0')
            break;

        fread(size_bytes, 1, 4, fp);
        size = read_size(size_bytes);

        fseek(fp, 2, SEEK_CUR); // flags

        char *data = calloc(1, size + 1);
        fread(data, 1, size, fp);

        if (!strncmp(id, "TIT2", 4))
            printf("TITLE   : %s\n", data + 1);
        else if (!strncmp(id, "TPE1", 4))
            printf("ARTIST  : %s\n", data + 1);
        else if (!strncmp(id, "TALB", 4))
            printf("ALBUM   : %s\n", data + 1);
        else if (!strncmp(id, "TYER", 4))
            printf("YEAR    : %s\n", data + 1);
        else if (!strncmp(id, "TCON", 4))
            printf("MUSIC   : %s\n", data + 1);
        else if (!strncmp(id, "COMM", 4))
            printf("COMMENT : %s\n", data + 4);

        free(data);
    }
}

int edit_id3v2(FILE *fp, char option, char *new_data)
{
    char id[5] = {0};
    unsigned char size_bytes[4];
    int size;
    char target[5];

    switch (option)
    {
        case 't': strcpy(target, "TIT2"); break;
        case 'a': strcpy(target, "TPE1"); break;
        case 'A': strcpy(target, "TALB"); break;
        case 'y': strcpy(target, "TYER"); break;
        case 'm': strcpy(target, "TCON"); break;
        case 'c': strcpy(target, "COMM"); break;
        default: return 0;
    }

    fseek(fp, 10, SEEK_SET);

    while (1)
    {
        long frame_pos = ftell(fp);

        if (fread(id, 1, 4, fp) != 4)
            break;

        if (id[0] == '\0')
            break;

        fread(size_bytes, 1, 4, fp);
        size = read_size(size_bytes);

        fseek(fp, 2, SEEK_CUR); // flags

        if (!strncmp(id, target, 4))
        {
            char *buf = calloc(1, size);
            buf[0] = 0x00;

            if (option == 'c')
            {
                buf[1] = 'e'; buf[2] = 'n'; buf[3] = 'g'; buf[4] = 0;
                strncpy(buf + 5, new_data, size - 5);
            }
            else
            {
                strncpy(buf + 1, new_data, size - 1);
            }

            fseek(fp, frame_pos + 10, SEEK_SET);
            fwrite(buf, 1, size, fp);

            free(buf);
            return 1;
        }

        fseek(fp, size, SEEK_CUR);
    }

    return 0;
}
