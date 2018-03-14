#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int comBuraco, semBuraco;

  CvPoint p;
  image = imread("bolhas.png",CV_LOAD_IMAGE_GRAYSCALE);

  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;

  //remover bordas
  for (int i = 0; i < height; i += height-1){
    for (int j = 0; j < width; j++){
      if(image.at<uchar>(i,j) == 255){
        p.x = j;
        p.y = i;
        floodFill(image, p, 0);
      }
    }
  }

  for (int i = 0; i < height; i ++){
    for (int j = 0; j < width; j+= width-1){
      if(image.at<uchar>(i,j) == 255){
        p.x = j;
        p.y = i;
        floodFill(image, p, 0);
      }
    }
  }

  //alterar cor de fundo
  p.x = 0;
  p.y = 0;
  floodFill(image, p, 50);

  //buscar objetos com buracos presentes
  comBuraco = 0;
  semBuraco = 0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 0 && image.at<uchar>(i-1,j-1) == 255){
      comBuraco++;
      p.x=j;
  		p.y=i;
  		floodFill(image,p,150);
      p.x=j-1;
      p.y=i-1;
      floodFill(image,p,150);
	  }
	 }
  }

  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
      semBuraco++;
      p.x=j;
      p.y=i;
      floodFill(image,p,200);
    }
   }
  }

  cout<<"Com buraco: "<<comBuraco<<endl;
  cout<<"Sem buraco: "<<semBuraco<<endl;
  cout<<"Total: " <<comBuraco+semBuraco<<endl;
  imshow("image", image);
  imwrite("labeling.png", image);
  waitKey();
  return 0;
}
