#include "glthread.h"
#include <stdio.h>

// here we are getting the addresses to the nodes directly so no need to traverse anything, just change the links

static void glthread_add_next(glthread_node_t *node_to_prepend, glthread_node_t *already_existing_node) {
    if(!node_to_prepend->right) {
        node_to_prepend->right = already_existing_node;
        already_existing_node->left = node_to_prepend;
    }

}

// will insert this glnode to the starting of the list not at the end, so prepending instead of appending
void glthread_add(glthread_t *lst, glthread_node_t *glnode) {
    glnode->left = NULL;
    glnode->right = NULL;

    // need to check where inserting now
    if (!lst->head) {
        // this is the first node
        lst->head = glnode;
        return;
    }
    glthread_node_t *head = lst->head;
    glthread_add_next(glnode, head);
    lst->head = glnode;
}


static void glthread_remove_node(glthread_node_t *node){
    // could be removing the first/last/any node in the middle
    
    // first node
    if(!node->left) {
        if(node->right) {
            node->right->left = NULL;
            node->right = NULL; // have isolated this node basically now
        }
        return;
    }

    // last node
    if(!node->right) {
        // this has to be the last node
        node->left->right = node->right;
        node->left = NULL; // have isolate the node
        return;
    }

    // any node in random
    node->left->right = node->right;
    node->right->left = node->left;
    // now isolating this node
    node->left = NULL;
    node->right = NULL;

    return;
}

static void glthread_remove_node_better(glthread_node_t *node) {
    if(node->left) {
        // need to make sure left node is pointing to correct node
        node->left->right = node->right;
    }

    if(node->right) {
        node->right->left = node->left;
    }

    // isolating the node
    node->left = NULL;
    node->right = NULL;

}


void glthread_remove(glthread_t *lst, glthread_node_t *node) {
    // need to go till the node which is pointing to this node and then make the link changes
    // also no need to call the free method here, the main block which is calling this method will call the free method
   if (node == lst->head) {
    // making sure head is pointing to correct node
    lst->head = node->right;
   }

    // glthread_remove_node(node);
    glthread_remove_node_better(node);
}

void glthread_init(glthread_t *glthread, size_t offset) {
    glthread->head = NULL;
    glthread->offset = offset;
}