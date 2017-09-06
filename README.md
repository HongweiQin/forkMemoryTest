# forkMemoryTest
A simple program to test memory status after fork()

In this test, the main process defines 4 different variants: count, pi,pmmapprivate, and pmmapshared.

count is a simple variant.

pi is a pointer points to a malloced integer.

pmmapprivate is a pointer points to a mmaped integer array.

pmmapshared is another pointer points to another mmaped intgeger array.

When mapping, pmmapprivate use MAP_PRIVATE as argument while pmmapshared use MAP_SHARED.

All abovementioned integers are initialized.

Afterwards, the main process calls the syscall fork();

The if-else separates the parent and the child process.

The child process modifies all abovementioned variants.

The parent process wait for the child process finishing its job and then prints out those variants.

Result shows that parent and child process don't share count,pi,and mmap private variants and will do copy-on-write after a memory store operation, and that parent and child process share mmap shared memory region and memory store operations are visible through these two process.
