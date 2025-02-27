#ifndef __FS_VFS_HEADER
#define __FS_VFS_HEADER

typedef struct {
	int flags;
	FS_node** next_nodes;
	char* name;
} FS_node;

FS_node traverse_nodes(char*);

int open(const char*, const char*);
int write(FS_node, char*);
int read(FS_node);
int close(FS_node);
#endif
