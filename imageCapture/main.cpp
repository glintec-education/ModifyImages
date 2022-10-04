#include <QCoreApplication>


//#include "opencv4/opencv2/core.hpp"
//#include <opencv4/opencv2/core/utility.hpp>
//#include "opencv4/opencv2/imgproc.hpp"
//#include "opencv4/opencv2/calib3d.hpp"
//#include "opencv4/opencv2/imgcodecs.hpp"
//#include "opencv4/opencv2/videoio.hpp"
//#include "opencv4/opencv2/highgui.hpp"
////#include "tbb/pipeline.h"

//#include <opencv4/opencv2/core/mat.hpp>

#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/mat.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

#include <QDebug>

using namespace cv;
using namespace  std;

Mat rotate(Mat src, double angle)
{
    Mat dst;
    Point2f pt(src.cols/2., src.rows/2.);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows));
    return dst;
}
int captureStereo(int indx1, int indx2, int idxImage=0, int numImages=21,
                      string ruta = "/home/glintec/Documents/recovery/CameraCal/camStereo_",
                      string nomCam1="cam1",
                      string nomCam2="cam2"){

    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
    compression_params.push_back(100);

    Mat imgCam1, imgCam2;
    VideoCapture camera[2];

    camera[0] = VideoCapture(indx1);
    camera[1] = VideoCapture(indx2);
    for (int i=0; i<2; i++){
            if (!camera[i].isOpened()){
                cout<<"!No se pudo abrir la camara!!! " << i << "\n";
                getchar();//espera que se preione Enter para dejar seguir
                return 1;
            }
        }

    for(int i=0; i<2; i++){
            camera[i].set(CAP_PROP_FRAME_HEIGHT,480);
            camera[i].set(CAP_PROP_FRAME_WIDTH,640);
        }

    bool SaveImage;

    string ruta1 = ruta+nomCam1;
    string ruta2 = ruta+nomCam2;
    std::stringstream Saveimgs;

    for(;;){

        camera[0] >> imgCam1;
        camera[1] >> imgCam2;

//        namedWindow("imagen Derecha",WINDOW_AUTOSIZE);
        imshow("image Derecha", imgCam1);
//        namedWindow("imagen Izquierda",WINDOW_AUTOSIZE);
        imshow("image Izquierda", imgCam2);

        if(waitKey(30) == 13){//espera 30ms y pregunta por ENTER

            Saveimgs << ruta1 << "R" << idxImage << ".jpg";
            SaveImage = imwrite(Saveimgs.str().c_str(), imgCam1, compression_params);
            Saveimgs = std::stringstream();

            Saveimgs << ruta2 << "L" << idxImage << ".jpg";
            SaveImage = imwrite(Saveimgs.str().c_str(), imgCam2, compression_params);
            Saveimgs = std::stringstream();
            idxImage++;
            if (!SaveImage){
                printf("!image %d saved failed!\n",idxImage);
            }else{
                printf("!image %d saved successful!\n",idxImage);
            }
            if (idxImage == numImages){break;}
        }
    }
    return 0;
}

int main (){

//    captureStereo(4, 2);


    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
    compression_params.push_back(100);

    Mat img;
    VideoCapture cam = VideoCapture(2);
    if(!cam.isOpened()){
        printf("!No se pudo abrir la camara!\n");
        getchar();//espera que se preione Enter para dejar seguir
        return -1;
    }


//    cam.set(CAP_PROP_FRAME_HEIGHT,1200);
//    cam.set(CAP_PROP_FRAME_HEIGHT,800);
//    cam.set(CAP_PROP_FRAME_WIDTH,600);
//    cam.set(CAP_PROP_FRAME_WIDTH,960);
    cam.set(CAP_PROP_FRAME_HEIGHT,480);
    cam.set(CAP_PROP_FRAME_WIDTH,640);

    bool SaveImage;
    int nimgs = 0;

//    std::string direccion = "C:\\Users\\GLOBAL\\Documents\\Proj_Qt\\CaliCam_2\\CamTorreon";
//    string direccion = "/home/glintec/Documents/recovery/CameraCal/microCam800x600_";
//    string direccion = "/home/glintec/Documents/weddingImg";
    string direccion = "/home/glintec/Documents/NonbrokenPiece";
    std::stringstream Saveimgs;

    for(;;){

    cam >> img;

//    img = rotate(img, -90); //para camara trasera

    namedWindow("image",WINDOW_AUTOSIZE);
    imshow("image", img);

    if(waitKey(30) == 13){//espera 30ms y pregunta por ENTER

        Saveimgs << direccion << nimgs << ".bmp";
        SaveImage = imwrite(Saveimgs.str().c_str(), img, compression_params);
        Saveimgs = std::stringstream();
        nimgs++;
            if (!SaveImage){
                printf("!image %d saved failed!\n",nimgs);
                qDebug()<<"!image saved failed!"<<nimgs<<endl;
            }else{
                printf("!image %d saved successful!\n",nimgs);
                qDebug()<<"!image saved successful!"<<nimgs<<endl;

            }
            if (nimgs == 100){break;}
        }
    }

    getchar();
    return 0;
}
