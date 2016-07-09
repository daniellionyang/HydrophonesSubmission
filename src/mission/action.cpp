#include "mission/action.hpp"

#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>

#include "common/defs.hpp"
#include "common/config.hpp"
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

bool lprintf(FILE*, FILE*, const std::string str)
{
	std::cerr << str;
	return true;
}

bool wait(FILE* in, FILE* out, float time)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(time * 1000)));
	return true;
}

bool moveAbsolute(FILE* in, FILE* out, const State& target, float minDistance)
{
	setState(out, target);

	bool close = false;
	while (!close)
	{
		State state = getState(in, out);

		if (
			state.distanceTo(target) < minDistance     &&
			std::abs(state.yaw() - target.yaw()) < .02 &&
			true
		)
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

bool moveDir(FILE* in, FILE* out, const State& change, float minDistance)
{
	auto state = getState(in, out);
	
	auto dx = change.x() * std::cos((state.yaw() + change.yaw()) * 2 * M_PI)
			- change.y() * std::sin((state.yaw() + change.yaw()) * 2 * M_PI);
	auto dy = change.x() * std::sin((state.yaw() + change.yaw()) * 2 * M_PI)
			+ change.y() * std::cos((state.yaw() + change.yaw()) * 2 * M_PI);
	
	auto target = State(dx, dy, change.depth(), change.yaw(), change.pitch(), change.roll());
	
	return moveRelative(in, out, target, minDistance);
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

bool moveModelDir(FILE* in, FILE* out, int xi, int yi, int zi, float xo, float yo, float zo, float minDistance)
{
	auto target = State(xo, yo, zo, 0, 0, 0);
	return (moveModel(in, out, xi, yi, zi, 0, 0, 0, minDistance) 
		&& moveDir(in, out, target, minDistance));
}

bool dropInBin(FILE* in, FILE* out)
{
	drop(out);
	return true;
}

bool uncoverBin(FILE* in, FILE* out)
{
	auto state = getState(in, out);
	auto target = state;

	target.setDepth(constants.get(C_BIN_D));
	moveAbsolute(in, out, target, .1);

	grab(out);
	wait(in, out, 1);

	target.setX(state.x() + .6);
	moveAbsolute(in, out, target, .1);

	release(out);
	wait(in, out, 1);

	moveAbsolute(in, out, state, .1);

	return true;
}

bool shootInHole(FILE* in, FILE* out, char side)
{
	shoot(out, side);
	return true;
}

bool moveToHole(FILE* in, FILE* out, size_t xi, size_t yi, size_t di, float offset, float mindist)
{
	bool close = false;
	while (!close)
	{
		State state = getState(in, out);
		float cx = state.x();
		float cy = state.y();
		float cz = state.depth();

		auto model = getModel(in, out);

		float tx = model.get(xi);
		float ty = model.get(yi);
		float td = model.get(di);

		float theta = model.get(M_TORP_SKEW);

		auto target = State(
			model.get(xi) - offset*std::cos(theta * 2*M_PI),
			model.get(yi) - offset*std::sin(theta * 2*M_PI),
			model.get(di),
			theta,
			0,
			0
		);

		setState(out, target);

		if (state.distanceTo(target) < mindist)
			close = true;
		else std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	stop(in, out);

	return true;
}

bool flag(FILE* in, FILE* out, size_t idx, float value)
{
	setFlag(out, idx, value);
	return true;
}

bool variance(FILE* in, FILE* out, size_t idx, float value)
{
	addVariance(out, idx, value);
	return true;
}

