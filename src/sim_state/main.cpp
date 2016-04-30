#include <cstdio>
#include <chrono>
#include <thread>
#include <atomic>
#include <vector>

#include "common/state.hpp"

bool update(std::atomic<State>* state, std::atomic<State>* des)
{
	float dX = 1;
	float dY = 1;
	float dDepth = 1;
	float dYaw = 1;
	float dPitch = 1;
	float dRoll = 1;

	float freq = 30;

	while (true)
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
			case 'c': state->load().write(out); break;
			case 'd': des->load().write(out); break;
			case 's': des->store(State(in)); break;
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
		state->load().write(out);

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 / freq)));
	}

	return true;
}

int main()
{
	std::atomic<State> state(State(0,0,0,0,0,0));
	std::atomic<State> des(State(0,0,0,0,0,0));

	std::thread u(update, &state, &des);
	std::thread c(handleCPU, &state, &des);
	std::thread o(outputState, &state);

	u.join();
	c.join();
	o.join();

	return 0;
}

