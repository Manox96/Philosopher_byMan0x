#include "philosopher.h"
#include <stdio.h>

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_err(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, my_strlen(str));
	exit(1);
}


int	my_atoi(char *str)
{
	int			i;
	long		s;
	long		r;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - '0';
		if ((r * s) > INT_MAX || (r * s) < INT_MIN)
			print_err("the number should be MIN_INT < numer < MAX_INT");
		i++;
	}
	return (s * r);
}
void handle_mtx_err(int status, t_type type)
{
	if (status == 0)
		return;
	else if (EINVAL == status && (type == LOCK || type == UNLOCK || type == DESTROY))
		print_err("Mutex Err");
	else if (EDEADLK == status || EPERM == status || ENOMEM == status || EBUSY == status)
		print_err("Mutex Err");
}

void	handle_mutex(t_type type, pthread_mutex_t *mtx)
{
	if (type == LOCK)
		handle_mtx_err(pthread_mutex_lock(mtx), type);
	else if (type == UNLOCK)
		handle_mtx_err(pthread_mutex_unlock(mtx), type);
	else if (type == INIT)
		handle_mtx_err(pthread_mutex_init(mtx, NULL), type);
	else if (type == DESTROY)
		handle_mtx_err(pthread_mutex_destroy(mtx), type);
	else
		print_err("Error type given");
}
void handle_thread_err(int status, t_type type)
{
	if (status == 0)
		return;
	else if (EINVAL == status && (type == LOCK || type == UNLOCK || type == DESTROY))
		print_err("Mutex Err");
	else if (EDEADLK == status || EPERM == status || ENOMEM == status || EBUSY == status)
		print_err("Mutex Err");
}

void	handle_thread(pthread_t *thread, void *(*foo)(void *), void *data, t_type type)
{
	if (type == CREATE)
		handle_thread_err(pthread_create(thread,NULL,foo,data),type);
	else if (type == JOIN)
		handle_thread_err(pthread_join(*thread,NULL),type);
	else if (type == DETACH)
		handle_thread_err(pthread_detach(*thread),type);
	else
		print_err("Error type given");
}

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		print_err("Malloc fail");
	return (res);
}