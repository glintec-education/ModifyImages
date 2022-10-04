    #include <QCoreApplication>

#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>
//#include <opencv4/opencv/cv.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/videoio.hpp>

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QString>

//#include "qtcommunicationdef.h"
//#include "parameters.h"
//#include "mainwindow.h"
//#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

static void onMouse(int event, int x, int y, int, void* );  //->>>>>>>>>>>>>>>>>>>>>>

Point origin, origin2;
int conta=0;

float px = 0;
float py = 0;
Point pxy;


 Mat rotate(Mat src, double angle)
 {
     Mat dst;
     Point2f pt(src.cols/2., src.rows/2.);
     Mat r = getRotationMatrix2D(pt, angle, 1.0);
     warpAffine(src, dst, r, Size(src.cols, src.rows));
     return dst;
 }


int main(){

    Mat imbgr;
    Mat gris;
    Mat imHSV;
    Mat seg;
    int index = 0;

    char key = 0;
    VideoCapture camera(index);
    if (!camera.isOpened()){
        printf("falla al abrir el dispositivo\n");
        return 1;
    }

//    camera.set(CV_CAP_PROP_FRAME_HEIGHT,480);
//    camera.set(CV_CAP_PROP_FRAME_WIDTH,640);
    camera.set(CAP_PROP_FRAME_HEIGHT,480);
    camera.set(CAP_PROP_FRAME_WIDTH,640);


//    namedWindow("Imagen RGB", CV_WINDOW_AUTOSIZE);
//    namedWindow("gris",CV_WINDOW_AUTOSIZE);
//    namedWindow("HSV",CV_WINDOW_AUTOSIZE);
//    namedWindow("gray",CV_WINDOW_AUTOSIZE);
    namedWindow("gray",WINDOW_AUTOSIZE);

    while (key != 'q'){
        camera >> imbgr;

//        imbgr = rotate(imbgr, -90); //para camara trasera

//        cvtColor(imbgr,gris,CV_BGR2GRAY);
        cvtColor(imbgr,gris,COLOR_BGR2GRAY);
        cvtColor(imbgr,imHSV,COLOR_BGR2HSV);
        inRange(imHSV,Scalar(0,10,60), Scalar(20, 150, 255),seg);

        imshow("Imagen RGB",imbgr);
//        imshow("gris", gris);
//        imshow("HSV",imHSV);
//        imshow("segmentada",seg);

        setMouseCallback("Imagen RGB", onMouse, &imbgr);   //-<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

         key = waitKey(25);
    }
    return 0;
}


static void onMouse( int event, int x, int y, int, void* userInput )
{
    // get the pointer input image
        Mat* img= (Mat*)userInput;
        Mat image(*img);


        if( event != EVENT_LBUTTONDOWN )
          return;

        Point Y =Point(x,y);

        cout<<"Punto seleccionado:  "<<Y.x<<","<< Y.y<<"   "<<Point(x,y)<<endl;
//        float fx = 960.92;
//        float fy = fx;
//        float cx = 319.5;
//        float cy = 239.5;

//        float fx = 874.154;
//        float fy = fx;
//        float cx = 319.5;
//        float cy = 239.5;

//        float Z = 20;

//        float fx = 590.9337;
//        float fy = fx;
//        float cx = 319.5;
//        float cy = 239.5;
//        float Z = 1150;

/*Calibracion parameters Camara Roja*/
//        float fx = 683.793172699;
//        float fy = fx;
//        float cx = 320;
//        float cy = 240;
//        float Z = 1185;

/*Calibracion parameters Camara logitec*/
                float fx = 647.4508417987233;
                float fy = fx;
                float cx = 320;
                float cy = 240;
                float Z = 1150;

        float PX = (Y.x-cx)*(Z/fx);
        float PY = (Y.y-cy)*(Z/fy);



        cout<< "Dis en X:  "<<PX<<"   "<<"Dis en Y:   "<<PY<<endl<<endl;

        conta++;
        if (conta == 1){
           px=PX;
           py=PY;
           pxy =Y;
           circle(*img, pxy, 10, Scalar(0,0,255), 3);
        }

        if (conta ==2){
            float d = sqrt((PX-px)*(PX-px)+(PY-py)*(PY-py));
            cout << "MED[" <<d << "]" << endl;

            circle(*img, Y, 10, Scalar(255,0,0), 3);
            circle(*img, pxy, 10, Scalar(0,0,255), 3);
//            line(*img, Y, pxy, CV_RGB(0,255,0), 2, CV_AA);
            line(*img, Y, pxy, CV_RGB(0,255,0), 2, LINE_AA);
            putText(*img,  to_string(d), Point(180,320), FONT_HERSHEY_SCRIPT_COMPLEX, 3, CV_RGB(125,12,145), 2);

            conta=0;
        }

   imshow("gray", *img);

}


