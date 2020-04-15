#ifndef pdprun_h
#define pdprun_h

typedef struct
{
    word mask;
    word opcode;
    char * name;
    void (*do_func)(void);   //err
    
} Command;

void do_MOV();
void do_ADD();
void do_HALT();
void do_nothing();

Command cmd[] = {
    {0170000, 0010000, "mov", do_MOV},
    {0170000, 0060000, "add", do_ADD},
    {0777777, 0000000, "halt", do_HALT},
    {0000000, 0000000, "unknown", do_nothing}
};


#endif

