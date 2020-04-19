#ifndef pdprun_h
#define pdprun_h

typedef struct
{
    word mask;
    word opcode;
    char * name;
    void (*do_func)(void);   //err
    char params;
} Command;

enum PARAMS_MASK {

    NO_PARAMS,
    HAS_DD,
    HAS_SS,

};


Command cmd[] = {
    {0170000, 0010000, "mov", do_MOV, HAS_SS | HAS_DD},
    {0170000, 0060000, "add", do_ADD, HAS_SS | HAS_DD},
    {0177777, 0000000, "halt", do_HALT, NO_PARAMS},
};

typedef struct {

    word val;
    word adr;

}Arg;



Arg get_mr(word w);


void run();


#endif
