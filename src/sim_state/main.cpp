#include <cstdio>
#include <chrono>
#include <thread>
#include <atomic>
#include <vector>
#include <ctime>

#include "common/state.hpp"

std::atomic<bool> alive;

bool update(std::atomic<State>* state, std::atomic<State>* des, int delay)
{
	float dX = .6;
	float dY = .6;
	float dDepth = 1;
	float dYaw = 1;
	float dPitch = 1;
	float dRoll = 1;

	float freq = 5;

	clock_t base = clock();

	while (true)
	{
		alive = delay == -1 ? true : (clock() - base)/delay % 2 ? false : true;
		if(alive)
		{
			auto st = state->load();
			auto d = des->load();

			auto ud = [=](float curr, float targ, float speed)
			{
				float v = speed / freq;
				float dist = targ - curr;
				if (dist < v && dist > -v) // close enough
					return targ;
				else return curr + v * (dist > 0 ? 1 : -1);
			};

			state->store(State(
				ud(st.x(), d.x(), dX),
				ud(st.y(), d.y(), dY),
				ud(st.depth(), d.depth(), dDepth),
				ud(st.yaw(), d.yaw(), dYaw),
				ud(st.pitch(), d.pitch(), dPitch),
				ud(st.roll(), d.roll(), dRoll)
			));

		}
		else {state->store(State(0, 0, 0, 0, 0, 0));}

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 / freq)));
	}

	return true;
}

bool handleCPU(std::atomic<State>* state, std::atomic<State>* des)
{

	float freq = 100;

	FILE* in = stdin;
	FILE* out = stdout;

	while (true)
	{
		int c = fgetc(in);
		switch (c)
		{
			case 'a': fprintf(out, "%i\n", alive ? 1 : 0); fflush(out); break;
			case 'c': state->load().write(out); break;
			case 's': des->store(State(in)); break;
			case 't':
			{
				char s;
				fscanf(in, " %c", &s);
				break;
			}
			case 'd': break;
			case 'g': break;
			case 'r': break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 / freq)));
	}

	return true;
}

bool outputState(std::atomic<State>* state)
{
	float freq = 8;
	FILE* out = fopen("pipe/sim_in", "w");

	while (true)
	{
		if(alive)
		{
			state->load().write(out);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 / freq)));
	}

	return true;
}

int main(int argc, char **argv)
{
	int delay = -1;
	if(argc == 2) {delay = atoi(argv[1]);}

	alive = true;

	std::atomic<State> state(State(0,0,0,0,0,0));
	std::atomic<State> des(State(0,0,0,0,0,0));

	std::thread u(update, &state, &des, delay);
	std::thread c(handleCPU, &state, &des);
	std::thread o(outputState, &state);

	u.join();
	c.join();
	o.join();

	return 0;
}

