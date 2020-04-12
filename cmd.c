#include "headers/cmd.h"
#include "headers/dbg.h"
#include <stdlib.h>

extern int tr;

extern Arg ss;
extern Arg dd;
extern Word nn;
extern Word n;
extern Word r;

extern Byte mem[MEMSIZE];

extern Word reg[8];
#define pc reg[7]

Cmd cmd[] =
        {
                {0xFFFF, 0000000, NO_PARAMS, "HALT", do_HALT},
                {0xFFC0, 0005000, HAS_DD, "CLR", do_CLR},
                {0xFE00, 0077000, HAS_R | HAS_NN, "SOB", do_SOB},
                {0xF000, 0010000, HAS_SS | HAS_DD, "MOV", do_MOV},
                {0xF000, 0060000, HAS_SS | HAS_DD, "ADD", do_ADD},
                {0xF000, 0160000, HAS_SS | HAS_DD, "SUB", do_SUB},
                {0x0000, 0000000, NO_PARAMS, "unknown cmd", do_unknown},
        };

void do_ADD()
{$;
    INDENT(T);
    trace(T, "[%s]\n", __PRETTY_FUNCTION__);
    //print_reg();

    w_write(dd.adr, dd.val + ss.val);

    INDENT(T);
    trace(T, "%d + %d\n", dd.val, ss.val);
    print_reg();
$$;
}

void do_SUB()
{$;
    INDENT(T);
    trace(T, "[%s]\n", __PRETTY_FUNCTION__);
    //print_reg();

    w_write(dd.adr, dd.val - ss.val);

    INDENT(T);
    trace(T, "%d - %d\n", dd.val, ss.val);
    print_reg();
    $$;
}

void do_HALT()
{$;
    INDENT(T);
    tr = 1;
    trace(T, "[%s]\n", __PRETTY_FUNCTION__);
    print_reg();
$$;
    exit(0);
}

void do_MOV()
{$;
    INDENT(t);
    trace(t, "[%s]\n", __PRETTY_FUNCTION__);
    //print_reg();

    w_write(dd.adr, ss.val);

    INDENT(t);
    trace(t, "adr: %d = %o\n", dd.adr, ss.val);
    print_reg();
$$;
}

void do_CLR()
{$;
   INDENT(t);
    trace(t, "[%s]\n", __PRETTY_FUNCTION__);

    w_write(dd.adr, 0);

    INDENT(t);
    trace(t, "adr: %d = %o\n", dd.adr, ss.val);
    print_reg();
$$;}

void do_SOB()
{$;
    INDENT(t);
    trace(t, "[%s]\n", __PRETTY_FUNCTION__);

    INDENT(t);
    trace(t, "SOB\nR = %hx, Rn = %ho, NN = %hx, pc = %ho\n", r, reg[r], nn, pc);

    reg[r] -= 1;
    if(reg[r] > 0)
        pc -= 2*nn;

    INDENT(t);
    trace(t, "SOB\nR = %hx, Rn = %ho, NN = %hx, pc = %ho\n", r, reg[r], nn, pc);
    print_reg();
$$;}

void do_unknown()
{$;
    INDENT(t);
    trace(t, "[%s]\n", __PRETTY_FUNCTION__);
$$;
    exit(1);
}

/*void do_ADD()
{
    printf("%s\n", __PRETTY_FUNCTION__);
}*/

