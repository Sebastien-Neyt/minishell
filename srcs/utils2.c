#include "../includes/minishell.h"

/*
static size_t	ft_wordcounter(char *s, char c)
{
	size_t			count;
	unsigned int	x;

	x = 0;
	count = 0;
	while (s[x])
	{
		while (s[x] && s[x] == c)
			x++;
		if (s[x])
			count++;
		while (s[x] && s[x] != c)
			x++;
	}
	return (count);
}

static void	ft_free_all(char **ans)
{
	unsigned int	i;

	i = 0;
	while (ans[i])
	{
		free(ans[i]);
		i++;
	}
	free(ans);
}

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, char const *src, size_t maxlen)
{
	size_t	srclen;
	size_t	count;

	srclen = ft_strlen(src);
	if (maxlen == 0)
		return (srclen);
	count = 0;
	while (count < maxlen - 1 && *(src + count))
	{
		*(dst + count) = *(src + count);
		count++;
	}
	*(dst + count) = '\0';
	return (srclen);
}

static int	ft_wordmalloc(char *s, char c, size_t amount, char **ans)
{
	size_t	i;
	size_t	x;
	size_t	len;

	i = 0;
	x = 0;
	while (s[i] && x < amount)
	{
		len = 0;
		if (s[i] != c)
		{
			while (s[i + len] != c && s[i + len])
				len++;
			ans[x] = malloc(sizeof(char) * (len + 1));
			if (!ans[x])
				return (0);
			ft_strlcpy(ans[x], (s + i), (len + 1));
			x++;
		}
		i += (1 + len);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ans;
	size_t	amount;

	if (s == 0)
		return (0);
	amount = ft_wordcounter((char *)s, c);
	ans = (char **)malloc(sizeof(char *) * (amount + 1));
	if (!ans)
		return (0);
	ans[amount] = 0;
	if (!ft_wordmalloc((char *)s, c, amount, ans))
	{
		ft_free_all(ans);
		return (0);
	}	
	return (ans);
}
*/
char	*ft_strdupv2(char *s1)
{
	size_t	len;
	char	*dupe;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	dupe = (char *)malloc((len + 1) * sizeof(char));
	if (!dupe)
		return (0);
	while (i < len)
	{
		dupe[i] = s1[i];
		i++;
	}
	dupe[i] = '\0';
	return (dupe);
}
