#ifndef __FS_VFS_HEADER
#define __FS_VFS_HEADER

#define NODEMAX 10

typedef struct {
	int flags;
	struct FS_node* next_nodes[NODEMAX];
	char* name;
} FS_node;

typedef struct {
	int mode;
	struct FS_node*;
} fd;

enum VFS_flags {
	D  = 1,
	F  = 2,
	X  = 4,
	IO = 8
}

enum file_flags {
	RDONLY = 0b00000001,
	WRONLY = 0b00000010,
	APPEND = 0b00000100,
	CREATE = 0b00001000,
	TRUNC  = 0b00010000,
};

FS_node* traverse_nodes(const char*);

int open(const char*, unsigned char);
size_t write(int, char*);
size_t read(int, void*, size_t);
int close(int);
#endif
