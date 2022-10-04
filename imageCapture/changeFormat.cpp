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
#include <QThread>

using namespace cv;
using namespace  std;

int main (){

    int nimgs=78;
    std::stringstream oldImgs, newImgs;

    Mat imgLeer, imgLeerMod, imgEscribir;
    namedWindow("image",WINDOW_AUTOSIZE);
    string direccion = "/home/glintec/Documents/haarTraining/weldingHaar/rawdata2/cuadro_";

    for(int i=1; i <= nimgs; i++){

        oldImgs << direccion << i << ".jpg";
        newImgs << direccion << i << ".bmp";
//        qDebug()<<oldImgs.str().c_str()<<endl;
//        imgLeer=imread(Saveimgs.str().c_str(),IMREAD_COLOR);
        imgLeer=imread(oldImgs.str(),IMREAD_COLOR);
        resize(imgLeer, imgLeerMod, Size(imgLeer.cols * 0.20,imgLeer.rows * 0.20), 0, 0, CV_INTER_LINEAR);
        imgEscribir=imwrite(newImgs.str(),imgLeerMod);
        oldImgs = std::stringstream();
        newImgs = std::stringstream();
        if (imgLeer.empty()) {
           cout << "Image File Not Found" << endl;
           break;
         }
        imshow("image", imgLeer);
        qDebug()<<"!Imagen !"<<i<<endl;

        waitKey(70);
        QThread::msleep(200);

    }
    destroyAllWindows();

    getchar();
    return 0;
}
