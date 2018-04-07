#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

double alfa;

int sup_slider = 0;
int sup_slider_max;

int decay_slider = 0;
int decay_slider_max = 100;

int inf_slider = 0;
int inf_slider_max;

Mat image1, image2, blended;

char TrackbarName[50];

double alpha(double x, double l1, double l2, double d){
  return 0.5*(tanh((x-l1)/d) - tanh((x-l2)/d));
}

void on_trackbar_blend(int,void*){
 for (int i = 0; i< image1.rows; i++){
   alfa = alpha(i, sup_slider, inf_slider, decay_slider);
    addWeighted( image1.row(i), alfa, image2.row(i), 1-alfa, 0.0, blended.row(i));
 }
 imshow("tiltshift", blended);
 imwrite("filtrada.jpg", blended);
}


int main(int argvc, char** argv){
  image1 = imread("img/gabi.jpg");
  image1.copyTo(image2);
  image1.copyTo(blended);
  namedWindow("tiltshift", 1);

  sup_slider_max = image1.rows;
  inf_slider_max = image1.rows;

  float media[] = {1,1,1,
                   1,1,1,
                   1,1,1};
  Mat mask(3,3,CV_32F), mask1;
  mask = Mat(3, 3, CV_32F, media);
  scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
  mask = mask1;

  for(int i = 0; i< 20; i++){
    filter2D(image1, image2, image1.depth(), mask, Point(1,1), 0);
  }
  sprintf( TrackbarName, "Superior %d", sup_slider_max );
  createTrackbar( TrackbarName, "tiltshift",
				  &sup_slider,
				  sup_slider_max,
				  on_trackbar_blend );
  on_trackbar_blend(sup_slider, 0 );

  sprintf( TrackbarName, "Decaimento %d", decay_slider_max );
  createTrackbar( TrackbarName, "tiltshift",
				  &decay_slider,
				  decay_slider_max,
				  on_trackbar_blend );
  on_trackbar_blend(decay_slider, 0 );

  sprintf( TrackbarName, "Inferior %d", inf_slider_max );
  createTrackbar( TrackbarName, "tiltshift",
          &inf_slider,
          inf_slider_max,
          on_trackbar_blend );
  on_trackbar_blend(inf_slider, 0 );

  waitKey(0);
  return 0;
}
