#include <iostream> 
#include <cstring>
#include <stdio.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "includes/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "includes/stb_image_resize.h"
void CalcPicSize(int w, int h, int *width, int *height);
using namespace std;
int main(int argc, char *argv[]){
    int w,h,width=120,height=120,n;
    unsigned char *idata = stbi_load(argv[1], &w, &h, &n, 3);
    CalcPicSize(w,h,&width,&height);
    auto *data = (unsigned char *) malloc(width*height*n);
    stbir_resize_uint8(idata, w, h, 0, data, width, height, 0, 3);
    for(int i=0;i<height;i+=2){
        cout<<"\n";
        for(int j=0;j<width;j++){
            //draw 2 pixels
            cout << "\033[38;2;"<<(int)data[(i*width+j)*3]<<";"<<(int)data[(i*width+j)*3+1]<<";"<<(int)data[(i*width+j)*3+2]<<"m" << \
            "\033[48;2;"<<(int)data[((i+1)*width+j)*3]<<";"<<(int)data[((i+1)*width+j)*3+1]<<";"<<(int)data[((i+1)*width+j)*3+2]<<"m"<<"▀\033[0m";
        }
    }
    cout << "\033[255;255H\033[A";
    cin.get();
    stbi_image_free(idata);
    stbi_image_free(data);
    printf("\033c\033[2K\r");
    return 0;
}
void CalcPicSize(int w, int h, int *width, int *height){
    int twidth, theight;//in windows change commands
    FILE *f1 = popen("tput cols", "r");//get term width
    fscanf(f1, "%d", &twidth);
    FILE *f2 = popen("tput lines", "r");//get term height
    fscanf(f2, "%d", &theight);
//     *width=twidth;
//     *height=theight*2;
    float twth = twidth/(theight*2);
    float wh = wh;
    if(twth>wh){
        *width=theight*2*w/h;
        *height=theight*2;
    } else if (twth<wh){
        *width=twidth;
        *height=twidth*h/w;
    } else {
        *width=twidth;
        *height=theight*2;
    }
}
