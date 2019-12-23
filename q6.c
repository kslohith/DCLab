#include<stdio.h>
#include<gd.h>
#include<stdlib.h>
#include<omp.h>


int main(int argc , char* argv[])
{
    char* input_file = argv[1];
    char* output_file = argv[2];

    FILE* fp;

    if( (fp=fopen(input_file,"r")) == NULL)
    {
        printf("error opening input file\n");
    }

    double t1 = omp_get_wtime();
    int red , green , blue , r , g , b;
    int color , x , y;

    gdImagePtr img = gdImageCreateFromPng(fp);
    int width = gdImageSX(img);
    int height = gdImageSY(img);


    #pragma omp parallel for private(y,color,red,green,blue) num_threads(8)
        for(int x = 0; x < width; x++ )
        {
            #pragma omp critical
            {
                for(int y = 0; y < height; y++ )
                {
                    color = x + 0;
                    color = gdImageGetPixel(img,x,y);
                    
                    r= gdImageRed(img,color);
            g= gdImageGreen(img,color);
            b= gdImageBlue(img,color);
            red=green=blue=0.2126*r+0.7152*g+0.0722*b;

                    
                    color = gdImageColorAllocate(img,red,green,blue);
                    gdImageSetPixel(img,x,y,color);
                }
            }
        }
        double t2 = omp_get_wtime();

        if( (fp=fopen(output_file,"w")) == NULL)
        {
            printf("Error opening output file\n");
        }

        gdImagePng(img,fp);
        gdImageDestroy(img);
        fclose(fp);
        printf("Time taken%f\n",(t2-t1));

        return 0;
}
