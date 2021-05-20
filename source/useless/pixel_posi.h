#pragma once 


struct pixel_posi
{
public:
	int x;
	int y;
	unsigned int raw_x;
	unsigned int raw_y;
	// constructing
	pixel_posi(unsigned int raw_xx, unsigned int raw_yy) :raw_x(raw_xx), raw_y(raw_yy)
	{
			x = raw_xx * 68 + 86;
			y = raw_yy * 67 + (raw_yy <= 4 ?46:62);
		
	};
	// end
	~pixel_posi()
	{

	};
};
