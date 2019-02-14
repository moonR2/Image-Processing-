    #include <opencv2/opencv.hpp>
    #include <iostream>
    #include <string>

    using namespace cv;
    using namespace std;

    Mat bit_slice(Mat image, int plane)
    {
    Mat image2;
    uint8_t tmp;
    image2 = Mat::ones(image.rows,image.cols,CV_8UC1); //Matrix of ones 

    for(int r = 0; r < image.rows; r++ )
    {
        for( int c = 0; c < image.cols; c++)
        {
        tmp = (uint8_t)pow(2,plane-1); // 1,2,4,8....planes
        tmp = image.at<uint8_t>(r,c) & tmp; //change bit planes
        if(tmp) image2.at<uchar>(r,c) = 255;
        else image2.at<uchar>(r,c) = 0;
        }
    }
            return image2;
    }


    int main(int argc, char** argv)
    {
    Mat image = imread("/home/moonify/Downloads/lena.jpg",IMREAD_GRAYSCALE); // Read the image file
    //Mat image = imread("/Users/moonify/Downloads/lena.jpg",IMREAD_GRAYSCALE); // Read the image file

    if (image.empty()) // Check for failure
    {
    cout << "Could not open or find the image" << endl;
    system("pause"); //wait for any key press
    return -1;
    }

    //Slice of the image with different planes
    Mat slice1 = bit_slice(image,1);
    Mat slice2 = bit_slice(image,2);
    Mat slice3 = bit_slice(image,3);
    Mat slice4 = bit_slice(image,4);
    Mat slice5 = bit_slice(image,5);
    Mat slice6 = bit_slice(image,6);
    Mat slice7 = bit_slice(image,7);
    Mat slice8 = bit_slice(image,8);

    //Concatenation process
    //Horizontal
    Mat post1[5] = {image,slice1, slice2, slice3, slice4};
    Mat post2[5] = {image,slice5, slice6, slice7, slice8}; 
    Mat hcont1;
    Mat hcont2;
    hconcat(post1,5,hcont1);
    hconcat(post2,5,hcont2);
    //Vertical
    Mat post3[2] = {hcont1,hcont2};
    Mat vcont;
    vconcat(post3,2,vcont);
    
    String windowName = "Plane-bit Slicing"; //Name of the window
    namedWindow(windowName,WINDOW_NORMAL); // Create a window
    //resizeWindow(windowName,450,450); Uncomment for custom size
    imshow(windowName, vcont); // Show our image xinside the created window.

    waitKey(0); // Wait for any keystroke in the window

    return 0;
    }
