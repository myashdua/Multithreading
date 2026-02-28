/**
 * Traditional Linked List:
 * ************************
 * [next pointer] + [data]
 * 
 * Glue Thread
 * ***********
 * [Data + [next pointer]]
 * 
 * create a tiny "Link" structure (the "Glue") and embed it inside your existing data structure. So the thread itself doesn't own any data
 * So a single data object/struct can be stored on multiple glthreads. 
 * since this data object needs to stick itself to a glNode, it will contain an object of glthread_node_t inside its data strucure and will glue itself to the glnode 
 * this is how this data object will become part of glthread
 * since this data member can have multiple objects inside representing other glthread nodes, so this data can be glued to multiple glthread_node_t and hence multiple glthreads
 * Since None of the glNodes are themselves storing data, this helps in saving memory
 * 
 */
#ifndef __GLUETHREAD__
#define __GLUETHREAD__

#include <stddef.h>

typedef struct glthread_node_ {
    struct glthread_node_  *left;
    struct glthread_node_ *right;
} glthread_node_t;


typedef struct _glthread { 
    // basically storing the address of starting node, but this will come from a structure storing data. 
    // so this glNode object will be part of the structure and will be participating in glthread as well
    // so indirectly that data is participating in glthread
    // and this glNode object also has left and right pointers, moving to next glNodes through which we can get main structure that is storing data by removing the offset of this glNode.
    glthread_node_t *head; 
    size_t offset; // offset of any field inside a struct is the number of bytes it is away from the start of the structure object, and this will be a constant value for a particular structure
    // since this thread will contain nodes which will contain structure of a particular type so this offset value should be same
} glthread_t;


void glthread_add(glthread_t *lst, glthread_node_t *glnode);

void glthread_remove(glthread_t *lst, glthread_node_t *glnode);

// Iterative macro to iterate over glthread
// struct type will be passed to offetOf macro to get the offset of glNode and then subtract it to get the starting address of the struct object to print the data
#define ITERATE_GL_THREAD_BEGIN(lstptr, ptr, struct_type)     \
{                                                             \
    glthread_node_t *_glnode = NULL, *_next = NULL;                          \
    for(_glnode = lstptr->head; _glnode; _glnode = _next) {    \
        _next = _glnode->right;                      \
        ptr = (struct_type *)((char *)_glnode - lstptr->offset); // getting the ptr to the starting of the str to print the details


#define ITERATE_GL_THREAD_ENDS }}


#define glthread_node_init(node) \
    node->left = NULL; \
    node->right = NULL; 


void glthread_init(glthread_t *glthread, size_t offset);

#define offsetOf(struct_type, struct_field) \
    (size_t)&(((struct_type *)0) -> struct_field)


#endif