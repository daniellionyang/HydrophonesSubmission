#include "common/config.hpp"

const Matrix initialModel =
{
	0,
	12,    0,
	17,    -3,     2,
	18,    0,      2,
	17.5,  -1.5,   2,
	24,    -3,
	18,    -10,
	17.4,  -10.3,
	19,    -11,
	0,
	3,
	18,    -10,
};

const Matrix initialVariance =
{
	1,
	4,     4,
	9,     9,     1,
	9,     9,     1,
	9,     9,     1,
	9,     9,
	9,     9,
	9,     9,
	9,     9,
	1,
	1,
	400,   400,
};

const Matrix varianceGrowth =
{
	0,
	.1,    .1,
	.1,    .1,    0,
	.1,    .1,    0,
	.1,    .1,    0,
	.1,    .1,
	.1,    .1,
	.1,    .1,
	.1,    .1,
	.1,
	.1,
};

const Matrix constants =
{
	4.8,
	3,
	30,    -15,
	4.5,
};

