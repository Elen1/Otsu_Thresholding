/*

 * To change this license header, choose License Headers in Project Properties.

 * To change this template file, choose Tools | Templates

 * and open the template in the editor.

 */

#include "opencv2/core/core.hpp"
#include  "opencv2/highgui.hpp"

#include <iostream>
#include <vector>
#include <cmath>
#include <string>





int optimalThreshold(cv::Mat image)
{
    int histogram[256];
    for (int i = 0; i < 256; i++)
    {
            histogram[i] = 0;
    }
    for (int y = 0; y < image.rows; y++)
    {
            for (int x = 0; x < image.cols; x++)
            {

                    histogram[(int)image.at<uchar>(y, x)]++;
            }
    }
     
        
    int total = image.rows * image.cols;

    float sum = 0;
    for (int t=0 ; t<256 ; t++) {
        sum += t * histogram[t];
    }

    float sumB = 0;
    int wB = 0;
    int wF = 0;

    float varMax = 0;
    int threshold = 0;

    for (int t=0 ; t<256 ; t++)
    {
       wB += histogram[t];               
       if (wB == 0) continue;

       wF = total - wB;                 
       if (wF == 0) break;

       sumB += (float) (t * histogram[t]);

       float mB = sumB / wB;            
       float mF = (sum - sumB) / wF;    

       
       float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);

       
       if (varBetween > varMax)
       {
          varMax = varBetween;
          threshold = t;
       }
    }
    return threshold;
        
}


cv::Mat toBinary(cv::Mat im, int threshold)
{
    for (int i = 0; i < im.rows; i++)
    {

		for (int j = 0; j < im.cols; j++)

		{

			if (im.at<uchar>(i,j) < threshold)
			{
				im.at<uchar>(i, j) = 0;
			}

			else
                        {
				im.at<uchar>(i, j) = 255;
                        }

		}
                
    }
    return im;
      
}

int main()

{
    cv::Mat image = cv::imread("/home/elen/Pictures/violet.jpg",cv::IMREAD_GRAYSCALE);

    cv::namedWindow("image_before", cv::WINDOW_NORMAL);

    cv::imshow("image_before", image);
    
    
    int threshold = optimalThreshold(image);
    cv::Mat result = toBinary(image,threshold);
    
    cv::namedWindow("image_after", cv::WINDOW_NORMAL);

    cv::imshow("image_after", result);
    

    cv::waitKey(0);

    return 0;

}







