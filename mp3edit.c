#include "common.h"
#include "mp3tag.h"
#include <stdio.h>
#include <string.h>

/* ---------------- EDIT TITLE ---------------- */
int edit_title(char *filename, char *new_title)
{
    FILE *fp;
    char buffer[10];
    long pos;

    fp = fopen(filename, "rb+");
    if (!fp)
    {
        perror("File open failed");
        return FAILURE;
    }

    /* Check ID3v2 */
    fseek(fp, 0, SEEK_SET);
    fread(buffer, 1, 3, fp);

    if (strncmp(buffer, "ID3", 3) == 0)
    {
        fseek(fp, 10, SEEK_SET);

        while (fread(buffer, 1, 4, fp) == 4)
        {
            if (strncmp(buffer, "TIT2", 4) == 0)
            {
                unsigned char size_bytes[4];
                fread(size_bytes, 1, 4, fp);
                fseek(fp, 2, SEEK_CUR);

                pos = ftell(fp);
                fseek(fp, pos + 1, SEEK_SET);

                fwrite(new_title, 1, strlen(new_title), fp);
                fclose(fp);
                return SUCCESS;
            }
            fseek(fp, -3, SEEK_CUR);
        }
    }

    /* ID3v1 fallback */
    fseek(fp, -125, SEEK_END);
    fwrite(new_title, 1, strlen(new_title), fp);
    fclose(fp);
    return SUCCESS;
}

/* ---------------- EDIT ARTIST ---------------- */
int edit_artist(char *filename, char *new_artist)
{
    FILE *fp;
    char buffer[10];
    long pos;

    fp = fopen(filename, "rb+");
    if (!fp)
        return FAILURE;

    fseek(fp, 0, SEEK_SET);
    fread(buffer, 1, 3, fp);

    if (!strncmp(buffer, "ID3", 3))
    {
        fseek(fp, 10, SEEK_SET);
        while (fread(buffer, 1, 4, fp) == 4)
        {
            if (!strncmp(buffer, "TPE1", 4))
            {
                unsigned char size_bytes[4];
                fread(size_bytes, 1, 4, fp);
                fseek(fp, 2, SEEK_CUR);

                pos = ftell(fp);
                fseek(fp, pos + 1, SEEK_SET);
                fwrite(new_artist, 1, strlen(new_artist), fp);
                fclose(fp);
                return SUCCESS;
            }
            fseek(fp, -3, SEEK_CUR);
        }
    }

    /* ID3v1 */
    fseek(fp, -95, SEEK_END);
    fwrite(new_artist, 1, strlen(new_artist), fp);
    fclose(fp);
    return SUCCESS;
}

/* ---------------- EDIT ALBUM ---------------- */
int edit_album(char *filename, char *new_album)
{
    FILE *fp;
    char buffer[10];
    long pos;

    fp = fopen(filename, "rb+");
    if (!fp)
        return FAILURE;

    fseek(fp, 0, SEEK_SET);
    fread(buffer, 1, 3, fp);

    if (!strncmp(buffer, "ID3", 3))
    {
        fseek(fp, 10, SEEK_SET);
        while (fread(buffer, 1, 4, fp) == 4)
        {
            if (!strncmp(buffer, "TALB", 4))
            {
                unsigned char size_bytes[4];
                fread(size_bytes, 1, 4, fp);
                fseek(fp, 2, SEEK_CUR);

                pos = ftell(fp);
                fseek(fp, pos + 1, SEEK_SET);
                fwrite(new_album, 1, strlen(new_album), fp);
                fclose(fp);
                return SUCCESS;
            }
            fseek(fp, -3, SEEK_CUR);
        }
    }

    /* ID3v1 */
    fseek(fp, -65, SEEK_END);
    fwrite(new_album, 1, strlen(new_album), fp);
    fclose(fp);
    return SUCCESS;
}

/* ---------------- EDIT YEAR ---------------- */
int edit_year(char *filename, char *new_year)
{
    FILE *fp;
    char buffer[10];
    long pos;

    fp = fopen(filename, "rb+");
    if (!fp)
        return FAILURE;

    fseek(fp, 0, SEEK_SET);
    fread(buffer, 1, 3, fp);

    if (!strncmp(buffer, "ID3", 3))
    {
        fseek(fp, 10, SEEK_SET);
        while (fread(buffer, 1, 4, fp) == 4)
        {
            if (!strncmp(buffer, "TYER", 4) || !strncmp(buffer, "TDRC", 4))
            {
                unsigned char size_bytes[4];
                fread(size_bytes, 1, 4, fp);
                fseek(fp, 2, SEEK_CUR);

                pos = ftell(fp);
                fseek(fp, pos + 1, SEEK_SET);
                fwrite(new_year, 1, strlen(new_year), fp);
                fclose(fp);
                return SUCCESS;
            }
            fseek(fp, -3, SEEK_CUR);
        }
    }

    /* ID3v1 */
    fseek(fp, -35, SEEK_END);
    fwrite(new_year, 1, 4, fp);
    fclose(fp);
    return SUCCESS;
}

/* ---------------- EDIT COMMENT ---------------- */
int edit_comment(char *filename, char *new_comment)
{
    FILE *fp;
    char buffer[10];
    long pos;

    fp = fopen(filename, "rb+");
    if (!fp)
        return FAILURE;

    fseek(fp, 0, SEEK_SET);
    fread(buffer, 1, 3, fp);

    if (!strncmp(buffer, "ID3", 3))
    {
        fseek(fp, 10, SEEK_SET);
        while (fread(buffer, 1, 4, fp) == 4)
        {
            if (!strncmp(buffer, "COMM", 4))
            {
                unsigned char size_bytes[4];
                fread(size_bytes, 1, 4, fp);
                fseek(fp, 2, SEEK_CUR);

                pos = ftell(fp);
                fseek(fp, pos + 5, SEEK_SET); // skip encoding + lang
                fwrite(new_comment, 1, strlen(new_comment), fp);
                fclose(fp);
                return SUCCESS;
            }
            fseek(fp, -3, SEEK_CUR);
        }
    }

    /* ID3v1 */
    fseek(fp, -31, SEEK_END);
    fwrite(new_comment, 1, strlen(new_comment), fp);
    fclose(fp);
    return SUCCESS;
}
