#include "Emulator.h"
#include "stdafx.h"
#include "Errors.h"

/**/
/*
NAME
    emulator::insertMemory(int a_location, int a_contents)

SYNOPSIS
    bool emulator::insertMemory(int a_location, int a_contents)
    a_location --> location what which to be inserted
    a_contents --> contents to be inserted into memory

DESCRIPTION
    Function to insert the contents into memory. Handles errors if location goes over 10,000.

RETURNS
    returns false if the memory exceeds 10,000. Returns true otherwise.
*/
/**/
bool emulator::insertMemory(int a_location, int a_contents){
    if(a_location< 10000){
        m_memory[a_location]= a_contents;
    }
    else{
        //memory too large
        string error = "Memory is too large";
        Errors::RecordError(error);
        return false;
    }
    return true;
}
/* bool emulator::insertMemory(int a_location, int a_contents) */

/**/
/*
NAME
    emulator::runProgram()

SYNOPSIS
    bool emulator::runProgram()

DESCRIPTION
    Function uses if statements based on op code to call corresponding fucntions. divides memeory into first 2(opcode) and last 4 (address).

RETURNS
    false
*/
/**/
bool emulator::runProgram(){
    location=0;

    for( ; ;){
        // dividing by 10000 gets the first 2 digits
        int op_code= m_memory[location]/10000;

        // moding by 10000 gets the last 4 digits
        addr= m_memory[location] % 10000;

        //calling appropriate functions in relation to the op code
        if(op_code==1){
            add();
        }

        else if(op_code== 2){
            sub();
        }

        else if(op_code==3){
            mult();
        }

        else if(op_code==4){
            divide();
        }

        else if(op_code==5){
            load();
        }

        else if(op_code==6){
            store();
        }

        else if(op_code==7){
            read();
        }

        else if(op_code==8){
            write();
        }

        else if(op_code==9){
            branch();
        }

        else if(op_code==10){
            branch_min();
        }

        else if(op_code==11){
            branch_zero();
        }

        else if(op_code==12){
            branch_pos();
        }

        else if(op_code ==13){
            halt();
            return true;
        }

        else{
            location++;
        }
    }
    return false;
}
/*bool emulator:runProgram() */

/**/
/*
NAME
    emulator::add()

SYNOPSIS
    void emulator::add()

DESCRIPTION
    Function adds the the accueumulator and memory and increase location.

*/
/**/
void emulator::add(){
    //ACC <-- c(ACC) + c(ADDR)
    int sum=acceumulator+m_memory[addr];
    acceumulator=sum;
    location++;
}
/*void emulator::add()*/

/**/
/*
NAME
    emulator::sub()

SYNOPSIS
    void emulator::sub();

DESCRIPTION
    Function that subtracts acceumulator and memory and increase location.

*/
/**/
void emulator::sub(){
    int diff=acceumulator-m_memory[addr];
    acceumulator=diff;
    location++;
}
/*void emulator::sub()*/

/**/
/*
NAME
    emulator::mult()

SYNOPSIS
    void emulator::mult();

DESCRIPTION
    Function to multiply the acc. and memory
*/
/**/
void emulator::mult(){
    int product=acceumulator*m_memory[addr];
    acceumulator=product;
    location++;
}
/*void emulator::mult()*/

/**/
/*
NAME
    emulator::divide()

SYNOPSIS
    void emulator::divide();

DESCRIPTION
    Function to divide the acc and memory
*/
/**/
void emulator::divide(){
    int quotient=acceumulator/m_memory[addr];
    acceumulator=quotient;
    location++;
}
/*void emulator::divide()*/

/**/
/*
NAME
    emulator::load()

SYNOPSIS
    void emulator::load()

DESCRIPTION
    assigns memory into acc. and increase location

*/
/**/
void emulator::load(){
    //ACC <-- c(ADDR)
    acceumulator=m_memory[addr];
    location++;
}
/*void emulator::load()*/

/**/
/*
NAME
    emulator::store()

SYNOPSIS
    void emulator::store()

DESCRIPTION
    stores acc. into memory

*/
/**/
void emulator::store(){
    //ADDR <-- c(ACC)
    m_memory[addr]=acceumulator;
    location++;
}
/*void emulator::store()*/

/**/
/*
NAME
    emulator::read()

SYNOPSIS
    void emulator::read()

DESCRIPTION
    reads in input, and and stores it in memory.

*/
/**/
void emulator::read(){
    //A line is read and its first 6 digits are placed in the specified address.
    string line;
    string line_6;

    cout<<"?";
    cin>>line;

    //need to convert string to int--only taking first 6 letters
    line_6=line.substr(0,5);
    int int_line6=atoi(line_6.c_str());

    m_memory[addr]=int_line6;
    location++;
}
/*void emulator::write()*/

/**/
/*
NAME
    emulator::write()

SYNOPSIS
    void emulator::write()

DESCRIPTION
    outputs the memory and increases the location.

*/
/**/
void emulator::write(){
    //c(ADDR) is displayed
    cout<<m_memory[addr]<<endl;
    location++;
}
/*void emulator::write()*/

/**/
/*
NAME
    emulator::branch()

SYNOPSIS
    void emulator::branch()

DESCRIPTION
    puts address into acc.

*/
/**/
void emulator::branch(){
    acceumulator=addr;
}
/*void emulator::branch()*/

/**/
/*
NAME
    emulator::branch_min()

SYNOPSIS
    void emulator::branch_min()

DESCRIPTION
    if the acc is less than 0 put addr into acc. otherwise increases location

*/
/**/
void emulator::branch_min(){
    if(acceumulator<0){
        acceumulator=addr;
    }

    else{
        location++;
    }
}
/*void emulator::branch_min()*/

/**/
/*
NAME
    emulator::branch_zero()

SYNOPSIS
    void emulator::branch_zero()

DESCRIPTION
    if acc is equal to zero, put addr into acc. Otherwise increase location.

*/
/**/
void emulator::branch_zero(){
    if(acceumulator == 0){
        acceumulator=addr;
    }

    else{
        location++;
    }
}
/*void emulator::branch_zero()*/

/**/
/*
NAME
    emulator::branch_pos()

SYNOPSIS
    emulator::branch_pos()

DESCRIPTION
    if the acc is greater than zero put addr. into location. Otherwise increase location.

*/
/**/
void emulator::branch_pos(){
    if(acceumulator > 0){
        location=addr;
    }

    else{
        location++;
    }
}
/*void emulator::branch_pos()*/

/**/
/*
NAME
    emulator::halt()

SYNOPSIS
    void emulator::halt()

DESCRIPTION
    function sets location to the end

*/
/**/
void emulator::halt(){
    location= 10000;
}
/*void emulator::halt() */
