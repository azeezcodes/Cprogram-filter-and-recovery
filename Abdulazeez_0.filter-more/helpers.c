#include <math.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"




// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //calling averge
    int average;

   //looping through the pixel of the images and applying same average rgb value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            average = round(((float)red + (float)green + (float)blue)/3);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;

        }
    }
    return;
}

// Reflect image horizontally
//executing the swap function
void swap (RGBTRIPLE *a, RGBTRIPLE *b){
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;

}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
 for(int i=0; i < height; i++)
 {
     for (int j=0, n = width/2; j<n ; j++)
     {
         swap(&image[i][j], &image[i][width-j-1]);
     }
 }

    return;
}







// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int total_red, total_blue, total_green;
            total_red = total_blue = total_green = 0;

            float zero_counter = 0.00;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int presentX = i + x;
                    int presentY = j + y;

                    if (presentX < 0 || presentX > (height - 1) || presentY < 0 || presentY > (width - 1))
                    {
                        continue;
                    }
                    total_red += image[presentX][presentY].rgbtRed;
                    total_green += image[presentX][presentY].rgbtGreen;
                    total_blue += image[presentX][presentY].rgbtBlue;

                    zero_counter++;
                }
                temp[i][j].rgbtRed = round(total_red / zero_counter);
                temp[i][j].rgbtGreen = round(total_green / zero_counter);
                temp[i][j].rgbtBlue = round(total_blue / zero_counter);
            }
        }

    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }




    return;
}








// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

 RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // sobel arrays with Gx and Gy matrix
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};




    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {

            float Gx_red;
            float Gx_blue;
            float Gx_green;
            float Gy_red;
            float Gy_blue;
            float Gy_green;
            Gx_red = Gx_blue = Gx_green = Gy_red = Gy_blue = Gy_green = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {

                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }

                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    Gx_red += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    Gx_green += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gx_blue += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gy_red += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    Gy_green += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gy_blue += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
            }

            int red_color = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green_color = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue_color = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            //  assign all to 255
            if (red_color > 255)
            {
                red_color = 255;
            }
            if (green_color > 255)
            {
                green_color = 255;
            }
            if (blue_color > 255)
            {
                blue_color = 255;
            }
            // new values assign
            image[i][j].rgbtRed = red_color;
            image[i][j].rgbtGreen = green_color;
            image[i][j].rgbtBlue = blue_color;
        }
    }

    return;
}
