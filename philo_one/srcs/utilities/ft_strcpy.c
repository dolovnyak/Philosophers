char	*ft_strcpy(char *dst, const char *src)
{
	int i;
	
	if (dst == src)
		return (dst);
	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}
