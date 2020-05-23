#include <iostream>
#include <fstream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"
#include <sstream>
#include <string.h>

using namespace cv;
using namespace std;
int main()
{
	int k;
	int tot_img_row, img_row, row_no;
	cin >> tot_img_row >> img_row>>row_no;
	bool try_use_gpu = false;
    Stitcher::Mode mode = Stitcher::SCANS;

    for(int i=1, k=1; i<tot_img_row*row_no;i=i+tot_img_row,k++)
    {
    	stringstream ss,ss1;
    	ss << k;
 		ss1 << i;
 		string path1 = "/home/atul/DeWinter/Video_Stitcher/" + ss1.str() + ".jpg" ;
 		Mat image1 = imread(path1);
 		vector <Mat> desk;	
 		desk.push_back(image1);
 		for(int j=i;j<i+img_row;j=j+1)
 		{
 			stringstream ss2;
 			ss2 << j;
 			string path2 = "/home/atul/DeWinter/Video_Stitcher/" + ss2.str() + ".jpg" ;
 			Mat image2 = imread(path2);
 			desk.push_back(image2);
 			Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
   	   	    Stitcher::Status status = stitcher->stitch(desk, image1);
   	   	    if (status != Stitcher::OK)	
			{
				cout << j;
				cout << "\nUnable to perform stitching...";
				cout << "\nError code: " << status;
				desk.clear();
				j=j+1;
			}	
			imwrite("image.jpg",image1);
			cout << j << endl;
 		}
	}
	return 0;
}
