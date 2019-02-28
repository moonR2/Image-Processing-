#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;


int main()
{
    Mat image = imread("/home/moonify/Downloads/lena.jpg",IMREAD_GRAYSCALE);
    //Mat image = imread("/Users/moonify/Downloads/lena.jpg",IMREAD_GRAYSCALE);
    Mat image_x = image.clone();
    Mat image_y = image.clone();
    Mat imageRes = image.clone();
    Mat imageLap = image.clone();
    Mat sovel = image.clone();
    Mat laplacian = image.clone();

    int kernel_x[3][3] = {-1,0,1,-2,0,2,-1,0,+1};
    int kernel_y[3][3] = {-1,-2,-1,0,0,0,1,2,1}; 

    //Derivate for x
    for(int row = 1; row < image.rows-1; row++)
    {
        for(int col = 1; col < image.cols-1; col++)
        {
            int sum = 0;
            for(int k = -1 ; k <= 1; k++)
            {
                for(int j = -1 ; j<=1;j++)
                {
                    sum += image.at<uchar>(row+k,col+j)*kernel_x[j+1][k+1];

                }
            }
            image_x.at<uchar>(row,col) = saturate_cast<uchar>(sum);        
        }
    }


    //Derivate for y
    for(int row = 1; row < image.rows-1; row++)
    {
        for(int col = 1; col < image.cols-1; col++)
        {
            int sum = 0;
            for(int k = -1 ; k <= 1; k++)
            {
                for(int j = -1 ; j<=1;j++)
                {
                    sum += image.at<uchar>(row+k,col+j)*kernel_y[j+1][k+1];

                }
            }
 
            image_y.at<uchar>(row,col) = saturate_cast<uchar>(sum);       
        }
    }

    //Gradient Sobar function
    for(int row = 1; row < image.rows-1; row++)
    {
        for(int col = 1; col < image.cols-1; col++)
        {
            imageRes.at<uchar>(row,col) = sqrt(pow(image_x.at<uchar>(row,col),2)+pow(image_y.at<uchar>(row,col),2));
        }
    }

    //Laplacian Filter
    for(int row = 1; row < image.rows-1; row++)
    {
        for(int col = 1; col < image.cols-1; col++)
        {
            int sum;
            sum = image.at<uchar>(row-1,col) 
            + image.at<uchar>(row+1,col) 
            + image.at<uchar>(row,col-1) 
            + image.at<uchar>(row,col+1) 
            - 4 * image.at<uchar>(row,col);

            imageLap.at<uchar>(row,col) = saturate_cast<uchar>(sum); 
        }
    }
    //Concatenation for Sobel 
    hconcat(image,image_x,sovel);
    hconcat(sovel,image_y,sovel);
    hconcat(sovel, imageRes, sovel);

    //Concatenation for Laplacian filter
    hconcat(image,imageLap,laplacian);
    hconcat(laplacian,(image-imageLap),laplacian);

    string windowname = "Horizontal - Vertical - Both (SOBEL)";
    namedWindow(windowname,WINDOW_AUTOSIZE);
    // resizeWindow(windowname,400,400);
    imshow(windowname,sovel);
    
    string windowlap = "Simple Laplacian";
    namedWindow(windowlap,WINDOW_AUTOSIZE);
    //resizeWindow(windowres,400,400);
    imshow(windowlap,laplacian);

    waitKey(0);
    return 0;
}
