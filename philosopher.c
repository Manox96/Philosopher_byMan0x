#include "philosopher.h"

int main(int ac, char **av)
{

	if (ac != 5 && ac != 6)
	{
		perror("should be 5 or 4 args");
		return (0);
	}
	if (!(checkOnly_num(av)))
		return (0);
	
	puts("ok");


}