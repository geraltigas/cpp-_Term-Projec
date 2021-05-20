#pragma once

namespace utils
{
	struct vector
	{
	public:
		int delta_x;
		int delta_y;
		vector(int x, int y) :delta_x(x), delta_y(y)
		{
		};
	};
}

