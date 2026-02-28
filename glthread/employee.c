#include"glthread.h"
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>


typedef struct employee {
    char name[30];
    char designation[30];
    unsigned int salary;
    unsigned int emp_id;
    // need a pointer to glnode as well
    glthread_node_t glnode;

} emp_t;

// should get pointer to starting of the emp_t object to print the detaisl
void print_emp_details(emp_t *emp){
    printf("Employee name = %s\n", emp->name);
    printf("salary = %u\n", emp->salary);
    printf("designation = %s\n", emp->designation);
    printf("emp_id = %u\n", emp->emp_id);
} 

int main() {
    //making 3 emp_t objects
    emp_t *emp1 = calloc(1, sizeof(emp_t));
    // it is dangerous to use strncpy instead use snprintf now.
    strncpy(emp1->name, "name1", strlen("name1"));
    strncpy(emp1->designation, "designation1", strlen("designation1"));
    emp1->salary = 10;
    emp1->emp_id = 1;

    emp_t *emp2 = calloc(1, sizeof(emp_t));
    strncpy(emp2->name, "name2", strlen("name2"));
    strncpy(emp2->designation, "designation2", strlen("designation2"));
    emp2->salary = 20;
    emp2->emp_id = 2;

    emp_t *emp3 = calloc(1, sizeof(emp_t));
    strncpy(emp3->name, "name3", strlen("name3"));
    strncpy(emp3->designation, "designation3", strlen("designation3"));
    emp3->salary = 30;
    emp3->emp_id = 3;

    // now initializing a glthread
    glthread_t *glthread = calloc(1, sizeof(glthread_t));
    glthread_init(glthread, offsetOf(emp_t, glnode)); // need to pass the constant value of offset of glnode in emp_t, this basically will make head as null and assign offset as whatever provided
    // now using the head can make the whole glthread

    glthread_add(glthread, &emp1->glnode); // since never init the glnode inside the emp_t object, glthread_add method will handle this
    glthread_add(glthread, &emp2->glnode);
    glthread_add(glthread, &emp3->glnode);

    // iterating over the glthread
    // need to get the starting address of the emp_t object
    emp_t *ptr = NULL;

    ITERATE_GL_THREAD_BEGIN(glthread, ptr, emp_t) {
        print_emp_details(ptr);
    } ITERATE_GL_THREAD_ENDS
    // removing one node
    glthread_remove(glthread, &emp2->glnode);

    // iterating again
    printf("Printing again after removing a glued node!\n");
    ITERATE_GL_THREAD_BEGIN(glthread, ptr, emp_t) {
        print_emp_details(ptr);
    } ITERATE_GL_THREAD_ENDS

    // freeing all the memory allocated
    ITERATE_GL_THREAD_BEGIN(glthread, ptr, emp_t){
        glthread_remove(glthread, &ptr->glnode);
        free(ptr);
    }ITERATE_GL_THREAD_ENDS
}
