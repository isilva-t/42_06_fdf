#include "fdf.h"

int	is_pt_inside_window(t_pt pt)
{
	if (pt.y < HEIGHT && pt.y >= 0
		&& pt.x >= 0 && pt.x < WIDTH)
		return (TRUE);
	return (FALSE);
}
