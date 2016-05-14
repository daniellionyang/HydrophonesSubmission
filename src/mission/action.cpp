#include "mission/action.hpp"

#include <thread>
#include <chrono>
#include <cmath>

#include "mission/command.hpp"
#include "mission/query.hpp"

Action::Action(FILE* in)
{
	// TODO: implement
}

size_t Action::write(FILE* out)
{
	// TODO: implement
	return 0;
}

bool Action::run(FILE* in, FILE* out)
{
	return m_function(in, out);
}

bool wait(FILE* in, FILE* out, float time)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(time * 1000)));
}

bool moveAbsolute(FILE* in, FILE* out, const State& target, float minDistance)
{
	bool close = false;
	while (!close)
	{
		State state = getState(in, out);

		move(out, state, target);

		if (state.distanceTo(target) < minDistance)
			close = true;
		else std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	stop(in, out);

	return true;
}

bool moveRelative(FILE* in, FILE* out, const State& diff, float minDistance)
{
	auto target = getState(in, out);

	target.setX(target.x() + diff.x());
	target.setY(target.y() + diff.y());
	target.setDepth(target.depth() + diff.depth());
	target.setYaw(target.yaw() + diff.yaw());
	target.setPitch(target.pitch() + diff.pitch());
	target.setRoll(target.roll() + diff.roll());

	return moveAbsolute(in, out, target, minDistance);
}

bool moveModel(FILE* in, FILE* out, int xi, int yi, int zi, float xo, float yo, float zo, float minDistance)
{
	bool close = false;
	while (!close)
	{
		State state = getState(in, out);
		float cx = state.x();
		float cy = state.y();
		float cz = state.depth();

		auto model = getModel(in, out);

		auto target = State(
			model.get(xi) + xo,
			model.get(yi) + yo,
			model.get(zi) + zo
		);

		move(out, state, target);

		if (state.distanceTo(target) < minDistance)
			close = true;
		else std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	stop(in, out);

	return true;
}

bool dropInBin(FILE* in, FILE* out)
{
	// maybe do stuff to aim here

	drop(out);

	wait(in, out, 1);

	return true;
}

bool uncoverBin(FILE* in, FILE* out)
{
	// maybe do stuff to aim here

	auto state = getState(in, out);
	auto target = state;

	target.setDepth(4.5);
	moveAbsolute(in, out, target, .1);

	grab(out);
	wait(in, out, 1);

	target.setDepth(4);
	target.setX(state.x() + 1);
	moveAbsolute(in, out, target, .1);

	release(out);
	wait(in, out, 1);

	moveAbsolute(in, out, state, .1);

	return true;
}

bool shootInHole(FILE* in, FILE* out, char side)
{
	// maybe do stuff to aim here

	shoot(out, side);

	wait(in, out, 1);

	return true;
}

bool uncoverHole(FILE* in, FILE* out)
{
	// maybe do stuff to aim here

	auto state = getState(in, out);
	auto target = state;

	grab(out);
	wait(in, out, 1);

	moveRelative(in, out, State(.3, .3, 0), .1);

	release(out);
	wait(in, out, 1);

	moveAbsolute(in, out, state, .1);

	return true;
}

