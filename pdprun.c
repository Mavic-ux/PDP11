#include "pdp.h"
#include "pdprun.h"
#include <stdlib.h>

Arg dd, ss;

byte Bw;

Arg get_mr(word w)
{
    int r = w & 7;
    int m = (w >> 3) & 7;

    Arg res;

    switch(m)
    {
        case 0: res.adr = r;
                res.val = reg[r];
              
                trace("R%d ", r);

                break;
        case 1: res.adr = reg[r];

                if (Bw == 0)
                    res.val = w_read(res.adr);

                else if (Bw == 1)
                    res.val = b_read(res.adr);
                
                trace("(R%d) ", r);

                break;
        case 2: res.adr = reg[r];

                if (Bw == 0)
                {
                    res.val = w_read(res.adr);
                    reg[r] += 2;
                }
                else if (Bw == 1)
                {
                    res.val = b_read(res.adr);
                    reg[r] += (r < 6) ? 1 : 2;
                }

                if (r == 7)
                {
                  
                    trace("#%o ", res.val);
                }

                else
                {
                 
                    trace("(R%d)+ ", r);
                }

                break;
 
       default: trace("Mode %d is not implemented yet ", m);
                exit(1);

    }


    return res;
}

void do_halt()
{
    trace("THE END\n");
    print_reg();
    exit(EXIT_SUCCESS);
}

void do_MOV()
{
    if (Bw == 0)
        w_write(dd.adr, ss.val);

    else if (Bw == 1)
        b_write(dd.adr, ss.val);

    else
        exit(0);

    Bw = 0;
}

void do_ADD()
{
    byte res = dd.val + ss.val;
    w_write(dd.adr, res);
    trace("%d + %d\n", dd.val, ss.val);
}

void do_HALT()
{
    trace("\n");
    trace("---------------- halted ---------------\n");
    print_reg();
    exit(0);

}

void do_nothing()
{


}

void run()
{
    pc = 01000;

    trace("---------------- running --------------\n");

    while(1)
    {
        trace("\n");

        word w = w_read(pc);

        trace("%06o: ", pc);

        pc += 2;

        for(unsigned int i = 0; i <= sizeof(cmd)/sizeof(Command); i++)
        {
            if((w & cmd[i].mask) == cmd[i].opcode)
            {
                
                trace("%s\t", cmd[i].name);

                if(cmd[i].params & HAS_SS)
                    ss = get_mr(w >> 6);

                if(cmd[i].params & HAS_DD)
                    dd = get_mr(w);
               

                cmd[i].do_func();

                Bw = 0;
    
                trace("\n");
                
                print_reg();

                break;

            }
        }
    }
}
