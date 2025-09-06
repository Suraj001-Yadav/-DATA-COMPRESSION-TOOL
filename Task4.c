#include <stdio.h>
#include <stdlib.h>

// Function to compress a file using RLE
void compressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    if (!in || !out) {
        printf("Error opening files!\n");
        return;
    }

    int count = 1;
    int curr = fgetc(in);
    if (curr == EOF) {
        fclose(in);
        fclose(out);
        return;
    }
    int next;

    while ((next = fgetc(in)) != EOF) {
        if (next == curr) {
            count++;
        } else {
            fprintf(out, "%d%c", count, curr);
            curr = next;
            count = 1;
        }
    }
    // Write last run
    fprintf(out, "%d%c", count, curr);

    fclose(in);
    fclose(out);
    printf("Compression complete: %s\n", outputFile);
}

// Function to decompress an RLE-compressed file
void decompressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    if (!in || !out) {
        printf("Error opening files!\n");
        return;
    }

    int count;
    char ch;
    while (fscanf(in, "%d%c", &count, &ch) == 2) {
        for (int i = 0; i < count; i++) {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);
    printf("Decompression complete: %s\n", outputFile);
}

int main() {
    char inputFile[100], compressedFile[100], decompressedFile[100];

    printf("Enter input file name: ");
    scanf("%s", inputFile);
    printf("Enter compressed file name: ");
    scanf("%s", compressedFile);
    printf("Enter decompressed file name: ");
    scanf("%s", decompressedFile);

    compressFile(inputFile, compressedFile);
    decompressFile(compressedFile, decompressedFile);

    printf("Process finished.\n");

    return 0;
}
