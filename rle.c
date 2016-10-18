    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <ctype.h>
    void compress_file(FILE *fp_in, FILE *fp_out);
    void uncompress_file(FILE *fp_in, FILE *fp_out);
    int main(void) {
        FILE *fp_in, *fp_out;
        char nm_in[FILENAME_MAX], nm_out[FILENAME_MAX];
        int chk;
        for (;;) {
            printf(" ----------------------------------------- \n");
            printf("|             1 - Compress                |\n");
            printf("|             2 - Decompress              |\n");
            printf("|             3 - Exit                    |\n");
            printf(" ----------------------------------------- \n");
            do {
                printf("Enter a command: ");
                scanf(" %d", &chk);
            } while (isalpha(chk));
            if (chk != 1 && chk != 2 )
                exit(EXIT_SUCCESS);
            printf("Enter input file name: ");
            scanf(" %s", nm_in);
            printf("Enter output file name: ");
            scanf(" %s", nm_out);
            while ((fp_in = fopen(nm_in, "rb")) == NULL) {
                fprintf(stderr, "Can't open \"%s\"\n", nm_in);
                printf("Enter input file name: ");
                scanf(" %s", nm_in);
            }
            while ((fp_out = fopen(nm_out, "wb")) == NULL) {
                fprintf(stderr, "Can't create \"%s\"\n", nm_out);
                printf("Enter output file name: ");
                scanf(" %s", nm_out);
            }
            switch(chk) {
                case 1: compress_file(fp_in, fp_out); break;
                case 2: uncompress_file(fp_in, fp_out); break;
            }
            putchar('\n');
        }
        return 0;
    }
    void compress_file(FILE *fp_in, FILE *fp_out) {
        int count, ch, ch2, chk;
        ch = getc(fp_in);
        ch2 = ch;
        while (ch2 != EOF) {
            for (count = 0; ch2 == ch && count < 255; count++) {
                ch2 = getc(fp_in);
            }
            putc(count, fp_out);
            putc(ch, fp_out);
            ch = ch2;
        }
        fclose(fp_in);
        fclose(fp_out);
        fprintf(stderr, "File Compressed\n");
    }
    void uncompress_file(FILE *fp_in, FILE *fp_out) {
        int count, ch, ch2;
        for (count = 0; ch2 != EOF; count = 0) {
	    ch = getc(fp_in);
            if ( (ch2 = getc(fp_in) ) == EOF) 
                break;
            do {
                putc(ch2, fp_out);
                count++;
            } while (count < ch );
        }
        fclose(fp_in);
        fclose(fp_out);
        fprintf(stderr, "File Decompressed\n");
    }
