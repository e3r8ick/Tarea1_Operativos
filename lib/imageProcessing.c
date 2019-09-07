//taken from https://github.com/Zarana-Parekh/Histogram-Equalization-Algorithm/blob/master/hist_serial.c

#include <imageProcessing.h>

// declare image dimensions and size as constant global variables

const int color_depth = 256;

void hist(char* filename){
    //read size from header
    int* size;
    size = read_size(filename);
    int image_width = size[0];
    printf("w: %i\n",image_width);
    int image_height = size[1];
    printf("h: %i\n",image_height);
    int image_size = image_width*image_height;
    /*int image_width = 256;
    int image_height = 256;
    int image_size = image_width*image_height;*/

    // read from the input bmp image file
    printf("here1\n");
    unsigned char* image = read_grayscale(filename);
    printf("here2\n");
    unsigned char* output_image = malloc(sizeof(unsigned char) * image_size);

    // create a histogram for the pixel values
    int* histogram = (int*)calloc(sizeof(int), color_depth);
    for(int i = 0; i < image_size; i++){
        histogram[image[i]]++;
    }

    // finding the normalised values using cumulative mass function
    float* transfer_function = (float*)calloc(sizeof(float), color_depth);
    for(int i = 0; i < color_depth; i++){
        for(int j = 0; j < i+1; j++){
            transfer_function[i] += round((color_depth*((float)histogram[j]))/(image_size));
        }
    }


    for(int i = 0; i < image_size; i++){
        output_image[i] = transfer_function[image[i]];
        // output_image[i] = image[i];
    }
    //char array_char[800];
    //strcpy(array_char,"images/");
    //strcat(array_char,filename);

    // write data to output bmp image file
    write_bmp(output_image, image_width, image_height,filename);
    // write(image,offset_size(argv[1]), read_head(argv[1]), image_width,image_height,"out.bmp");
}

int racist(char* filename){


    //read size from header
    int* size;
    size = read_size(filename);
    int image_width = size[0];
    //printf("w: %i\n",image_width);
    int image_height = size[1];
    //printf("h: %i\n",image_height);
    int image_size = image_width*image_height;

    // read from the input bmp image file
    unsigned char* image = read_full_color(filename);


    long sumR=0,sumG=0,sumB=0;
    for(int i=0;i<image_size*3;i+=3){
        sumB+=image[i];
        sumG+=image[i+1];
        sumR+=image[i+2];
    }

    printf("R: %ld, G: %ld, B: %ld \n",sumR,sumG,sumB);
    if(sumR>sumB&&sumR>sumG){
        return 1;
        //printf("Is RED\n");
    }
    else if(sumG>sumB&&sumG>sumR) {
        return 2;
        //printf("Is GREEN\n");
    }
    else{
        return 3;
        //printf("Is BLUE\n");
    }


}
