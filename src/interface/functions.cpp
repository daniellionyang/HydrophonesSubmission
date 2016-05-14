#include "interface/functions.hpp"

#include <utility>
#include <queue>
#include <thread>
#include <chrono>

#include "common/defs.hpp"
#include "common/matrix.hpp"
#include "common/state.hpp"
#include "image/image.hpp"
#include "model/evidence.hpp"
#include "model/system.hpp"

bool hydrophones(const std::string in_name, const std::string out_name, Data* data)
{
	FILE* in = NULL;
	FILE* out = NULL;

	while (!in) 
	{
		in = fopen(in_name.c_str(), "r");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	while (!out)
	{
		out = fopen(out_name.c_str(), "w");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	bool quit = false;
	while (!quit)
	{
		float theta, phi;
		fscanf(in, " h %f %f", &theta, &phi);

		float x = 0, y = 0, s = 1;

		// TODO: compute values

		data->lock();
			data->evidence.push(Evidence({
				{M_PINGER_X, x, s},
				{M_PINGER_Y, y, s},
			}));
		data->unlock();
	}

	return true;
}

bool buoys(const std::string in_name, const std::string out_name, Data* data)
{
	FILE* in = NULL;
	FILE* out = NULL;

	while (!in) 
	{
		in = fopen(in_name.c_str(), "r");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	while (!out)
	{
		out = fopen(out_name.c_str(), "w");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	uint32_t imageID = 0;

	bool quit = false;
	while (!quit)
	{
		bool newImage = false;
		cv::Mat img;
		data->lock();
			if (data->imageFrontID > imageID)
			{
				img = data->imageFront;
				imageID = data->imageFrontID;
				newImage = true;
			}
		data->unlock();

		if (newImage)
		{
			imageWrite(out, img);

			float // theta, phi, rho
				rt, rp, rr,
				gt, gp, gr,
				yt, yp, yr;

			fscanf(in, " %f %f %f %f %f %f %f %f %f",
				rt, rp, rr,
				gt, gp, gr,
				yt, yp, yr
			);

			float // x, y, depth, horizontal variance, depth variance
				rx, ry, rd, rhs, rds,
				gx, gy, gd, ghs, gds,
				yx, yy, yd, yhs, yds;

			// TODO: compute values

			data->lock();
				data->evidence.push(Evidence({
					{M_RBUOY_X, rx, rhs},
					{M_RBUOY_Y, ry, rhs},
					{M_RBUOY_D, rd, rds},
				}));
				data->evidence.push(Evidence({
					{M_GBUOY_X, gx, ghs},
					{M_GBUOY_Y, gy, ghs},
					{M_GBUOY_D, gd, gds},
				}));
				data->evidence.push(Evidence({
					{M_YBUOY_X, yx, yhs},
					{M_YBUOY_Y, yy, yhs},
					{M_YBUOY_D, yd, yds},
				}));
			data->unlock();
		}
	}

	return true;
}

bool bins(const std::string in_name, const std::string out_name, Data* data)
{
	FILE* in = NULL;
	FILE* out = NULL;

	while (!in) 
	{
		in = fopen(in_name.c_str(), "r");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	while (!out)
	{
		out = fopen(out_name.c_str(), "w");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	uint32_t imageID = 0;

	bool quit = false;
	while (!quit)
	{
		bool newImage = false;
		cv::Mat img;
		data->lock();
			if (data->imageDownID > imageID)
			{
				img = data->imageDown;
				imageID = data->imageDownID;
				newImage = true;
			}
		data->unlock();

		if (newImage)
		{
			imageWrite(out, img);

			float
				ox, oy,
				cx, cy;

			fscanf(in, " %f %f %f %f",
				ox, oy,
				cx, cy
			);

			// variance
			float cs = 0, os = 0;

			// TODO: compute variance
			// TODO: transform values so angle isn't linear with position

			data->lock();
				data->evidence.push(Evidence({
					{M_OBIN_X, ox, os},
					{M_OBIN_Y, oy, os},
				}));
				data->evidence.push(Evidence({
					{M_CBIN_X, cx, cs},
					{M_CBIN_Y, cy, cs},
				}));
			data->unlock();
		}
	}

	return true;
}
bool camera_f(const std::string in_name, const std::string out_name, Data* data)
{
	FILE* in = NULL;
	FILE* out = NULL;

	while (!in) 
	{
		in = fopen(in_name.c_str(), "r");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	while (!out)
	{
		out = fopen(out_name.c_str(), "w");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	bool quit = false;
	while (!quit)
	{
		fprintf(out, "i\n"); // request image
		fflush(out);
		auto img = imageRead(in); // read image

		// store image
		data->lock();
			data->imageFront = std::move(img);
			data->imageFrontID++;
		data->unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return true;
}

bool camera_d(const std::string in_name, const std::string out_name, Data* data)
{
	FILE* in = NULL;
	FILE* out = NULL;

	while (!in) 
	{
		in = fopen(in_name.c_str(), "r");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	while (!out)
	{
		out = fopen(out_name.c_str(), "w");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	bool quit = false;
	while (!quit)
	{
		fprintf(out, "i\n"); // request image
		fflush(out);
		auto img = imageRead(in); // read image

		// store image
		data->lock();
			data->imageDown = std::move(img);
			data->imageDownID++;
		data->unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return true;
}

bool mission(const std::string in_name, const std::string out_name, Data* data)
{
	FILE* in = NULL;
	FILE* out = NULL;

	while (!in) 
	{
		in = fopen(in_name.c_str(), "r");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	while (!out)
	{
		out = fopen(out_name.c_str(), "w");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	bool quit = false;
	while (!quit)
	{
		char m;
		fscanf(in, " %c", &m);
		switch (m)
		{
			case 'q': // query
			{
				char q;
				fscanf(in, " %c", &q);
				switch (q)
				{
					case 's': // state
					{
						data->lock();
							auto state = data->state;
						data->unlock();

						state.write(out);
						fflush(out);
						break;
					}
					case 'i': // image
					{
						char i;
						fscanf(in, " %c", &i);
						switch (i)
						{
							case 'f': // front
							{
								data->lock();
									auto img = data->imageFront;
								data->unlock();

								imageWrite(out, img);
								fflush(out);
								break;
							}
							case 'd': // down
							{
								data->lock();
									auto img = data->imageDown;
								data->unlock();

								imageWrite(out, img);
								fflush(out);
								break;
							}
						}
						break;
					}
					case 'm': // modeling
					{
						char m;
						fscanf(in, " %c", &m);
						switch (m)
						{
							case 'm': // mode
							{
								data->lock();
									auto model = data->model;
								data->unlock();

								model.write(out);
								fflush(out);
								break;
							}
							case 's': // system
							{
								System().write(out); // currently unsupported
								fflush(out);
								break;
							}
							case 'c': // certainty
							{
								fprintf(out, "0\n"); // currently unsupported
								fflush(out);
								break;
							}
						}
						break;
					}
				}
				break;
			}
			case 'c': // command
			{
				char c;
				fscanf(in, " %c", &c);
				switch(c)
				{
					case 's': // state
					{
						auto state = State(in);
						data->lock();
							data->desiredState = std::move(state);
							data->setState = true;
						data->unlock();
						break;
					}
					case 'd': // dropper
						data->lock();
							data->drop = true;
						data->unlock();
						break;
					case 'g': // grabber
					{
						char g;
						fscanf(in, " %c", &g);
						switch (g)
						{
							case 'g': // grab
								data->lock();
									data->grab = true;
								data->unlock();
								break;
							case 'r': // release
								data->lock();
									data->release = true;
								data->unlock();
								break;
						}
						break;
					}
					case 't': // torpedo
					{
						char t;
						fscanf(in, " %c", &t);
						data->lock();
							data->shoot = t;
						data->unlock();
						break;
					}
				}
				break;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return true;
}

bool modeling(const std::string in_name, const std::string out_name, Data* data)
{
	FILE* in = NULL;
	FILE* out = NULL;
	FILE* config = NULL;

	while (!in) 
	{
		in = fopen(in_name.c_str(), "r");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	while (!out)
	{
		out = fopen(out_name.c_str(), "w");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	while (!config)
	{
		config = fopen("config/initial_model.conf", "r");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	int c;
	while ((c = fgetc(config)) != EOF)
		fputc(c, out);
	fflush(out);

	bool quit = false;
	while (!quit)
	{
		fprintf(out, "m\n"); // request model
		fflush(out);
		auto model = Matrix(in); // read model

		std::queue<Evidence> evidence;
		// store model and get new evidences
		data->lock();
			data->model = std::move(model);
			data->modelID++;
			std::swap(evidence, data->evidence);
		data->unlock();

		// send new evidence
		while (!evidence.empty())
		{
			fprintf(out, "e\n");
			evidence.front().write(out);
			evidence.pop();
		}
		fflush(out);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return true;
}

bool control(const std::string in_name, const std::string out_name, Data* data)
{
	FILE* in = NULL;
	FILE* out = NULL;

	while (!in) 
	{
		in = fopen(in_name.c_str(), "r");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	while (!out)
	{
		out = fopen(out_name.c_str(), "w");
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	bool quit = false;
	while (!quit)
	{
		fprintf(out, "c\n"); // request state
		fflush(out);
		auto state = State(in); // read state

		State desiredState;
		bool setState, drop, grab, release;
		char shoot;
		// store state and get new commands
		data->lock();
			data->state = std::move(state);
			data->stateID++;

			std::swap(desiredState, data->desiredState);
			setState = data->setState;
			data->setState = false;
			shoot = data->shoot;
			data->shoot = false;
			drop = data->drop;
			data->drop = false;
			grab = data->grab;
			data->grab = false;
			release = data->release;
			data->release = false;
		data->unlock();

		// send commands to arduino
		if (setState)
		{
			fprintf(out, "s\n");
			desiredState.write(out);
			fflush(out);
		}

		if (shoot == 'r') fprintf(out, "t r\n");
		if (shoot == 'l') fprintf(out, "t l\n");

		if (drop) fprintf(out, "d\n");
		if (grab) fprintf(out, "g\n");
		if (release) fprintf(out, "r\n");

		fflush(out);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return true;
}

