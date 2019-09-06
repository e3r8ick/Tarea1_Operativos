//based on code foound at https://github.com/Zarana-Parekh/Histogram-Equalization-Algorithm/blob/master/hist_serial.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include <math.h> 

// declare image dimensions and size as constant global variables

const int color_depth = 256;

int main(int argc, char** argv){

    if(argc != 2){
        printf("Usage: %s image \n", argv[0]);
        exit(-1);
    }

    //read size from header
    int* size;
    size = read_size(argv[1]);
    int image_width = size[0];
    printf("w: %i\n",image_width);
    int image_height = size[1];
    printf("h: %i\n",image_height);
    int image_size = image_width*image_height;

    // read from the input bmp image file
    unsigned char* image = read_full_color(argv[1]);


    long sumR=0,sumG=0,sumB=0;
    for(int i=0;i<image_size*3;i+=3){
        sumB+=image[i];
        sumG+=image[i+1];   
        sumR+=image[i+2];
    }

    printf("R: %ld, G: %ld, B: %ld \n",sumR,sumG,sumB);
    if(sumR>sumB&&sumR>sumG){
        printf("Is RED\n");
    }
    else if(sumG>sumB&&sumG>sumR) {
        printf("Is GREEN\n");
    }
    else{
        printf("Is BLUE\n");
    }

  
}
