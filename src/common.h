#ifndef COMMON
#define COMMON

#ifdef __cplusplus
# define MP_BGN_C_DECLS    extern "C" {
# define MP_END_C_DECLS    }
#else
# define MP_BGN_C_DECLS
# define MP_END_C_DECLS
#endif

//MP_BGN_C_DECLS
//time
#include <time.h>
#include <sys/time.h>

//add opencv head
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/cvwimage.h>
#include <opencv/cxcore.h>

#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>

//other header
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <math.h>

typedef void                    mpVOID;
typedef bool                    mpBOOL;
typedef char                    mpCHAR;
typedef unsigned char           mpBYTE;
typedef int                     mpINT;
typedef unsigned int            mpUINT;
typedef long                    mpLONG;
typedef unsigned long           mpULONG;
typedef unsigned short          mpWORD;
typedef unsigned int            mpDWORD;
typedef unsigned long long      mpQWORD;
typedef float                   mpFLOAT;
typedef double                  mpDOUBLE;

using namespace std;
using namespace cv;

#define MP_LOG_DBG
#define MP_MEM_DBG

#define MP_MALLOC(s)            MP_Malloc(s)
#define MP_FREE(p)              MP_Free(p)

#define mpTRUE                  1
#define mpFALSE                 0
#define mpNULL                  0

#define QMESSAGEBOX_WARNING         "Warning"
#define QFILEDIALOG_SAVEIMAGE       "Save Image"
#define QFILEDIALOG_OPENIMAGE       "Open Image"
#define QFILEDIALOG_SUPPORTTYPE     "Image File(*.jpg *png)"
#define QFILEDIALOG_CURRENTPATH     "."

#define DELAY_DISPLAY_INTERVAL 50
#define DIRECTION_DISPLAY_INTERVAL 2000

#define TEMPLATE_NUMS   (10)
#define IMAGE_NUMS      (9)

#define HANDGESTURE_START1_CMD   (1)
#define HANDGESTURE_START2_CMD   (7)
#define HANDGESTURE_START3_CMD   (2)
#define HANDGESTURE_INVAILD_CMD    (0)
#define HANDGESTURE_STOP_CMD    (10)
#define HANDGESTURE_SUSPEND_CMD    2
#define HANDGESTURE_OFFSET_SCALE    100

#define HANDGESTURE_DIRECTION_LEFT  "Left"
#define HANDGESTURE_DIRECTION_RIGHT "Right"
#define HANDGESTURE_DIRECTION_UP    "Up"
#define HANDGESTURE_DIRECTION_DOWN  "Down"

#define HANDGESTURE_MONITOR_MINHIGH_POINT  0
#define HANDGESTURE_MONITOR_MAXHIGH_POINT  50
#define HANDGESTURE_RED_MIN_POINT       100
#define HANDGESTURE_RED_MAX_POINT       200
#define HANDGESTURE_GREEN_MIN_POINT     300
#define HANDGESTURE_GREEN_MAX_POINT     400
#define HANDGESTURE_BLUE_MIN_POINT      500
#define HANDGESTURE_BLUE_MAX_POINT      600

#ifdef MP_LOG_DBG
#define PRT_INFO(fmt, ...) MP_Log(__FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#else
#define PRT_INFO(fmt, ...)
#endif

typedef struct _tagLogTime
{
    struct tm logSec;
    mpINT logMSec;
} LogTime;

const int FeatureNum=5;//The hand gesture classification
const int GestureNum =11;

typedef struct {
    float angle[FeatureNum][10];//skin angle
    float anglecha[FeatureNum][10];//skin angeche
    float count[FeatureNum];//angle count
    string GestureName;
    string angleName;
    string anglechaName;
    string countName;

    void initGestureFeature()
    {
        memset(&angle[0],0,sizeof(angle));
        memset(&anglecha[0],0,sizeof(anglecha));
        memset(&count[0],0,sizeof(count));
        GestureName.clear();
        angleName.clear();
        anglechaName.clear();
        countName.clear();
    }

}SGestureFeature;

class WatershedSegmenter {
private:
    cv::Mat markers;
public:
    void setMarkers(const cv::Mat& markerImage) {

        // Convert to image of ints
        markerImage.convertTo(markers, CV_32S);
    }
    cv::Mat process(const cv::Mat &image) {

        // Apply watershed
        cv::watershed(image, markers);
        return markers;
    }
    // Return result in the form of an image
    cv::Mat getSegmentation() {

        cv::Mat tmp;
        // all segment with label higher than 255
        // will be assigned value 255
        markers.convertTo(tmp, CV_8U);
        return tmp;
    }

    // Return watershed in the form of an image
    cv::Mat getWatersheds() {
        cv::Mat tmp;
        markers.convertTo(tmp, CV_8U,255, 255);
        return tmp;
    }
};

// conversion from cvConvexityDefect
struct ConvexityDefect
{
    Point start;
    Point end;
    Point depth_point;
    float depth;
};

struct DrawPoint
{
    Point  point;
    Scalar color;
};

/**
 * @ingroup SUB_GROUP_LOG
 * @brief
 * @param   pszFile in which file
 * @param   iLine   in which line
 * @param   pFunction   in which function
 * @parma   format  output format
 */
mpVOID MP_Log(const mpCHAR * pszFile, mpINT iLine, const mpCHAR * pFunction,const mpCHAR * format, ...);

#endif // COMMON

