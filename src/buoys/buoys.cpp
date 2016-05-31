#include "buoys/buoys.hpp"
#include "image/image.hpp"
#include "model/evidence.hpp"

//Creates an equalized distribution of certain colors
//Read more at http://docs.opencv.org/2.4/doc/tutorials/imgproc/histograms/histogram_equalization/histogram_equalization.html
cv::Mat equalColorHist(cv::Mat& img, bool red, bool green, bool blue)
{
	std::vector<cv::Mat> channels;
	cv::split(img, channels);

	if(blue)
	{
		cv::equalizeHist(channels[0], channels[0]);
	}
	if(green)
	{
		cv::equalizeHist(channels[1], channels[1]);
	}
	if(red)
	{
		cv::equalizeHist(channels[2], channels[2]);
	}

	cv::Mat result;
	cv::merge(channels, result);
	return result;
}

//Turns the mat into a diffmap (make each pixel the difference between it and its neighbors)
//Useful because the water near the top usually looks like the green buoys near the bottom
cv::Mat generateDiffMap(cv::Mat& img, int diff)
{
	cv::Mat diffMap = cv::Mat(img.size(), CV_32F, cv::Scalar(0));

	float* ip = img.ptr<float>();
	float* op = diffMap.ptr<float>();

	for (int c = diff; c < img.cols - diff; c++)
	{
		for (int r = diff; r < img.rows - diff; r++)
		{
			// make the value equal to how much it stands out from its\
				horizontal or vertical neighbors, whichever is less
			float vert = (2*ip[(r*img.cols+c)]-ip[((r-diff)*img.cols+c)]-ip[((r+diff)*img.cols+c)]);
			float hori = (2*ip[(r*img.cols+c)]-ip[(r*img.cols+c+diff)]-ip[(r*img.cols+c-diff)]);
			float weak = (std::abs(vert) < std::abs(hori)) ? vert : hori;
			op[r*img.cols+c] = weak;
		}
	}
 
	return diffMap;
}
	
int main(int argc, char** argv)
{
	char ch = fgetc(stdin);
	while(ch != 'q')
	{
		//Obtain image from the front camera.
		cv::Mat image = imageRead(stdin);
	
		if(!image.data)
		{
			std::cout << "0\n";
			return -1;
		}

		//Initialize evidence variables 
		std::vector<Variable> buoy_evidence_variables;
		for(int i = 0; i < 9; i++)
		{
			buoy_evidence_variables.push_back(Variable()); 
			buoy_evidence_variables[i].index = i;
		}
				
		Evidence buoy_evidence(buoy_evidence_variables);	
	 
		//Reset processedImage and define the image size
		cv::Mat processedImage; 
		processedImage.create(360, 640, CV_8UC3);
		memset(processedImage.ptr(), 100, processedImage.rows*processedImage.cols*3);
		int image_size = image.rows*image.cols;

		//Crop and resize image
		cv::resize(image(cv::Rect(image.cols*(1-cropx)/2, image.rows*(1-cropy-offset)/2, 
					image.cols*cropx, image.rows*cropy)), image, 
				cv::Size(image.cols*cropx*scalex, image.rows*cropy*scaley));

		//Create temporabuoy_evidence_variables[RY].value image to store lower smaller processed image
		cv::Mat output(image.rows, image.cols, CV_8UC3, cv::Scalar(0, 0, 0));
		unsigned char* op = output.ptr();

		cv::Mat imgR, imgG, imgY;
		imgR.create(image.rows, image.cols, CV_8UC1);
		imgG.create(image.rows, image.cols, CV_8UC1);
		imgY.create(image.rows, image.cols, CV_8UC1);

		unsigned char* rPtr = imgR.ptr(), *gPtr = imgG.ptr(), *yPtr = imgY.ptr();

		const unsigned char* ip = image.ptr();

		//Filter for green
		cv::Mat grMat(image.size(), CV_32F, cv::Scalar(0));
		cv::Mat reMat(image.size(), CV_32F, cv::Scalar(0));
		float* gp = grMat.ptr<float>();
		float* rp = reMat.ptr<float>();
		cv::Mat histo = equalColorHist(image, false, false, false);
		unsigned char* hp = histo.ptr();
		for (int i = 0; i < image.rows*image.cols; i++)
		{
			int b = hp[3*i], g = hp[3*i+1], r = (int)hp[3*i+2];
			//gp[i] = 40.0*(g-0.4*r)/(b+3.0*r+10.1);
			gp[i] = (g+0.4*r)/(b+0.7*r+3.01)-0.004*r;
			rp[i] = 70.0*r/(g+1.0) - 120.0*g/(b+1.0)-(g+b)*0.1;
		}
	 
		cv::Mat diMap = generateDiffMap(grMat, diffDist);
		cv::Mat drMap = generateDiffMap(reMat, diffDist);

		cv::blur(diMap, diMap, cv::Size(3,3));

		float* drffp = drMap.ptr<float>();
		float* diffp = diMap.ptr<float>();

		float maxR[4] = {-1000, 0, 0, 1000};
		int maxY[3] = {-1};
		float maxG[4] = {-1000, 0, 0, 1000};
		for (int i = 0; i < image.cols*image.rows; i++)
		{
			int b = ip[3*i], g = ip[3*i+1], r = (int)ip[3*i+2];
			
			op[3*i+2] = drffp[i]/10+128;

			//Filter for red
			if (drffp[i] > maxR[0])
			{
				maxR[0] = drffp[i];
				maxR[1] = i % image.cols;
				maxR[2] = i / image.cols;
			}
			if (drffp[i] < maxR[3])
			{
				maxR[3] = drffp[i];
			}

			//Filter for yellow
			yPtr[i] = std::max(0, std::min(255, 128+(r+g-b)/4));
			op[3*i] = yPtr[i];

			//Find yellow buoy
			if (yPtr[i] > maxY[0])
			{
				maxY[0] = yPtr[i];
				maxY[1] = i % image.cols;
				maxY[2] = i / image.cols;
			}

			op[3*i+1] = diffp[i]+128;
			//Find green buoy and max/min values
			if (diffp[i] > maxG[0])
			{
				maxG[0] = diffp[i];
				maxG[1] = i % image.cols;
				maxG[2] = i / image.cols;
			}
			if (diffp[i] < maxG[3])
			{
				maxG[3] = diffp[i];
			}
		}
		buoy_evidence_variables[RX].value = (int)maxR[1];
		buoy_evidence_variables[RY].value = (int)maxR[2];
		buoy_evidence_variables[YX].value = maxY[1];
		buoy_evidence_variables[YY].value = maxY[2];
		buoy_evidence_variables[GX].value = (int)maxG[1];
		buoy_evidence_variables[GY].value = (int)maxG[2];
		
		if(ch == 'i')
		{
			//Highlight buoys on processed image
			op[(int)(3*(buoy_evidence_variables[RY].value*image.cols+buoy_evidence_variables[RX].value))] = 0;
			op[(int)(3*(buoy_evidence_variables[RY].value*image.cols+buoy_evidence_variables[RX].value))+1] = 0;
			op[(int)(3*(buoy_evidence_variables[GY].value*image.cols+buoy_evidence_variables[GX].value))] = 0;
			op[(int)(3*(buoy_evidence_variables[GY].value*image.cols+buoy_evidence_variables[GX].value))+2] = 0;
			op[(int)(3*(buoy_evidence_variables[YY].value*image.cols+buoy_evidence_variables[YX].value))+1] = 0;
			op[(int)(3*(buoy_evidence_variables[YY].value*image.cols+buoy_evidence_variables[YX].value))+2] = 0;
			op[(int)(3*(buoy_evidence_variables[GY].value*image.cols+buoy_evidence_variables[GX].value))+1] = 255;
			op[(int)(3*(buoy_evidence_variables[RY].value*image.cols+buoy_evidence_variables[RX].value))+2] = 255;
			op[(int)(3*(buoy_evidence_variables[YY].value*image.cols+buoy_evidence_variables[YX].value))] = 255;
		
			// resize filtered image for processed image
			cv::resize(output, processedImage(cv::Rect(processedImage.cols*(1-cropx)/2, processedImage.rows*(1-cropy-offset)/2, 
					processedImage.cols*cropx, processedImage.rows*cropy)), 
					cv::Size(processedImage.cols*cropx, processedImage.rows*cropy), 0, 0, cv::INTER_NEAREST);
			
			imageWrite(stdout, output);
		}
		
		else if(ch == 'e')
		{
			buoy_evidence_variables[RX].value = (buoy_evidence_variables[RX].value - image.cols/2) / image.cols;
			buoy_evidence_variables[RY].value = (image.rows/2 - buoy_evidence_variables[RY].value) / image.rows;
			buoy_evidence_variables[RZ].value = 1;
			buoy_evidence_variables[GX].value = (buoy_evidence_variables[GX].value - image.cols/2) / image.cols;
			buoy_evidence_variables[GY].value = (image.rows/2 - buoy_evidence_variables[GY].value) / image.rows+offset;
			buoy_evidence_variables[GZ].value = 1;
			buoy_evidence_variables[YX].value = (buoy_evidence_variables[YX].value - image.cols/2) / image.cols;
			buoy_evidence_variables[YY].value = (image.rows/2 - buoy_evidence_variables[YY].value) / image.rows;
			buoy_evidence_variables[YZ].value = 1;

			buoy_evidence.write(stdout);
		}
		
		ch = fgetc(stdin);
	}
		 
	return 0;
}
