#include "common.h"
#include "mp3tag.h"

int view_tag(char *filename)
{
    FILE *fp;
    char tag[3];
    ID3v1Tag tagdata;

    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        perror("File open failed");
        return FAILURE;
    }

    /* Check ID3v2 first */
fseek(fp, 0, SEEK_SET);
fread(tag, 1, 3, fp);

if (strncmp(tag, "ID3", 3) == 0)
{
    printf("ID3v2 tag found\n");
    fclose(fp);
    return SUCCESS;
}

/* Check ID3v1 */
fseek(fp, -TAG_SIZE, SEEK_END);
fread(tag, 1, 3, fp);

if (strncmp(tag, "TAG", 3) != 0)
{
    printf("ERROR: ID3 tag not found\n");
    fclose(fp);
    return FAILURE;
}


    fread(tagdata.title, 1, 30, fp);
    fread(tagdata.artist, 1, 30, fp);
    fread(tagdata.album, 1, 30, fp);
    fread(tagdata.year, 1, 4, fp);
    fread(tagdata.comment, 1, 30, fp);
    fread(&tagdata.genre, 1, 1, fp);

    printf("\n----- MP3 TAG DETAILS -----\n");
    printf("Title   : %.30s\n", tagdata.title);
    printf("Artist  : %.30s\n", tagdata.artist);
    printf("Album   : %.30s\n", tagdata.album);
    printf("Year    : %.4s\n", tagdata.year);
    printf("Comment : %.30s\n", tagdata.comment);
    printf("Genre   : %d\n", tagdata.genre);

    fclose(fp);
    return SUCCESS;
}
