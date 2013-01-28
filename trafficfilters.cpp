#include <stdio.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "stdlib.h"
using namespace std;
#include <iostream>
#define  TPL_WIDTH       50      /* template width       */
#define  TPL_HEIGHT      50
FILE *fp;CvScalar sum;
char str[6]={0};
void mouseHandler( int event, int x, int y, int flags, void *param );
IplImage *frame,*tpl,*imggray;CvCapture  *capture,*capture1;
int  object_x0, object_y0,posx=0,posy=0;int key,totframe,sum1[1000]={0},tmpnum=0;int *jok;
//int jok=(int*)sum1[1];
int main(){
   capture = cvCaptureFromFile( "traffic5.mpg" );
   capture1=cvCaptureFromFile( "traffic5.mpg" );
   int fps = ( int )cvGetCaptureProperty( capture, 5 );
   if( !capture ) {return 1;}
   tpl = cvQueryFrame( capture1 );
   frame = cvQueryFrame( capture );
   //tpl = cvCreateImage( cvSize( TPL_WIDTH, TPL_HEIGHT ),frame->depth, frame->nChannels );
   cvNamedWindow( "video", CV_WINDOW_AUTOSIZE );
   cvSetMouseCallback( "video", mouseHandler, NULL );
   cvShowImage("video",frame);
   cvWaitKey(3000);
   //cvWaitKey(1000);
 if (posx != 0){
  while (tmpnum < 1000){

   imggray = cvCreateImage( cvGetSize( tpl ), IPL_DEPTH_8U, 1);
   tpl = cvQueryFrame( capture1 );
   frame = cvQueryFrame( capture );
   cvCvtColor( tpl, imggray, CV_RGB2GRAY );
   sum=cvSum(imggray);
   sum1[tmpnum]=sum.val[0];
    //sum1[tmpnum]=456;
   totframe = (int)cvGetCaptureProperty(capture,7);
   cvRectangle( frame,cvPoint( posx, posy ),cvPoint( posx + TPL_WIDTH,posy + TPL_HEIGHT ),cvScalar( 0, 255, 0, 0 ), 1, 0, 0 );
   //cvShowImage( "video", frame );
   cvShowImage( "video", frame );
   tmpnum = tmpnum+1;
   if ( !frame ) return 1;
   if (key == 'q') break;
   if (tmpnum == 999){
     fp = fopen("test","w"); /* open for writing */
     for (int i = 0; i < 999; i++){
         //jok = (int*)(sum1[i]);
        //snprintf(str, sizeof(str), "%d",sum1[i]);
     	fprintf(fp," %d\n",sum1[i] );
     }
     fclose(fp);
     system("gnuplot input");
   }
  key=cvWaitKey(200/fps);
  //   	printf("%c\n",str[1]);
  }
      /* close the file before ending program */

 }
 return 0;

}



void mouseHandler( int event, int x, int y, int flags, void *param )
{
        if( event == CV_EVENT_LBUTTONUP ) {
        object_x0 = x - ( TPL_WIDTH  / 2 );
        object_y0 = y - ( TPL_HEIGHT / 2 );
        posx=object_x0;
        posy=object_y0;
        cvSetImageROI( tpl,cvRect( object_x0,object_y0,TPL_WIDTH,TPL_HEIGHT ) );
        //cvResetImageROI( frame );
        cvRectangle( frame,cvPoint( posx, posy ),cvPoint( posx + TPL_WIDTH,posy + TPL_HEIGHT ),cvScalar( 0, 255, 0, 0 ), 1, 0, 0 );
        cvShowImage( "video", frame );
        }
}
 
