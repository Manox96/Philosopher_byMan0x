#include "philosopher.h"
#include <stdio.h>

int main(int ac, char **av)
{
	t_data data;
	
	if (ac != 5 && ac != 6)
		print_err("should be 5 or 4 args");
	initial_inputs(&data, ac, av);
	// start_sumilation(&data);
	puts("ok");

}