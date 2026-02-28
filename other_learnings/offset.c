#include <stdio.h>
#include <string.h>

typedef struct glthread_node {
    struct glthread_node *left;
    struct glthread_node *right;
} glthread_node_t;

typedef struct emp {
    char name[30];
    unsigned int salary;
    char designation[30];
    unsigned int employee_id;
    glthread_node_t glNode;
} emp_t;

/*
 * given the glNode address need to print the employee details
 * so basically we need to calculate the offset(difference b/w starting address of node and starting address of struct object say 64).
 * then if subtract 64, will get starting address of struct object, then can get the emp details
*/

/**
 * Note: can directly pass the fields in macros. why?
 * Preprocessor is not part of the C compiler. It is a text-replacement engine that runs before the compiler even looks at your code.
 * whenever offsetOf(struct_name, struct_field) it will be replaced by (size_t)&((struct_name *)0 -> struct_field) automatically
 * 
 * Since we don't know what type struct_field could be, better to define it as macro
 */

// basically taking the starting of the computer's memory map(0) and then telling the compiler to treat this memory as if pointing to this struct object, get the field and then get the address of the field(32 bit or 64 bit depending upon system) and then convert it back to unsigned integer
#define offsetOf(struct_name, struct_field) \
    (size_t)&(((struct_name *)0) -> struct_field) // unsigned int will not work because that is of 32 bits but here since doing &, will get a 64 bit pointer, so half info will be lost.

    
void print_emp_details(glthread_node_t *node) {
    // this node is part of the struct, so getting the offset of glNode and then just removing that offset will give the starting address of the struct
    // size_t is of 64 bit in 64 bit machines, it basically represents memory which in a 64 bit mahcine is 64 bit 
    // whenever we do & basically passing or getting memory info which is stored in pointer, that is of 64 bits
    size_t offset = offsetOf(emp_t, glNode);

    // now need to convert glthread_node_t* to char* due to pointer arithmetic, for eg if do (int*)4 - 3 => some memory address - 3 * 4bytes as assume each integer takes 4 bytes.
    // but here need to subtract whatever offset we get so if 72, need to subtract 72 bytes only
    emp_t *emp = (emp_t *)((char *)node - offset); // basically doing memory subtraction, think of this as like subtracing 2 hexadecimal numbers.

    printf("------------Employee Details-------------\n\n");
    printf("Id: %u\n", emp->employee_id);
    printf("Name: %s\n", emp->name);
    printf("Designation: %s\n", emp->designation);
    printf("Salary: %u\n", emp->salary);
        
}


int main() {
    emp_t info;

    info.salary = 70000;
    info.employee_id = 20;
    strcpy(info.name, "Henry");
    strcpy(info.designation, "Software engineer");

    // init glnode
    info.glNode.left = NULL;
    info.glNode.right = NULL;

    print_emp_details(&info.glNode);


}