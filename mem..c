#include "shell.h"

/**
 * copy_memory - copy memory from source to destination
 * @dest: destination pointer
 * @src: source pointer
 * @n: number of bytes to copy
 * Return: void
 */
void copy_memory(char *dest, char *src, unsigned int n)
{
	unsigned int i = 0;

	for (; i < n; i++)
	{
		dest[i] = src[i];
	}
}

/**
 * reallocate_mem - reallocate memory with new size
 * @ptr: pointer to the memory block
 * @old_size: old size of the memory block
 * @new_size: new size of the memory block
 * Return: pointer to the reallocated memory block
 */
void *reallocate_mem(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
		return (new_ptr);
	}

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		free(ptr);
		exit(0);
	}

	if (new_size > old_size)
		copy_memory(new_ptr, ptr, old_size);
	else
		copy_memory(new_ptr, ptr, new_size);

	free(ptr);
	return (new_ptr);
}
