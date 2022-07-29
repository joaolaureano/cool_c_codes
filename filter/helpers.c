#include "helpers.h"
#include "math.h"


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

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int x = 0; x < height; x++){
        for(int y = 0; y < width; y++){

            BYTE red,blue,green = 0;

            red =   fmin(round(0.393 * image[x][y].rgbtRed + 0.769 * image[x][y].rgbtGreen + 0.189 * image[x][y].rgbtBlue), 255);

            green = fmin(round(0.349 * image[x][y].rgbtRed + 0.686 * image[x][y].rgbtGreen + 0.168 * image[x][y].rgbtBlue), 255);


            blue =  fmin(round(0.272 * image[x][y].rgbtRed + 0.534 * image[x][y].rgbtGreen + 0.131 * image[x][y].rgbtBlue), 255);

            image[x][y].rgbtRed = red;
            image[x][y].rgbtBlue = blue;
            image[x][y].rgbtGreen = green;
        }
    }
    return;
}


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

void calc_blur(RGBTRIPLE *pixel, int red_v, int blue_v, int green_v, float divider ){

    pixel->rgbtRed =     round(red_v / divider);
    pixel->rgbtBlue =    round(blue_v / divider);
    pixel->rgbtGreen =   round(green_v / divider);

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    for(int i = 1; i < width - 1; i++){
        for(int j = 1; j < height - 1; j++){
            int red_value = 0;
            int blue_value = 0;
            int green_value = 0;
            for(int k = i-1; k < i+2;k++){
                for(int l = j-1; l < j+2;l++){
                    red_value   +=      copy_image[l][k].rgbtRed;
                    blue_value  +=      copy_image[l][k].rgbtBlue;
                    green_value +=      copy_image[l][k].rgbtGreen;

                }
            }

            calc_blur(&image[j][i],red_value,blue_value,green_value, 9.0);

        }
    }

    int red_value_width[2];
    int blue_value_width[2];
    int green_value_width[2];


    for(int i = 1; i < width - 1; i++){
        red_value_width[0] = 0;
        blue_value_width[0] = 0;
        green_value_width[0] = 0;

        red_value_width[1] = 0;
        blue_value_width[1] = 0;
        green_value_width[1] = 0;

        for(int k = i-1; k < i+2;k++){
            for(int l = 0; l < 2;l++){

                red_value_width[0]   +=      copy_image[l][k].rgbtRed;
                blue_value_width[0]  +=      copy_image[l][k].rgbtBlue;
                green_value_width[0] +=      copy_image[l][k].rgbtGreen;

                red_value_width[1]   +=      copy_image[l + height - 2][k].rgbtRed;
                blue_value_width[1]  +=      copy_image[l + height - 2][k].rgbtBlue;
                green_value_width[1] +=      copy_image[l + height - 2][k].rgbtGreen;

            }
        }

        calc_blur(&image[0][i],red_value_width[0],blue_value_width[0],green_value_width[0], 6.0);

        calc_blur(&image[height - 1][i],red_value_width[1],blue_value_width[1],green_value_width[1], 6.0);
    }

        red_value_width[0] = red_value_width[1] = 0;
        blue_value_width[0] = blue_value_width[1] = 0;
        green_value_width[0] = green_value_width[1] = 0;


    for(int j = 1; j < height - 1; j++){
        red_value_width[0] = 0;
        blue_value_width[0] = 0;
        green_value_width[0] = 0;

        red_value_width[1] = 0;
        blue_value_width[1] = 0;
        green_value_width[1] = 0;

            for(int k = 0; k < 2;k++){
                for(int l = j-1; l < j+2;l++){

                red_value_width[0]   +=      copy_image[l][k].rgbtRed;
                blue_value_width[0]  +=      copy_image[l][k].rgbtBlue;
                green_value_width[0] +=      copy_image[l][k].rgbtGreen;

                red_value_width[1]   +=      copy_image[l][k + width - 2].rgbtRed;
                blue_value_width[1]  +=      copy_image[l][k + width - 2].rgbtBlue;
                green_value_width[1] +=      copy_image[l][k + width - 2].rgbtGreen;

                }
            }

            calc_blur(&image[j][0],red_value_width[0],blue_value_width[0],green_value_width[0], 6.0);

            calc_blur(&image[j][width - 1],red_value_width[1],blue_value_width[1],green_value_width[1], 6.0);

        }

        int red_value_corner[4];
        int blue_value_corner[4];
        int green_value_corner[4];


        for(int k = 0; k < 2;k++){
            for(int l = 0; l < 2;l++){

                red_value_corner[0]   +=      copy_image[l][k].rgbtRed;
                blue_value_corner[0]  +=      copy_image[l][k].rgbtBlue;
                green_value_corner[0] +=      copy_image[l][k].rgbtGreen;

                red_value_corner[1]   +=      copy_image[l][k + width - 2].rgbtRed;
                blue_value_corner[1]  +=      copy_image[l][k + width - 2].rgbtBlue;
                green_value_corner[1] +=      copy_image[l][k + width - 2].rgbtGreen;

                red_value_corner[2]   +=      copy_image[l + height - 2][k].rgbtRed;
                blue_value_corner[2]  +=      copy_image[l + height - 2][k].rgbtBlue;
                green_value_corner[2] +=      copy_image[l + height - 2][k].rgbtGreen;

                red_value_corner[3]   +=      copy_image[l + height - 2][k + width - 2].rgbtRed;
                blue_value_corner[3]  +=      copy_image[l + height - 2][k + width - 2].rgbtBlue;
                green_value_corner[3] +=      copy_image[l + height - 2][k + width - 2].rgbtGreen;
            }
        }

        calc_blur(&image[0][0],red_value_corner[0], blue_value_corner[0] ,green_value_corner[0], 4.0);

        calc_blur(&image[0][width - 1],red_value_corner[1], blue_value_corner[1] ,green_value_corner[1], 4.0);

        calc_blur(&image[height - 1][0],red_value_corner[2], blue_value_corner[2] ,green_value_corner[2], 4.0);

        calc_blur(&image[height - 1][width - 1],red_value_corner[3], blue_value_corner[3] ,green_value_corner[3], 4.0);

    return;
}
// Detect edges
void calc_edge(RGBTRIPLE *pixel, int red[2], int blue[2], int green[2]){

    int r_red, r_blue, r_green = 0;
    r_red   = ((int) round(sqrt(pow(red[0],2) + pow(red[1],2)))) ;
    r_blue  = ((int) round(sqrt(pow(blue[0],2) + pow(blue[1],2)))) ;
    r_green = ((int) round(sqrt(pow(green[0],2) + pow(green[1],2)))) ;

    pixel->rgbtRed = r_red > 255 ? 255: r_red;
    pixel->rgbtBlue =  r_blue > 255 ? 255: r_blue;
    pixel->rgbtGreen = r_green > 255 ? 255: r_green;



    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int kernel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernel_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};


  RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height ; i++){
        for(int j = 0; j < width ; j++){
            int red_value[2]    = {0,0};
            int blue_value[2]   = {0,0};
            int green_value[2]  = {0,0};

                for(int k = -1; k < 2;k++){
                    for(int l = -1; l < 2;l++){
                        int k_i = k + i;
                        int l_j = l + j;

                        if (
                            k_i < 0 || k_i > height - 1 ||
                            l_j < 0 || l_j > width - 1
                        )
                        {
                            continue;
                        }

                        int k_p = k + 1;
                        int l_p = l + 1;

                    red_value[0]   +=    copy_image[k_i][l_j].rgbtRed *   kernel_x[k_p][l_p];
                    red_value[1]   +=    copy_image[k_i][l_j].rgbtRed *   kernel_y[k_p][l_p];

                    blue_value[0]  +=    copy_image[k_i][l_j].rgbtBlue *  kernel_x[k_p][l_p];
                    blue_value[1]  +=    copy_image[k_i][l_j].rgbtBlue *  kernel_y[k_p][l_p];

                    green_value[0] +=    copy_image[k_i][l_j].rgbtGreen *  kernel_x[k_p][l_p];
                    green_value[1] +=    copy_image[k_i][l_j].rgbtGreen *  kernel_y[k_p][l_p];

                }
            }

            calc_edge(&image[i][j],red_value,blue_value,green_value);

        }
    }

    return;
}
