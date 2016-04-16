#include "interface/functions.hpp"

#include <utility>
#include <queue>
#include <thread>
#include <chrono>

#include "common/matrix.hpp"
#include "common/state.hpp"
#include "image/image.hpp"
#include "model/system.hpp"

bool camera_f(FILE* in, FILE* out, Data* data)
{
	bool quit;
	while (!quit)
	{
		fprintf(out, "i\n"); // request image
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

bool camera_d(FILE* in, FILE* out, Data* data)
{
	bool quit;
	while (!quit)
	{
		fprintf(out, "i\n"); // request image
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

bool mission(FILE* in, FILE* out, Data* data)
{
	bool quit;
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
								break;
							}
							case 'd': // down
							{
								data->lock();
									auto img = data->imageDown;
								data->unlock();

								imageWrite(out, img);
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
								break;
							}
							case 's': // system
							{
								System().write(out); // currently unsupported
								break;
							}
							case 'c': // certainty
							{
								fprintf(out, "0\n"); // currently unsupported
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

bool modeling(FILE* in, FILE* out, Data* data)
{
	bool quit;
	while (!quit)
	{
		fprintf(out, "m\n"); // request model
		auto model = Matrix(in); // read model

		std::queue<System> evidence;
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

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return true;
}

bool control(FILE* in, FILE* out, Data* data)
{
	bool quit;
	while (!quit)
	{
		fprintf(out, "g\n"); // request state
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
		}

		if (shoot == 'r') fprintf(out, "t r\n");
		if (shoot == 'l') fprintf(out, "t l\n");

		if (drop) fprintf(out, "d\n");
		if (grab) fprintf(out, "g\n");
		if (release) fprintf(out, "r\n");

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return true;
}

