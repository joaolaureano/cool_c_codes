#include "helpers.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int x = 0; x < height; x++){
        for(int y = 0; y < width; y++){
            BYTE new_value = round((image[x][y].rgbtBlue + image[x][y].rgbtGreen + image[x][y].rgbtRed) / (float) 3);

            image[x][y].rgbtBlue = new_value;
            image[x][y].rgbtGreen = new_value;
            image[x][y].rgbtRed = new_value;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int max_x = width / 2;
    for(int x = 0; x < max_x; x++){
        for(int y = 0; y < height; y++){

            int idx_mirror = width - x - 1;

            RGBTRIPLE swap = image[y][x];
            image[y][x] = image[y][idx_mirror];
            image[y][idx_mirror] = swap;

        }
    }
    return;
}

void copy(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width]){

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed =    image[i][j].rgbtRed;
            copy[i][j].rgbtBlue =   image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen =  image[i][j].rgbtGreen;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];

    copy(height, width, image, copy_image);

    for(int i = 1; i < width - 1; i++){
        for(int j = 1; j < height - 1; j++){
            BYTE red_value = 0;
            BYTE blue_value = 0;
            BYTE green_value = 0;
            for(int k = i-1; k < i+2;k++){
                    printf("\n%d", k);
                for(int l = j-1; l < i+2;l++){

                    red_value   +=      copy_image[l][k].rgbtRed;
                    blue_value  +=      copy_image[l][k].rgbtBlue;
                    green_value +=      copy_image[l][k].rgbtGreen;
                }
            }

            image[397][405].rgbtRed =     red_value / 9;
            image[j][i].rgbtBlue =    blue_value / 9;
            image[j][i].rgbtGreen =   green_value / 9;
        }
    }
    return;
}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
