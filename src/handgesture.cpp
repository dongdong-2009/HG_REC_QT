#include "handgesture.h"
#include "ui_handgesture.h"

handGesture::handGesture(QWidget *parent) :
    QWidget(parent),maskImage(frame.rows, frame.cols, CV_8UC3),dstImage(frame),
    ui(new Ui::handGesture)
{
    ui->setupUi(this);

    ui->pushButton_openCamera->setEnabled(true);
    ui->pushButton_startRecognize->setDisabled(true);
    ui->pushButton_captureImage->setDisabled(true);
   // ui->pushButton_training->setDisabled(true);
    getCurrentFilePath();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(readFrame()));
    init_hand_template();
    EOperation = ENOTHING;
    sColor=Scalar(0,0,255);
}

handGesture::~handGesture()
{
    delete ui;

    //delete QT timer
    if(mpNULL != timer)
    {
        timer->stop();
        delete timer;
        timer = mpNULL;
    }
}

void handGesture::readFrame()
{
    cap>>frame;
    if(frame.empty() )
    {
        cout << "frame is empty! "<<endl;
        return ;
    }
    Mat original = frame.clone();    // Clone the current frame:
    QImage scrImage=QImage((const uchar*)original.data,original.cols,original.rows,QImage::Format_RGB888).rgbSwapped();
    scrImage = scrImage.scaled(400, 350);
    ui->label_srcScreen->setPixmap(QPixmap::fromImage(scrImage));

    sourceImagePreprocessing(original);


    handGestureDrawing();
    hand_template_match();
}

void handGesture::init_hand_template(void)
{
    PRT_INFO("\n");
    Mat srcImage;
    vector< vector<Point> > mContours;
    vector< Vec4i > mHierarchy;
    static const char *tmp_names[TEMPLATE_NUMS] =
    {"1.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp","7.bmp","8.bmp","9.bmp","10.bmp"};

    for(int i = 0; i < TEMPLATE_NUMS; i++)
    {
        string imagepath = sCurrentFilepPath + "/images/tempimages/";
        cout<<imagepath<<endl;
        srcImage = imread((imagepath+tmp_names[i]).c_str(), IMREAD_GRAYSCALE);
        if(true == srcImage.empty())
        {
            cout << "Failed to load image: " << tmp_names[i] <<endl;
            continue;
        }

        mContours.clear();
        mHierarchy.clear();
        findContours(srcImage, mContours, mHierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        if(mContours.size() > 0)
        {
            mContoursTemp.insert(mContoursTemp.end(), mContours.begin(), mContours.end());
        }
    }
    cout << "mContoursTemp size = " << mContoursTemp.size() << endl;
}

 void handGesture::binary_image_process(Mat src)
 {
     Mat tmpImage;
     Mat Cr, Cb;
     vector<Mat> channels;
     cvtColor(src, binImage, CV_BGR2GRAY);
     src.copyTo(tmpImage);
     cvtColor(tmpImage, tmpImage, CV_BGR2YCrCb);
     split(tmpImage, channels);
     Cr = channels.at(1);
     Cb = channels.at(2);
     //肤色检测，输出二值图像
     for (int j = 1; j < Cr.rows - 1; j++)
     {
         uchar* currentCr = Cr.ptr< uchar>(j);
         uchar* currentCb = Cb.ptr< uchar>(j);
         uchar* current = binImage.ptr< uchar>(j);
         for (int i = 1; i < Cb.cols - 1; i++)
         {
             if ((currentCr[i] > 140) && (currentCr[i] < 170)  &&(currentCb[i] > 77) && (currentCb[i] < 123))
                 current[i] = 255;
             else
                 current[i] = 0;
         }
      }
      dilate(binImage, binImage, Mat());
      imshow("watershed", binImage);
 }

void handGesture::sourceImagePreprocessing(Mat srcImage)
{
    medianBlur(srcImage, srcImage, 5); // 中值滤波: 可以很好的去除椒盐噪声
    // cvt to HSV color
    cv::Mat frameHSV;
    cvtColor( srcImage, frameHSV, CV_BGR2HSV );
    //Mat mask(srcImage.rows, srcImage.cols, CV_8UC1);
    Mat dstTemp1(srcImage.rows, srcImage.cols, CV_8UC3);
    Mat dstTemp2(srcImage.rows, srcImage.cols, CV_8UC3);
    //对HSV空间进行量化，得到2值图像
    inRange(frameHSV, Scalar(0,30,30), Scalar(40,170,256), dstTemp1);//split skin color
    inRange(frameHSV, Scalar(156,30,30), Scalar(180,170,256), dstTemp2);
    bitwise_or(dstTemp1, dstTemp2, maskImage);

    //去噪声，使手形更加清晰
    Mat element = getStructuringElement(MORPH_RECT, Size(7,7));
    erode(maskImage, maskImage, element);
    morphologyEx(maskImage, maskImage, MORPH_OPEN, element);
    dilate(maskImage, maskImage, element);
    morphologyEx(maskImage, maskImage, MORPH_CLOSE, element);
    srcImage.copyTo(dstImage, maskImage);//clone after preprocess image
}

void handGesture::hand_template_match(void)
{
    double hu = 1.0, huTmp = 0.0;
    int match_number = -1;

    if((filterContours.size() == 0) || (mContoursTemp.size() == 0))
    {
        cout << "There are no contours to match" << endl;
        return;
    }

    for(int i = 0; i < mContoursTemp.size(); i++)
    {
        for(int j = 0; j < filterContours.size(); j++)
        {
            huTmp = matchShapes(mContoursTemp[i], filterContours[j], CV_CONTOURS_MATCH_I3, 0);
            // hu矩越小，匹配度越高
            if(huTmp < hu)
            {
                hu = huTmp;
                //保存好，是哪个轮廓和哪个模板匹配上了
                match_number = i +1;
            }
            cout<<"filterContours:"<<filterContours.size()<<"  huTmp:"<<huTmp<<endl;
        }
    }

    cout<<"match_number:"<<match_number<<endl;
    if(centerNum < 8 )
    {
        mResultArray.push_back(match_number);
        centerNum++;
    }
    else
    {
        recResult = RecogniseResult(mResultArray);
        QString str;
        str.setNum(recResult);
        ui->label_result->setText(str);
        mResultArray.clear();
        centerNum =0;
    }
}

void handGesture::handRecogniseResult()
{
      PRT_INFO("\n");
      if(HANDGESTURE_STOP_CMD == recResult)
      {
          drawPoint.clear();
      }
      else
      {
          cout<<"DP size:"<<drawPoint.size()<<endl;
          if(drawPoint.size() > 2)
          {
              for(int i =0; i<drawPoint.size()-1;i++)
              {
                  line(dstImage, drawPoint[i].point,drawPoint[i+1].point, drawPoint[i+1].color, 5, CV_AA);
              }
          }
      }
}

int handGesture::RecogniseResult(vector<int> iArray)
{
    int result;
    int count=0;
    for(int i=0;i<iArray.size();i++)
    {
        result = iArray[i];
        for(int j=i;j<iArray.size();j++)
        {
            if(result == iArray[j])
                count++;
            if(count > (iArray.size()-2))
            {
                return result;
            }
        }
    }
}

void handGesture::handGestureDrawing()
{
    Size sz = frame.size();
    double imageArea = sz.width * sz.height;
    contours.clear();
    hierarchy.clear();
    filterContours.clear();
    findContours(maskImage, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    for (size_t i = 0; i < contours.size(); i++)
    {
        double contArea = contourArea(contours[i]);
       // if(contArea/imageArea > 0.015) filterContours.push_back(contours[i]);

        if(contArea > 5000) filterContours.push_back(contours[i]);
    }
    if(filterContours.size() < 0) return;
    dstImage.zeros(frame.size(),CV_8UC3);
    drawContours(dstImage, filterContours, -1, Scalar(0,255,0), 3);
    vector<Point2f> center(filterContours.size());
    ComputeHandGestureCenterPoint(center);

    rectangle(dstImage,Point(200,0),Point(300,60),Scalar(0,0,255), CV_FILLED, CV_AA,0);
    rectangle(dstImage,Point(350,0),Point(450,60),Scalar(0,255,0), CV_FILLED, CV_AA,0);
    rectangle(dstImage,Point(500,0),Point(600,60),Scalar(255,0,0), CV_FILLED, CV_AA,0);

    //via Center Point draw a rect box
    vector<Rect> boundRect(filterContours.size());
    for (int i = 0; i < (int)filterContours.size(); i++)
    {
        //boundRect[i] = boundingRect(Mat(filterContours[i]));
        //rectangle(dstImage,boundRect[i].tl(),boundRect[i].br(),Scalar(0,0,255), 2, 8,0);

        if(EOperation == EDIRRECOGNIZE)
        {
            if(centerNum < 8)
            {
                centerArray.push_back(center[i]);
                centerNum++;
            }
            else
            {
                string result;
                RecogniseHandGestureSeq(centerArray, boundRect[i].width/2, boundRect[i].height/2, result);
                cout<<"result:"<<result<<endl;
                QString showResult;
                showResult.append(result.c_str());
                ui->label_result->setText(showResult);
                centerArray.clear();
                centerNum = 0;
            }
        }
    }

    vector<ConvexityDefect> convexDefects;
    vector< int > hullI;
    for (size_t j=0; j<filterContours.size(); j++)
    {
        circle(dstImage, center[j], 8 ,Scalar(255, 0, 0), CV_FILLED);
        convexHull(Mat(filterContours[j]), hullI, false, false);//via filterContours get hull
        findConvexityDefects(filterContours[j], hullI, convexDefects);
        cout<<"size:"<<convexDefects.size()<<endl;
        Point minPoint=convexDefects[0].start;
        for(int i=0;i<convexDefects.size();i++)
        {
            line(dstImage, convexDefects[i].start, convexDefects[i].end, Scalar(255,0,0), 2, CV_AA);
            //line(dstImage, convexDefects[i].start, convexDefects[i].depth_point, Scalar(0,0,255), 2, CV_AA);
            //line(dstImage, convexDefects[i].depth_point, convexDefects[i].end, Scalar(0,0,255), 2, CV_AA);
            judgeCurrentDrawingColor(convexDefects[i].start);
            if(convexDefects[i].start.y < minPoint.y)  minPoint = convexDefects[i].start;//get hand min point
        }
        saveFingerTopPoint(minPoint);
    }
    handRecogniseResult();
    //display in screen
    QImage dImage=QImage((const uchar*)dstImage.data,dstImage.cols,dstImage.rows,QImage::Format_RGB888).rgbSwapped();
    if(!dImage.isNull())
    {
        dImage = dImage.scaled(400, 350);
        ui->label_cvtScreen->setPixmap(QPixmap::fromImage(dImage));
        dstImage.release();
    }
}

void  handGesture::saveFingerTopPoint(Point minPoint)
{
    DrawPoint dPoint;
    dPoint.point = minPoint;
    dPoint.color = sColor;
    if(recResult != HANDGESTURE_STOP_CMD)
        drawPoint.push_back(dPoint);
     circle(dstImage, minPoint, 8 ,sColor, CV_FILLED);
}

void  handGesture::judgeCurrentDrawingColor(Point curPoint)
{
    if(curPoint.y >=0 && curPoint.y<=80)
    {
        if(curPoint.x>= 200 && curPoint.x<= 300)
            sColor=Scalar(0,0,255);
        else  if(curPoint.x>= 350 && curPoint.x<= 450)
            sColor=Scalar(0,255,0);
        else  if(curPoint.x>= 500 && curPoint.x<= 600)
            sColor=Scalar(255,0,0);
    }
}

void  handGesture::findConvexityDefects(vector<Point>& contour, vector<int>& hull, vector<ConvexityDefect>& convexDefects)
{
    if(hull.size() > 0 && contour.size() > 0)
    {
        CvSeq* contourPoints;
        CvSeq* defects;
        CvMemStorage* storage;
        CvMemStorage* strDefects;
        CvMemStorage* contourStr;
        CvConvexityDefect *defectArray = 0;

        strDefects = cvCreateMemStorage();
        defects = cvCreateSeq( CV_SEQ_KIND_GENERIC|CV_32SC2, sizeof(CvSeq),sizeof(CvPoint), strDefects );
        //We transform our vector<Point> into a CvSeq* object of CvPoint.
        contourStr = cvCreateMemStorage();
        contourPoints = cvCreateSeq(CV_SEQ_KIND_GENERIC|CV_32SC2, sizeof(CvSeq), sizeof(CvPoint), contourStr);
        for(int i = 0; i < (int)contour.size(); i++) {
            CvPoint cp = {contour[i].x,  contour[i].y};
            cvSeqPush(contourPoints, &cp);
        }

        //Now, we do the same thing with the hull index
        int count = (int) hull.size();
        //int hullK[count];
        int* hullK = (int*) malloc(count*sizeof(int));
        for(int i = 0; i < count; i++) { hullK[i] = hull.at(i); }
        CvMat hullMat = cvMat(1, count, CV_32SC1, hullK);

        // calculate convexity defects
        storage = cvCreateMemStorage(0);
        defects = cvConvexityDefects(contourPoints, &hullMat, storage);
        defectArray = (CvConvexityDefect*)malloc(sizeof(CvConvexityDefect)*defects->total);
        cvCvtSeqToArray(defects, defectArray, CV_WHOLE_SEQ);

        for(int i = 0; i<defects->total; i++){
            ConvexityDefect def;
            def.start       = Point(defectArray[i].start->x, defectArray[i].start->y);
            def.end         = Point(defectArray[i].end->x, defectArray[i].end->y);
            def.depth_point = Point(defectArray[i].depth_point->x, defectArray[i].depth_point->y);
            def.depth       = defectArray[i].depth;
            convexDefects.push_back(def);
        }
        // release memory
        cvReleaseMemStorage(&contourStr);
        cvReleaseMemStorage(&strDefects);
        cvReleaseMemStorage(&storage);
        free(hullK);
    }
}

void handGesture::on_pushButton_openCamera_clicked()
{
    cap.open(0);
    if(!cap.isOpened()) {
        cout<<"Can't Open /dev/video0 device ID."<<endl;
        QMessageBox::information(mpNULL,tr(QMESSAGEBOX_WARNING),tr("Can't Open /dev/video0 device ID"));
    }else{
        timer->start(DELAY_DISPLAY_INTERVAL);
        ui->pushButton_startRecognize->setEnabled(true);
        //ui->pushButton_training->setEnabled(true);
        ui->pushButton_openCamera->setDisabled(true);
        ui->pushButton_captureImage->setEnabled(true);
    }
}

void handGesture::ComputeHandGestureCenterPoint(vector<Point2f>& center)
{
     if(filterContours.size() < 0)
     {
         PRT_INFO("filterContours can't small zero\n");
         return;
     }

     //get contours distance
     vector<Moments> g_vMoments(filterContours.size());
     for (int i = 0; i < (int)filterContours.size(); i++)
     {
          g_vMoments[i] = moments(filterContours[i], true);
          //get contours center
          center[i] = Point2f(float(g_vMoments[i].m10 / g_vMoments[i].m00), float(g_vMoments[i].m01 / g_vMoments[i].m00));//轮廓的面积为g_vMoments[i].m00
          cout<<"x:"<<center[i].x<<endl;
          cout<<"y:"<<center[i].y<<endl;
     }
}

void handGesture::ComputeHandGestureMaxCenterRadius(vector<Point2f> center,float &radius)
{
    if(filterContours.size() < 0)
    {
        PRT_INFO("filterContours can't small zero\n");
        return;
    }

    for (size_t j=0; j<filterContours.size(); j++)
    {
        convexHull(Mat(filterContours[j]), hull, true);
        int hullcount = (int)hull.size();
        for (int i=0; i<hullcount-1; i++)
        {
            double tmpRadius=sqrt((double)((center[j].x-hull[i].x)*(center[j].x-hull[i].x))+
                     (double)((center[j].y-hull[i].y)*(center[j].y-hull[i].y)));
            if(tmpRadius > radius)//as the max radius
            {
                radius = tmpRadius;
            }
        }
    }//end of for filterContours
}

void handGesture:: RecogniseHandGestureSeq(vector<Point2f> &ptArr, float width, float height, string &result)
{
    PRT_INFO("\n");
    float x_min_tmp=(float)(ptArr[0].x);
    float x_max_tmp=(float)(ptArr[0].x);
    float y_min_tmp=(float)(ptArr[0].y);
    float y_max_tmp=(float)(ptArr[0].y);

    for(int i = 0;i < ptArr.size(); i++)
    {
        if(ptArr[i].x < x_min_tmp)
            x_min_tmp = (float)(ptArr[i].x);
        if(ptArr[i].x > x_max_tmp)
            x_max_tmp = (float)(ptArr[i].x);
        if(ptArr[i].y < y_min_tmp)
            y_min_tmp = (float)(ptArr[i].y);
        if(ptArr[i].y > y_max_tmp)
            y_max_tmp = (float)(ptArr[i].y);
    }

    /*cout<<"x_min_tmp:" <<x_min_tmp <<endl;
        cout<<"x_max_tmp:" <<x_max_tmp <<endl;
            cout<<"y_min_tmp:" <<y_min_tmp <<endl;
                cout<<"y_max_tmp:" <<y_max_tmp <<endl;*/

    if(x_max_tmp-x_min_tmp>2*width&&y_max_tmp-y_min_tmp<height)
    {
        cout<<"col:"<<ptArr[ptArr.size() - 1].x-ptArr[0].x<<endl;
        if((ptArr[ptArr.size() - 1].x-ptArr[0].x) > 0)
        {
            result="Left";
        }
        else
        {
            result="Right";
        }
    }
    else if(x_max_tmp-x_min_tmp<width&&y_max_tmp-y_min_tmp>height)
    {
        cout<<"row:"<<ptArr[ptArr.size() - 1].y - ptArr[0].y<<endl;
        if((ptArr[ptArr.size() - 1].y - ptArr[0].y) > 0)
        {
            result="Down";
        }
        else
        {
            result="Up";
        }
    }
}

void handGesture::getCurrentFilePath()
{
    QString qstrpath = QApplication::applicationDirPath();
    sCurrentFilepPath = qstrpath.toStdString();
    if(!sCurrentFilepPath.empty())
    {
        printf("Directory is:%s\n", sCurrentFilepPath.c_str());
    }
}

QDir handGesture::SetFolderPath(int num)
{
    string target[GestureNum] =
    {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine","Ok", "Stop"};

    string targetdir = sCurrentFilepPath + "/images/SingleNums/" + target[num];
    //cout << targetdir << endl;

    QString filePathInfo = QString::fromStdString(targetdir);
    QDir dir(filePathInfo);
    if(dir.exists())
    {
         QStringList filters;
         filters<<QString("*.jpeg")<<QString("*.jpg")<<QString("*.png")<<QString("*.bmp");
         dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
         dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式（后缀为.jpeg等图片格式）
    }

    return dir;
}


void handGesture::saveImageWithDialog()
{
    QFileDialog fileDialog;
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);//set save model
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setViewMode(QFileDialog::Detail);//time,date..
    fileDialog.setGeometry(10,30,600,400);
    fileDialog.setDirectory(QFILEDIALOG_CURRENTPATH);
    fileDialog.setWindowTitle(QFILEDIALOG_SAVEIMAGE);
    fileDialog.setFilter(tr(QFILEDIALOG_SUPPORTTYPE));
    fileDialog.setOption(QFileDialog::DontConfirmOverwrite);
    if(fileDialog.exec() == QDialog::Accepted)
    {
        QString strFilePath = fileDialog.selectedFiles()[0];
        QString fileName = strFilePath +".jpg";
        if(fileName.isEmpty())
        {
            return;
        }
        else
        {
            cv::imwrite(fileName.toStdString().c_str(), captureframe);
            cout<<"save image sucess"<<endl;
        }
    }
}

void handGesture::on_pushButton_captureImage_clicked()
{
    timer->stop();//stop update frame
    cap>>captureframe;//capture the once frame
    //display in screen
    QImage dstImage=QImage((const uchar*)captureframe.data,captureframe.cols,captureframe.rows,QImage::Format_RGB888).rgbSwapped();
    dstImage = dstImage.scaled(320, 240);
    ui->label_cvtScreen->setPixmap(QPixmap::fromImage(dstImage));
    saveImageWithDialog();
    timer->start(DELAY_DISPLAY_INTERVAL);
}

void handGesture::on_pushButton_StartDrawing_clicked()
{
    centerArray.clear();
    EOperation = ESTARTDRAWING;
}

void handGesture::on_pushButton_ClearDrawing_clicked()
{
    EOperation = ECLEARDRAWING;
}

void handGesture::on_pushButton_startRecognize_clicked()
{
    EOperation = EDIGITRECOGNIZE;
    centerArray.clear();
}

void handGesture::on_pushButton_DirectionRecognize_clicked()
{
    EOperation = EDIRRECOGNIZE;
    centerArray.clear();
}
