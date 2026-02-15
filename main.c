#include "common.h"
#include "id3v2.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    char header[3];

    /* --help */
    if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        printf("HELP MENU\n");
        printf("-v -> view mp3 file contents\n");
        printf("-e -> edit mp3 file contents\n");
        printf("   -t -> edit title\n");
        printf("   -a -> edit artist\n");
        printf("   -A -> edit album\n");
        printf("   -y -> edit year\n");
        printf("   -m -> edit music\n");
        printf("   -c -> edit comment\n");
        return SUCCESS;
    }

    /* View */
    if (argc == 3 && strcmp(argv[1], "-v") == 0)
    {
        fp = fopen(argv[2], "rb");
        if (!fp)
        {
            perror("File open failed");
            return FAILURE;
        }

        fread(header, 1, 3, fp);
        if (strncmp(header, "ID3", 3) != 0)
        {
            printf("ERROR: ID3v2 tag not found\n");
            fclose(fp);
            return FAILURE;
        }

        view_id3v2(fp);
        fclose(fp);
        return SUCCESS;
    }

    /* Edit */
    if (argc == 5 && strcmp(argv[1], "-e") == 0)
    {
        fp = fopen(argv[4], "rb+");
        if (!fp)
        {
            perror("File open failed");
            return FAILURE;
        }

        fread(header, 1, 3, fp);
        if (strncmp(header, "ID3", 3) != 0)
        {
            printf("ERROR: ID3v2 tag not found\n");
            fclose(fp);
            return FAILURE;
        }

        if (edit_id3v2(fp, argv[2][1], argv[3]))
            printf("UPDATED SUCCESSFULLY\n");
        else
            printf("EDIT FAILED\n");

        fclose(fp);
        return SUCCESS;
    }

    printf("Invalid arguments. Use --help\n");
    return FAILURE;
}
