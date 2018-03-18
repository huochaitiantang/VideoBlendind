#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/photo.hpp>
#include <opencv2/imgcodecs.hpp>

#include "algorithms.h"

using namespace cv;
using namespace std;


void img_fusion_to_video(Mat &roi_front, Mat &mask, Rect b_roi, int fusion_type){
	VideoCapture vcap;
	string input_file("1.mp4");
	string output_file("out.mp4");

	cout << "Handle for video " << input_file << endl;
	if(!vcap.open(input_file)){
		cout << "ERROR in open file "<< input_file << endl;
	}

	long total_frame = vcap.get(CV_CAP_PROP_FRAME_COUNT);
	int width = vcap.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = vcap.get(CV_CAP_PROP_FRAME_HEIGHT);
 	double rate=vcap.get(CV_CAP_PROP_FPS);
	cout << " Total Frame: " << total_frame << " Width:" << width << " Height: " << height << " Frame Rate:" << rate << endl;

 	Size videoSize(width, height);
	VideoWriter writer;
	writer.open(output_file, CV_FOURCC('M','J','P','G'), rate, videoSize);

        int frame_id = 0;
	Mat img;
	while(vcap.read(img)){
                cout << "Handle for frame [" << frame_id << "/" << total_frame << "]"<<endl;
		Mat new_img = getFusionMat(img, roi_front, mask, b_roi, fusion_type);
		writer << new_img;
		//imshow("img.jpg", new_img);
		//imwrite("img.jpg", new_img);
		//return;
		frame_id += 1;

	}
}

int main (int argc, char **argv)
{	

	Rect b_roi, f_roi;		
	b_roi = Rect(800, 150, 100, 100);
	f_roi = Rect(160, 40, 150, 150);

	char back_name[128] = "mountain.jpg";
	char front_name[128] = "moon.jpg";
        char blend_name[128] = "moon_mountain.jpg";

	Mat back = imread(back_name, CV_LOAD_IMAGE_COLOR);
	Mat front = imread(front_name, CV_LOAD_IMAGE_COLOR);

	if ( !back.data || !front.data ){
		cout << "No Image Data!" << endl;
		return 0;
	}

	//resize the roi of the front img
	Mat roi_front;
	Rect roi(0, 0, b_roi.width, b_roi.height);
	front(f_roi).copyTo(roi_front);
	resize(roi_front, roi_front, roi.size());

	Mat mask = 255 * Mat::ones( roi_front.rows, roi_front.cols, roi_front.depth() );
        Mat new_back = getFusionMat(back, roi_front, mask, b_roi, 0);
	//imshow("poisson", new_back);
        imwrite(blend_name, new_back);

	Rect video_b_roi = Rect(200, 500, 100, 100);
	img_fusion_to_video(roi_front, mask, video_b_roi, 0);
	

	waitKey(0);
	return 0;
}
