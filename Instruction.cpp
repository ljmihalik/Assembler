//
//  Implementation of instruction class.
//
#include "stdafx.h"
#include "Instruction.h"
#include <iostream>

#include <string>
#include <sstream>
#include <vector>

using namespace std;
//class Instruction;

/**/
/*
Name
   Instruction::get_instruction()

Synopsis
    int Instruction::get_instruction()

Description
    function to get private variable m_instruction

Returns
    m_Instruction
*/
/**/
string Instruction::get_instruction(){
    return m_instruction;
}
/*string Instruction::get_instruction() */

/**/
/*
Name
   Instruction::get_operand()

Synopsis
    int Instruction::get_operand()

Description
    function to get private variable m_Operand

Returns
    m_Operand
*/
/**/
string Instruction::get_operand(){
    return m_Operand;
}
/*string Instruction::get_Operand() *?

/**/
/*
Name
   Instruction::get_opCode()

Synopsis
    int Instruction::get_opCode()

Description
    function to get private variable m_pCode

Returns
    m_NumOpCode
*/
/**/
string Instruction::get_opcode(){
    return m_OpCode;
}
/*string Instruction::get_opcode() */

/**/
/*
Name
   Instruction::get_num_opCode()

Synopsis
    int Instruction::get_num_opCode()

Description
    function to get private variable m_NumOpCode

Returns
    m_NumOpCode
 */
/**/
int Instruction::get_num_opCode(){
    return m_NumOpCode;
}
/*int Instruction::get_num_opCode() */

/**/
/*
Name
    Instruction::get_operandValue()

Synopsis
    int Instruction::get_operandValue()

Description
    function to get private variable m_OperandValue

Returns
    m_OperandValue
*/
/**/
int Instruction::get_operandValue(){
    return m_OperandValue;
}
/*int Instruction::get_operandValue() */

/**/
/*
Name
    Instruction::get_is_numeric()

Synopsis
    bool Instruction::get_is_numeric()

Description
    function to get private variable m_IsNumericOperand.

Returns
    m_IsNumericOperand
*/
/**/
 bool Instruction::get_is_numeric(){
     return m_IsNumericOperand;
 }
 /*Instruction::get_is_numeric() */

/**/
/*
Name
    Instruction::set_numOpCode()

Synopsis
    void Instruction::set_numOpCode()

Description
    function sets the numeric op code
*/
/**/
void Instruction::set_numOpCode(){
    if(m_OpCode=="add"){
        m_NumOpCode=1;
    }
    else if(m_OpCode=="sub"){
        m_NumOpCode=2;
    }
    else if(m_OpCode=="mult"){
        m_NumOpCode=3;
    }
    else if(m_OpCode=="div"){
        m_NumOpCode=4;
    }
    else if(m_OpCode=="load"){
        m_NumOpCode=5;
    }
    else if(m_OpCode=="store"){
        m_NumOpCode=6;
    }
    else if(m_OpCode=="read"){
        m_NumOpCode=7;
    }
    else if(m_OpCode=="write"){
        m_NumOpCode=8;
    }
    else if(m_OpCode=="b"){
        m_NumOpCode=9;
    }
    else if(m_OpCode=="bm"){
        m_NumOpCode=10;
    }
    else if(m_OpCode=="bz"){
        m_NumOpCode=11;
    }
    else if(m_OpCode=="bp"){
        m_NumOpCode=12;
    }
    else if(m_OpCode=="halt"){
        m_NumOpCode=13;
    }
    else{
        //assembler language
        m_NumOpCode=999;
    }
}
/*void Instruction::set_numOpCode()*/

/**/
/*
Name
    Instruction::ParseInstruction()

Synopsis
    Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
    string a_buff -->

Description
    resets all variables then sets all variables, deletes comments, parses instruction into machine
    lang, assembly lang, comments, and end statements.
*/
/**/
Instruction::InstructionType Instruction::ParseInstruction(string & a_buff){
    //reserting the variables
    m_Label="";
    m_OpCode="";
    m_Operand="";
    m_OperandValue=0;
    m_IsNumericOperand=false;
    m_instruction="";
    m_NumOpCode=0;

    //setting m_instruction
    m_instruction=a_buff;

    //looking for comments
    size_t found=a_buff.find(";");
    if(found != std::string::npos){
        //if line has comment, remove the comment (delete all to right of comment start)
        a_buff.erase(found, string::npos);
    }

    //checking if blank --treating comments and blanks the same
    if(a_buff.empty()){
        //if line is blank instruction = ST_Comment
        m_type=ST_Comment;
        return m_type;
        cout<<"empty"<<endl;
    }

    //putting string into vector
    vector <string> arr;
    stringstream ins(a_buff);
    string temp;
    while (ins >> temp){
        arr.push_back(temp);
    }

    //setting private variables if label, op code, and operand are there
    if(arr.size()==3){
        m_Label=arr[0];
        m_OpCode=arr[1];
        m_Operand=arr[2];

    }

    //setting if only 2 are there (i.e. op code, operand)
    else if(arr.size() ==2){
        m_OpCode=arr[0];
        m_Operand=arr[1];
    }

    //setting if only 1 (opcode)
    else if(arr.size() ==1){
        m_OpCode=arr[0];
    }

    //checking if operand is a number then converting and setting
    if(arr.size()==3 || arr.size()==2){
        //Check if operand is number
        if(isdigit(m_Operand[0]) ==true){
            string::size_type sz;
            m_OperandValue=atoi(m_Operand.c_str());
            m_IsNumericOperand=true;
        }
    }

    //setting NumOpCode to the numeric value
    set_numOpCode();

    //checking if assembler lang.
    if(m_NumOpCode == 999){
        if(m_OpCode =="end"){
            m_type=ST_End;
        }
        else{
            m_type=ST_AssemblerInstr;
        }
    }
    else{
        m_type=ST_MachineLanguage;
    }

    return m_type;

}
/*Instruction::InstructionType Instruction::ParseInstruction(string & a_buff)*/

/**/
/*
Name
   Instruction::LocationNextInstruction()

Synopsis
    int Instruction::LocationNextInstruction(int a_loc)
    a_loc --> location to be manipulated

Description
    takes into account for a comment, org, and ds and sets location accordingly

Return
    location
*/
/**/
//location next instruction
int Instruction::LocationNextInstruction(int a_loc ){
    int int_operand=atoi(m_Operand.c_str());

    if(m_type==ST_Comment){
        return a_loc;
    }
    //"org" starts translation at specific spot (e.g. org 200)
    if(m_OpCode=="org"){
        return a_loc=int_operand;
    }

    //"ds" adds the operand to the existing location (e.g. ds 55 => 55+200 = 255)
    else if(m_OpCode=="ds"){
        return a_loc+=int_operand;
    }

    //every other location will be 1 after the other
    else{
        return a_loc+=1;
    }
}
/*int Instruction::LocationNextInstruction(int a_loc ) */
