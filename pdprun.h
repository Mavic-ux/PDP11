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
    HAS_N,
    HAS_NN,
    HAS_R,
    HAS_XX,
    HAS_B,

};


Command cmd[] = {
    {0070000, 0010000, "MOV", do_MOV, HAS_B | HAS_SS | HAS_DD},
    {0170000, 0060000, "ADD", do_ADD, HAS_SS | HAS_DD},
    {0177777, 0000000, "HALT", do_HALT, NO_PARAMS},
    {0077700, 0005000, "CLR", do_CLR, HAS_DD},
    {0177000, 0077000, "SOB", do_SOB, HAS_NN},
 
};

typedef struct {

    word val;
    word adr;

}Arg;



Arg get_mr(word w);


void run();


#endif
