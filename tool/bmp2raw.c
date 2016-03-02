    /* 
     *  bmp2raw.c - convert .bmp file to .raw file  
     *  compiled by gcc in SlackWare 11.0. 
     * 
     *  Copyright (C) 2007  Haiyong Zheng <zhyfly.org@gmail.com> 
     *                                     http://www.zhyfly.org 
     */  
      
    #include <stdio.h>  
    #include <stdlib.h>  
    #include <string.h>  
    #pragma pack (2) /* for byte-alignment */  
      
    /*-----STRUCTURES-----*/  
    typedef unsigned short WORD;  
    typedef unsigned long DWORD;  
    typedef signed long LONG;  
    typedef unsigned char BYTE;  
    typedef struct tagBITMAPFILEHEADER{  
        WORD   bfType;           /* "BM" */  
        DWORD  bfSize;           /* Size of file in bytes */  
        WORD   bfReserved1;      /* set to 0 */  
        WORD   bfReserved2;      /* set to 0 */  
        DWORD  bfOffBits;        /* Byte offset to actual bitmap data (= 54 if RGB) */  
    }BITMAPFILEHEADER;  
    typedef struct tagBITMAPINFOHEADER{  
        DWORD  biSize;           /* Size of BITMAPINFOHEADER, in bytes (= 40) */     
        LONG   biWidth;          /* Width of image, in pixels */  
        LONG   biHeight;         /* Height of images, in pixels */  
        WORD   biPlanes;         /* Number of planes in target device (set to 1) */  
        WORD   biBitCount;       /* Bits per pixel (24 in this case) */    
        DWORD  biCompression;    /* Type of compression (0 if no compression) */  
        DWORD  biSizeImage;      /* Image size, in bytes (0 if no compression) */  
        LONG   biXPelsPerMeter;  /* Resolution in pixels/meter of display device */  
        LONG   biYPelsPerMeter;  /* Resolution in pixels/meter of display device */  
        DWORD  biClrUsed;        /* Number of colors in the color table (if 0, use  
                        maximum allowed by biBitCount) */  
        DWORD  biClrImportant;   /* Number of important colors.  If 0, all colors  
                        are important */  
    }BITMAPINFOHEADER;  
    /* 
     * If it's not RGB image, it has an extra color palette structure. 
     * (1024 bytes normally) 
     */  
    typedef struct tagRGBQUAD{  
        BYTE   rgbBlue;  
        BYTE   rgbGreen;  
        BYTE   rgbRed;  
        BYTE   rgbReserved;  
    }RGBQUAD;  
      
    /*-----PROTOTYPES-----*/  
    int ReplaceStr(char*, char*, char*);  
      
    int main(int argc, char *argv[])  
    {  
        FILE *inputBMP, *outputRAW;  
        BYTE ***image, *outputFileName;  
        int i, j, k, width, height, level;  
        int rgbCount, bmpFileNameLen;  
        int *x;  
        BITMAPFILEHEADER bmfhdr;  
        BITMAPINFOHEADER bmihdr;  
        /* 
          RGBQUAD *aColors; 
          BYTE aBitmapBits[]; 
        */  
          
        if (argc != 2) {  
            printf("Arguments Error.\n");  
            printf("Usage:\n");  
            printf("\t\t%s <inputBMP.bmp>\n", argv[0]);  
            exit(0);  
        }   
          
        /*-----DECLARE INPUT FILE----*/   
        if (!(inputBMP = fopen(argv[1], "rb"))) {  
            printf("Cannot open file %s.\n", argv[1]);  
            exit(7);  
        }  
        fseek(inputBMP, 0L, SEEK_SET);  
          
        /* read file and info headers of input BitMaP image. */  
        fread(&bmfhdr.bfType, sizeof(WORD), 1, inputBMP);  
        fread(&bmfhdr.bfSize, sizeof(DWORD), 1, inputBMP);  
        fread(&bmfhdr.bfReserved1, sizeof(WORD), 1, inputBMP);  
        fread(&bmfhdr.bfReserved2, sizeof(WORD), 1, inputBMP);  
        fread(&bmfhdr.bfOffBits, sizeof(DWORD), 1, inputBMP);  
        fread(&bmihdr.biSize, sizeof(DWORD), 1, inputBMP);  
        fread(&bmihdr.biWidth, sizeof(LONG), 1, inputBMP);  
        fread(&bmihdr.biHeight, sizeof(LONG), 1, inputBMP);  
        fread(&bmihdr.biPlanes, sizeof(WORD), 1, inputBMP);  
        fread(&bmihdr.biBitCount, sizeof(WORD), 1, inputBMP);  
        fread(&bmihdr.biCompression, sizeof(DWORD), 1, inputBMP);  
        fread(&bmihdr.biSizeImage, sizeof(DWORD), 1, inputBMP);  
        fread(&bmihdr.biXPelsPerMeter, sizeof(LONG), 1, inputBMP);  
        fread(&bmihdr.biYPelsPerMeter, sizeof(LONG), 1, inputBMP);  
        fread(&bmihdr.biClrUsed, sizeof(DWORD), 1, inputBMP);  
        fread(&bmihdr.biClrImportant, sizeof(DWORD), 1, inputBMP);  
          
        printf("+--------------------+\n");      
        printf("| bfType: %d\n", bmfhdr.bfType);  
        printf("| bfSize: %ld\n", bmfhdr.bfSize);  
        printf("| bfReserved1: %d\n", bmfhdr.bfReserved1);  
        printf("| bfReserved2: %d\n", bmfhdr.bfReserved2);  
        printf("| bfOffBits: %ld\n", bmfhdr.bfOffBits);  
        printf("| biSize: %ld\n", bmihdr.biSize);  
        printf("| biWidth: %ld\n", bmihdr.biWidth);  
        printf("| biHeight: %ld\n", bmihdr.biHeight);  
        printf("| biPlanes: %d\n", bmihdr.biPlanes);  
        printf("| biBitCount: %d\n", bmihdr.biBitCount);  
        printf("| biCompression: %ld\n", bmihdr.biCompression);  
        printf("| biSizeImage: %ld\n", bmihdr.biSizeImage);  
        printf("| biXPelsPerMeter: %ld\n", bmihdr.biXPelsPerMeter);  
        printf("| biYPelsPerMeter: %ld\n", bmihdr.biYPelsPerMeter);  
        printf("| biClrUsed: %ld\n", bmihdr.biClrUsed);  
        printf("| biClrImportant: %ld\n", bmihdr.biClrImportant);  
        printf("+--------------------+\n");  
          
        /* width and height of input BitMaP image. */  
        width = bmihdr.biWidth;  
        height = bmihdr.biHeight;  
        level = 3; /* for RGB only */  
          
        /* malloc for 3-D array ***image and 1-D array *x. */  
        image = (BYTE ***)malloc(height * sizeof(BYTE **));  
        for (i=0; i<height; i++)  
            image[i] = (BYTE **)malloc(width * sizeof(BYTE *));  
        for(i=0; i<height; i++)  
            for (j=0; j<width; j++)  
                image[i][j] = (BYTE *)malloc(level * sizeof(BYTE));  
        x = (int *)malloc(level * sizeof(int));  
          
        /* initialize 3-D array ***image and 1-D array *x. */  
        for (i=0; i<height; i++)  
            for (j=0; j<width; j++)  
                for (k=0; k<level; k++)  
                    image[i][j][k] = 0;  
        for (k=0; k<level; k++)  
            x[k] = 0;  
          
        /* 
          bmihdr.biBitCount = 1  -> Binary image. 
          bmihdr.biBitCount = 8  -> Gray-Level or Indexed image. 
          bmihdr.biBitCount = 24 -> RGB image. 
        */  
        if ((bmihdr.biBitCount == 1) || (bmihdr.biBitCount == 8)) {  
            /* process color palette data of input BitMaP image. */  
            rgbCount = bmfhdr.bfOffBits - 54;  
              
            if (rgbCount % 4 != 0) {  
                printf("BMP image %s bmfhdr.bfOffBits = %ld Error.\n", argv[1], bmfhdr.bfOffBits);  
                exit(77);  
            }  
      
            fseek(inputBMP, rgbCount, SEEK_CUR);  
              
            /* get real data from input BitMaP image to 3-D array ***image. */  
            for (i=height-1; i>=0; i--) {  
                for (j=0; j<width; j++) {  
                    image[i][j][0] = fgetc(inputBMP);  
                }  
            }  
      
            /*-----DECLARE OUTPUT FILE----*/  
            bmpFileNameLen = strlen(argv[1]);  
            outputFileName = (BYTE *)malloc((bmpFileNameLen + 8) * sizeof(BYTE));  
            strcpy(outputFileName, argv[1]);  
            ReplaceStr(outputFileName, ".bmp", ".raw");  
              
            outputRAW = fopen(outputFileName, "wb");  
      
            /* write real data of input BitMaP image from 3-D array to output .raw file. */  
            for (i=0; i<height; i++)  
                for (j=0; j<width; j++)  
                    fputc(image[i][j][0], outputRAW);  
      
            printf("It's Binary, Gray-Level or Indexed BitMaP image.\n");  
            printf("BitMaP image %s is converted to %s successfully.\n", argv[1], outputFileName);  
      
            fclose(inputBMP);         
            fclose(outputRAW);  
            free(outputFileName);  
            free(image);  
        } else if (bmihdr.biBitCount == 24) {  
            /* get real data from input BitMaP image to 3-D array ***image. */  
            for (i=height-1; i>=0; i--) {  
                for (j=0; j<width; j++)  
                    for (k=level-1; k>=0; k--)  
                        image[i][j][k] = fgetc(inputBMP);  
                /* 
                  if(3*width%4 != 0) 
                  fseek(inputBMP, 4-width*3%4, SEEK_CUR); 
                */  
            }  
              
            /*-----DECLARE OUTPUT FILE----*/  
            bmpFileNameLen = strlen(argv[1]);  
            outputFileName = (BYTE *)malloc((bmpFileNameLen + 8) * sizeof(BYTE));  
            strcpy(outputFileName, argv[1]);  
            ReplaceStr(outputFileName, ".bmp", ".raw");  
              
            outputRAW = fopen(outputFileName, "wb");  
      
            /* write real data of input BitMaP image from 3-D array to output .raw file. */  
            for (i=0; i<height; i++)  
                for (j=0; j<width; j++) {  
                    for (k=0; k<level; k++)  
                   		fputc(image[i][j][2-k], outputRAW);
					//fputc(0,outputRAW);
                }  
      
            printf("It's RGB BitMaP image.\n");  
            printf("BitMaP image %s is converted to %s successfully.\n", argv[1], outputFileName);  
      
            fclose(inputBMP);  
            fclose(outputRAW);  
            free(outputFileName);  
            free(x);  
            free(image);  
        } else {  
            printf("BMP image %s bmihdr.biBitCount = %d Error.\n", argv[1], bmihdr.biBitCount);  
            exit(7);  
        }  
          
        return 0; /* for #ErrorNumber: 84 - int main(int argc, char *argv[]) { } */  
    } /* end of main() */  
      
    /* 
     * Replace *sMatchStr with *sReplaceStr in *sSrc. 
     */  
    int ReplaceStr(char *sSrc, char *sMatchStr, char *sReplaceStr)  
    {  
            int StringLen;  
        int MAX_MSG_LENGTH = 77;  
            char caNewString[MAX_MSG_LENGTH];  
      
            char *FindPos = strstr(sSrc, sMatchStr);  
            if ((!FindPos) || (!sMatchStr))  
                    return -1;  
          
            while (FindPos) {  
                    memset(caNewString, 0, sizeof(caNewString));  
                    StringLen = FindPos - sSrc;  
                    strncpy(caNewString, sSrc, StringLen);  
                    strcat(caNewString, sReplaceStr);  
                    strcat(caNewString, FindPos + strlen(sMatchStr));  
                    strcpy(sSrc, caNewString);  
      
                    FindPos = strstr(sSrc, sMatchStr);  
            }  
          
            return 0;  
    } /* end of ReplaceStr */  
