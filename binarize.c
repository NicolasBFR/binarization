//Safety infinite loop
#ifndef MAIN_BINARIZE_BINARIZEC
#define MAIN_BINARIZE_BINARIZEC


/**
 *  Author: Nicolas
 *  Until 2 oct: research
 *  Until 21 oct: malloc to prevent image size limit
 *  Until 22 oct : moving code out of main to functions
 *  Until 24 : correcting bugs, commenting
 *  17 dec : new Wellner's method implemented
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "binarize.h"
/**
 * binarize a matrix of gray pixels
 * inputs:
 *      in :   grayscaled matrix
 *      out :  result matrix
 *      w and h : width and height
 */


#define t 30
#define s 20


void binarize(Uint8 * in, Uint8 * out, int w, int h){
    Uint32 * intImg = NULL;
    intImg = malloc(w * h * sizeof(Uint32));
    //printf("\n\noui\n\n");
    Uint32 sum;
    for (Uint16 i = 0; i < w;i++){
        sum = 0;
        for (Uint16 j = 0; j < h;j++){
          sum += in[j * w + i];
          if (i == 0){
            intImg[j * w + i] = sum;
          }
          else{
            intImg[j * w + i] = intImg[j * w + i -1] + sum;
          }
        }
        //printf("%d + %u\n",i,w);
    }
    //printf("\n\nnon\n\n");
    for (Uint16 i = 0; i < w ;i++){
        for (Uint16 j = 0; j < h ;j++){
            Uint16 x1 = i - s/2;
            if (i <= s/2){
              x1 = 1;
            }
            Uint16 x2 = i + s/2;
            if (i +s/2 >= w){
              x2 = w-1;
            }
            Uint16 y1 = j - s/2;
            if (j <= s/2){
              y1 = 1;
            }
            Uint16 y2 = j + s/2;
            if (j +s/2 >= h){
              y2 = h-1;
            }
            Uint16 count = (x2-x1)*(y2-y1);
            sum = intImg[y2 * w + x2] - intImg[(y1 -1) * w + x2]
                    - intImg[y2 * w + x1-1] + intImg[(y1-1) * w + x1-1];
            if ((in[j * w + i] * count) <= (sum * (100 -t)/100)){
                out[j * w + i] = 0;
            }
            else{
                out[j * w + i] = 255;
            }
        }
        //printf("%d + %u\n",i,w);
    }
    free(in);
    free(intImg);
}

//End safety loop
#endif