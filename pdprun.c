#include "pdp.h"
#include "pdprun.h"
#include <stdlib.h>

Arg dd, ss;


byte Bw = 0;
word NN = 0;
word r = 0;

byte flag_N  = 0;
byte flag_Z  = 0;
byte flag_V  = 0;
byte flag_C  = 0;


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

                res.val = Bw ? b_read(res.adr) : w_read(res.adr);
                
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
                  
                    trace("#%06o ", res.val);
                }

                else
                {
                 
                    trace("(R%d)+ ", r);
                }

                break;

        case 3: res.adr = w_read(reg[r]);
              
                if (r == 7 || r == 6)
                {
                    res.val = Bw ? b_read(res.adr) : w_read(res.adr);
                    reg[r] += 2;
                    trace("@#%06o ", res.adr);
                }

                else
                {
                    res.val = Bw ? b_read(res.adr) : w_read(res.adr);
                    reg[r] += 2;
                    trace("@(R%o)+ ", r);
                }

                break;
                   
       default: trace("Mode %d is not implemented yet ", m);
                exit(1);

    }


    return res;
}


void do_MOV()
{    
    
    Bw ? b_write(dd.adr,ss.val) : w_write(dd.adr,ss.val);
  
    get_flag(ss.val);
    
    flag_V = 0;

    Bw = 0;

    NZVC();
    trace("\n");
}

void do_ADD()
{
    word res = dd.val + ss.val;
    w_write(dd.adr, (byte)res);
    
    get_flag(res);
    flag_C = (res >> 16) & 1;
    trace("%d + %d\n ", dd.val, ss.val);
    NZVC();
    trace("\n");
}

void do_CLR()
{
    
    Bw ? b_write(dd.adr, 0) : w_write(dd.adr, 0);   
  
    trace("\n");

    flag_N = 0;
    flag_V = 0;
    flag_C = 0;
    flag_Z = 1;

    NZVC();
    trace("\n");
    Bw = 0;

}



void do_SOB()
{
    NZVC();
    reg[r]--;
    
    if (reg[r] > 0)
        pc -= 2*NN;
    
    trace("\n");
}

void do_HALT()
{
    trace("\n");
    trace("---------------- halted ---------------\n");

    print_reg();
    exit(0);

}

void NZVC()
{
    trace("\n");
    trace("%c", flag_N ? 'N' : '-');
    trace("%c", flag_Z ? 'Z' : '-');
    trace("%c", flag_V ? 'V' : '-');
    trace("%c", flag_C ? 'C' : '-');
}

void get_flag(word p)
{
    flag_Z = (p == 0) ? 1: 0;
    
    flag_N = Bw ? ((p >> 7) & 1) : ((p >> 15) & 1);


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
               
                if(cmd[i].params & HAS_B)
                    Bw = w >> 15;

                trace("%s%s\t", cmd[i].name, (Bw == 1) ? "b" : "");//MOVb(temp_sol)

                if(cmd[i].params & HAS_R)
                    r= (w & 0700) >> 6;

                if(cmd[i].params & HAS_SS)
                    ss = get_mr(w >> 6);

                if(cmd[i].params & HAS_DD)
                    dd = get_mr(w);
                

                if(cmd[i].params & HAS_NN)
                    NN = w & 077;
        
                cmd[i].do_func();

                Bw = 0;
    
                trace("\n");
                
                print_reg();

                break;

            }
        }
    }
}

