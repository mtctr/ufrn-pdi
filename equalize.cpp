#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, equalized;
  int width, height;
  vector<Mat> planes;
  Mat hist;
  int nbins = 256;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  image= imread("img/IMG_0904edit.jpg",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data){
    cout << "imagem não encontrada" << endl;
  } else{
    resize(image, image, Size(720,480));
  }

  width  = image.cols;
  height = image.rows;

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;
  imshow("original", image);

  calcHist(&image, 1, 0, Mat(), hist, 1, &nbins, &histrange, uniform, acummulate);

  int histw = nbins, histh = nbins/2;
  Mat histImg(histh, histw, CV_8UC3, Scalar(0));
  normalize(hist, hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());

  histImg.setTo(Scalar(0));


  for(int i=0; i<nbins; i++){
    line(histImg,
         Point(i, histh),
         Point(i, histh-cvRound(hist.at<float>(i))),
         Scalar(0), 1, 8, 0);
  }
  


  imshow("image", image);
  waitKey();

  return 0;
}
