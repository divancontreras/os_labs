# Managing Memory

On all computers is a scare resource, the demand of it is increasing real fast, and we need to make software as eficient as posible. UNIX-style operating systems have had a very clean approach to managing memory, and in most cases is almost never permitted to access physical memory directly.

## Simple Memory Allocation

You can allocate a great amount of memory in almost all Linux Systems, this can be done in runtime with malloc library, every malloc will store a megabyte.

## Allocating Lots of Memory.

This program will allocate more memory than the system has available.

## Available Memory

The application’s allocated memory is managed by the Linux kernel. Each time the program asks for
memory or tries to read or write to memory that it has allocated, the Linux kernel takes charge and
decides how to handle the request

## Abusing Memory

The Linux memory management system has protected the rest of the system from this abuse of memory.
To ensure that one badly behaved program (this one) can’t damage any other programs, Linux has terminated
it.

## The Null Pointer

The first printf attempts to print out a string obtained from a null pointer; then the sprintf attempts to
write to a null pointer. In this case, Linux (in the guise of the GNU “C” library) has been forgiving about
the read and has simply provided a “magic” string containing the characters ( n u l l ) \0. It hasn’t been
so forgiving about the write and has terminated the program. This can sometimes be helpful in tracking
down program bugs.

## Freeing Memory

Programs that use memory on a dynamic basis should always release unused memory back to the
malloc memory manager using the free call. This enables separate blocks to be remerged and enables
the malloc library to look after memory, rather than have the application manage it.

## Other Memory Allocation Functions

Although calloc allocates memory that can be freed with free, it has somewhat different parameters
from malloc: It allocates memory for an array of structures and requires the number of elements and the
size of each element as its parameters. 

The realloc function changes the size of a block of memory that has been previously allocated. It’s
passed a pointer to some memory previously allocated by malloc, calloc, or realloc and resizes it
up or down as requested
