#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <flycapture/FlyCapture2.h>
#include <cstdio>
#include <iomanip>
#include <thread>
#include <chrono>

#include "image/image.hpp"

int startCamera(FILE* in, FILE* out, FILE* log, FlyCapture2::PGRGuid guid)
{
	FlyCapture2::Error error;
	FlyCapture2::Camera cam;

	// connect
	error = cam.Connect(&guid);
	if (error != FlyCapture2::PGRERROR_OK)
	{
		error.PrintErrorTrace();
		return 1;
	}

	// set mode (pixel format, fps)
	FlyCapture2::Format7ImageSettings format;
	unsigned int packetSize;
	float percentage;
	error = cam.GetFormat7Configuration(&format, &packetSize, &percentage);
	if (error != FlyCapture2::PGRERROR_OK)
	{
		error.PrintErrorTrace();
		return 1;
	}

	format.mode = FlyCapture2::MODE_1;
	format.offsetX = 0;
	format.offsetY = 0;
	format.width = 644;
	format.height = 482;
	format.pixelFormat = FlyCapture2::PIXEL_FORMAT_RGB8;
	bool valid;
	FlyCapture2::Format7PacketInfo packetInfo;
	error = cam.ValidateFormat7Settings(&format, &valid, &packetInfo);
	if (error != FlyCapture2::PGRERROR_OK)
	{
		error.PrintErrorTrace();
		return 1;
	}

	error = cam.SetFormat7Configuration(&format, packetInfo.recommendedBytesPerPacket);
	if (error != FlyCapture2::PGRERROR_OK)
	{
		error.PrintErrorTrace();
		return 1;
	}

	error = cam.GetFormat7Configuration(&format, &packetSize, &percentage);
	if (error != FlyCapture2::PGRERROR_OK)
	{
		error.PrintErrorTrace();
		return 1;
	}

	// start capturing
	error = cam.StartCapture();
	if (error != FlyCapture2::PGRERROR_OK)
	{
		error.PrintErrorTrace();
		return 1;
	}

	FlyCapture2::Image fcImage;
	bool quit = false;
	while (!quit)
	{
		// wait for image request
		char c;
		fscanf(in, " %c ", &c);
		switch (c)
		{
			case 'i':
			{
				// get image
				error = cam.RetrieveBuffer(&fcImage);
				if (error != FlyCapture2::PGRERROR_OK)
				{
					fprintf(log, "error: getting image\n");
					error.PrintErrorTrace();
					continue;
				}

				// convert
				FlyCapture2::Image bgr;
				error = fcImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &bgr);
				if (error != FlyCapture2::PGRERROR_OK)
				{
					fprintf(log, "error: converting image\n");
					error.PrintErrorTrace();
					continue;
				}

				// convert to opencv mat
				cv::Mat image(bgr.GetRows(), bgr.GetCols(), CV_8UC3, bgr.GetData(), bgr.GetStride());

				// send image
				imageWrite(out, image);
			}

			case 'q': quit = true; break;
		}

		// wait a bit
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	// stop capturing
	error = cam.StopCapture();
	if (error != FlyCapture2::PGRERROR_OK)
	{
		error.PrintErrorTrace();
		return 1;
	}

	// disconnect
	error = cam.Disconnect();
	if (error != FlyCapture2::PGRERROR_OK)
	{
		error.PrintErrorTrace();
		return 1;
	}

	return 0;
}

int main(int argc, char** argv)
{
	FlyCapture2::Error error;

	FlyCapture2::BusManager busMgr;
	unsigned int numCameras;
	error = busMgr.GetNumOfCameras(&numCameras);
	if (error != FlyCapture2::PGRERROR_OK)
	{
		error.PrintErrorTrace();
		return 1;
	}

	if (numCameras < 1)
	{
		fprintf(stderr, "error: no camera detected\n");
		return 1;
	}

	FlyCapture2::PGRGuid guid;
	error = busMgr.GetCameraFromIndex(0, &guid);
	if (error != FlyCapture2::PGRERROR_OK)
	{
		error.PrintErrorTrace();
		return 1;
	}

	startCamera(stdin, stdout, stderr, guid);

	return 0;
}
