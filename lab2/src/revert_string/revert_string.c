#include "revert_string.h"
#include <string.h>

void RevertString(char *str)
{
	size_t len = strlen(str);

	char tmp;
	for (size_t  i = 0; i < len/2; i++) 
	{
		tmp = str[len - i - 1];
		str[len - i - 1] = str[i];
		str[i] = tmp;
	}
}

