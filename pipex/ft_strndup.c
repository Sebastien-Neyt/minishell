#include "pipex.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*copy;

	copy = malloc(sizeof(char) * (n + 1));
	if (copy == NULL)
		return (0);
	ft_strlcpy(copy, (char *)src, n + 1);
	return (copy);
}
