#include "VFS.h"
#include <string.h>

FS_node root;
fd fds[10] = { 0 };
FS_node testnode;

void vfs_init() {
	root.flags = 1;
	memset(root.next_nodes, 0, NODEMAX * sizeof(FS_node*));
	root.name = "/";
	testnode.flags = 1;
	testnode.name = "a";
	memset(testnode.next_nodes, 0, NODEMAX * sizeof(FS_node*));
	root.next_nodes[0] = (struct FS_node*)&testnode;
}

FS_node* traverse_nodes(const char* path) {
	FS_node* current = &root;
	char* curfolder = strtok(path, "/");
	size_t i = 0;

	while (curfolder != NULL) {
		for (i = 0; i < NODEMAX; i++) {
			FS_node* next_node = (FS_node*)current->next_nodes[i];
			if (memcmp(next_node->name, curfolder, strlen(curfolder)) == 0) {
				// Next folder found
				current = next_node;

				break;
			}
		}
		if (i == NODEMAX) {
			// next folder not found, return NULL
			return NULL;
		}
		curfolder = strtok(NULL, "/");
	}

	return current;
}

int open(const char* path, unsigned char flags) {
	// Look for next free file descriptor
	int nextfd = 0;
	while (fds[nextfd].mode != 0) {
		nextfd++;
	}	

	// find FS_node at path
	FS_node* node = traverse_nodes(path);
	
	// make an entry in the filedescriptor array
	fds[nextfd] = (fd) {flags, node};
	
	return nextfd;
}

size_t write(int fd, char* buf) {

}

size_t read(int fd, void* buf, size_t count) {

}

int close(int fd) {
	fds[fd].mode = 0;
}
