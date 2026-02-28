/**
    glthread is basically a doubly linked list.
 
    function pointer
    ****************
    syntax: return_type (*pointer_name)(parameter_types);

    Note: int* fp(int, int) => this implies function returning int pointer, this is NOT a function pointer. int (*fp)(int, int) => this is a function pointer.

    int add (int a, int b) {
        return a + b;
    }

    fp = add; // assigning function to function pointer

    int result = fp(2, 3); // calling function using function pointer
    int result = (*fp)(2, 3); // this is also valid

    Callback functions (function pointers as arguments)
    ***************************************************

    int add (int a, int b) {
        return a + b;
    }

    int multiply(int a, int b) {
        return a * b;
    }

    // operation is a function pointer, also called callback function
    void compute(int (*operation)(int, int), int x, int y) {
        int result = operation(x, y);
        std::cout << "Result: " << result << std::endl;
    }

    typedef to simplify function pointers
    *************************************

    typedef int (*Operation)(int, int);    // note here we just declare a new type: Operation: all functions that take in 2 ints and return an int can be represented by this Operation function pointer as done below

    int operate(int x, int y, Operation op) {
        return op(x, y);
    }

    Array of function pointers
    **************************

    int add(int a, int b) { return a + b; }
    int multiply(int a, int b) { return a * b; }
    int subtract(int a, int b) { return a - b; }

    int (*ops[])(int, int) = {add, multiply, subtract};

    // can be called like this
    for (int i = 0; i < 3; ++i) {
        int result = ops[i](5, 3);
        std::cout << "Result: " << result << std::endl;
    }

    function pointers in struct
    ***************************

    typedef struct {
        int (*operate)(int, int);
    } Calculator;

    int add (int a, int b) {
        return a + b;
    }

    int main() {
        Calculator c;
        c.operate = add;

        printf("%d\n", c.operate(4,5)); // prints 9
    }

    Basically, think of function pointers as interfaces in C, can create different implementations and assign them to function pointers.
 */