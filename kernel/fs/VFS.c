#include "VFS.h"
#include <stdbool.h>
#include <string.h>

FS_node root;
fd fds[10] = { 0 };

void vfs_init() {
	root.flags = 1;
	memset(root.next_nodes, 0, NODEMAX * sizeof(FS_node*));
	root.name = "/";
}

FS_node* traverse_nodes(const char* path) {
	FS_node* current = &root;
	while (1) {
		if (memcmp(path, current->name, strlen(path)))
			break;
	
			
	}
	return current;
}

int open(const char* path, unsigned char flags) {
	// Look for next free file descriptor
	int nextfd = 0;
	while (!fds[nextfd].mode) {
		nextfd++;
	}

	// find FS_node at path
	FS_node* node = traverse_nodes(path);
	
	// make an entry in the filedescriptor array
	//fds[nextfd] = (fd) {flags, };
	
	return nextfd;
}

size_t write(int fd, char* buf) {

}

size_t read(int fd, void* buf, size_t count) {

}

int close(int fd) {

}
