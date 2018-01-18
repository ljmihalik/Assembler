//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"
#include <sstream>
#include <algorithm>

/**/
/*
Name
    Assembler::Assembler( int argc, char *argv[] ): m_facc( argc, argv )

Synopsis
    Assembler::Assembler( int argc, char *argv[] ): m_facc( argc, argv )

Description
    constructor for the Assembler class
*/
/**/
Assembler::Assembler( int argc, char *argv[] ): m_facc( argc, argv )
{
    // Nothing else to do here at this point.
}
/*Assembler::Assembler( int argc, char *argv[] ): m_facc( argc, argv )*/

/**/
/*
Name
    Assembler::Assembler()

Synopsis
    Assembler::Assembler()

Description
    destructor for the Assembler class
*/
/**/
Assembler::~Assembler( )
{
}
/*Assembler::~Assembler( )*/

/**/
/*
NAME
    Assembler::print_translation() -prints translation

SYNOPSIS
    void Assembler::print_translation(int loc, string content);
    loc --> the location to be printed
    content --> the 6 digit string to be printed

DESCRIPTION
    This function prints out the translation.

*/
/**/
void Assembler::print_translation(int loc, string content){
    //accounting for the comments which shouldn't have a location
    if(loc==-1){
        cout<<""<<
        '\t'<<'\t'<<content<<
        '\t'<<'\t'<<m_inst.get_instruction()<<endl;
    }
    else{
        cout<<loc<<
        '\t'<<'\t'<<content<<
        '\t'<<'\t'<<m_inst.get_instruction()<<endl;
    }
}
/*void Assembler::print_translation(int loc, string content)*/

/**/
/*
NAME
    Assembler::validate_label() -error handling

SYNOPSIS
    bool Assembler::validate_label(string label);
    label --> the label that needs validation

DESCRIPTION
    Function to handle errors, if the size of the label is not correct or if the first position is not a letter.

*/
/**/
bool Assembler::validate_label(string label){
    if(m_inst.isLabel() == true){
        if (label.size() <1 || label.size() >10){
            string error= "Incorrect label length, must be 1 to 10 characters long";
            Errors::RecordError(error);
            return false;
        }

        if(isalpha(label.at(0))==false){
            string error= "first position not a letter";
            Errors::RecordError(error);
            return false;
        }
    }
    return false;
}
/*bool Assembler::validate_label(string label). */

/**/
/*
NAME
    Assembler::validate_operand() -error handling for operand

SYNOPSIS
    void Assembler::validate_operand();


DESCRIPTION
    Function to handle errors if the length is wrong. Has to exclude halt because it has no operand.
*/
/**/
void Assembler::validate_operand(){
    //excluding halt which has no operand
    if(m_inst.get_num_opCode()!=13){
        if (m_inst.get_operand().size() <1 || m_inst.get_operand().size() >10){
            string error= "Incorrect operand length, must be 1 to 10 characters long";
            Errors::RecordError(error);
        }

        if(m_inst.get_operand().size() >=10){
            string error="Invalid operand";
            Errors::RecordError(error);
        }
    }
}
/*void Assembler::validate_operand() */

/**/
/*
NAME
    Assembler::pass1()

SYNOPSIS
    void Assembler::pass1();

DESCRIPTION
    Function to find location of labels.

*/
/**/
void Assembler::PassI( )
{
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; ) {

        // Read the next line from the source file.
        string buff;

        if( ! m_facc.GetNextLine( buff ) ) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }

        //making everything lowercase
        transform(buff.begin(), buff.end(), buff.begin(), ::tolower);

        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction( buff );

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
        if( st == Instruction::ST_End ) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr )
        {
        	continue;
	  }
        // If the instruction has a label, record it and its location in the
        // symbol table.
        if( m_inst.isLabel( ) ) {
            m_symtab.AddSymbol( m_inst.GetLabel( ), loc );
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );

    }
}
/*void Assembler::pass1() */

/**/
/*
NAME
    Assembler::pass2();

SYNOPSIS
    void Assembler::pass2();

DESCRIPTION
    Function to generates a translation.
*/
/**/
void Assembler::PassII(){
    string content;
    int loc = 0;

    cout<<"Transaltion of Program: "<<endl;
    cout<<"Location"<<
    '\t'<<"Contents"<<
    '\t'<<"Original Statement"<<'\n';

    m_facc.rewind();

    for( ; ;){
        string buff;

        if( !m_facc.GetNextLine( buff ) ) {
            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            string error="Missing end statement";
            Errors::RecordError(error);

            print_translation(loc, content);

            cout<<"Press ENTER to continue...";
            cin.ignore();
            return;
        }

        //making everything lowercase
        transform(buff.begin(), buff.end(), buff.begin(), ::tolower);

         // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction( buff );

        //checking comments
        if( st == Instruction::ST_Comment ){
            //comments/blanks are detected--dont want to print location or content
            print_translation(-1, "");

        }

        // determine if the end is the last statement.
        else if( st == Instruction::ST_End ){
            if(m_facc.GetNextLine(buff)){
                vector <string> check_arr;
                stringstream ins(buff);
                string temp;

                //parsing to check for end as last statement
                while (ins >> temp){
                    if(temp != " " || temp != "\t" || temp != "\n"){
                        string error="End statement is not last line";
                        Errors::RecordError(error);
                    }
                }
            }

            print_translation(-1, "");
            cout<<"Press ENTER to continue...";
            cin.ignore();
            return;
        }

        //most of this if statement handles errors
        if( st == Instruction::ST_MachineLanguage || st == Instruction::ST_AssemblerInstr )
        {
            //validate label
            string label=m_inst.GetLabel();
            validate_label(label);

            //op code lookup
            int loc_num_opCode=m_inst.get_num_opCode();
            if(loc_num_opCode == -1){
                string error= "Invalid Op Code";
                Errors::RecordError(error);
            }

            //validate operand
            validate_operand();

            //memory exceeds 10,000
            if(sizeof(m_emul.get_mem()) > 10000){
                string error= "Constant too large 10,000";
                Errors::RecordError(error);
            }
            //not enough memory
            if(loc >10000){
                string error= "Insufficient memory for translation";
                Errors::RecordError(error);
            }

            //computing the "content"
            string op_str;
            string label_str;

            //if isnumeric add number with 0's in front
            if(m_inst.get_is_numeric()== false){
                op_str=to_string(m_inst.get_num_opCode());

                if(op_str != "13"){
                //accounting for the leading zeros from the location
                    label_str=to_string(m_symtab.get_sym_loc( m_inst.get_operand()));
                }

                //if num-opcode less then 10-add zero to front as a string
                if(m_inst.get_num_opCode() < 10){
                    op_str="0"+op_str;
                }

                if(loc<10){
                label_str="000"+label_str;

                }

                else if(loc < 100){
                    label_str="00"+label_str;
                }

                else if(loc <1000){
                    label_str="0"+label_str;
                }

                else{
                    label_str="0000";
                }

                //halt is a special case
                if(op_str == "13"){
                    label_str="0000";
                }
            }

            //if no numeric
            else{
                op_str="00";
                int op=m_inst.get_operandValue();
                label_str=to_string(op);

                if(op<10){
                    label_str="000"+label_str;
                }

                else if(op < 100){
                    label_str="00"+label_str;
                }

                else if(op <1000){
                    label_str="0"+label_str;
                }

                else{
                    label_str="0000";
                }

            }

            //concat everything together
            content=op_str+label_str;

            if(m_inst.get_opcode()=="org" || m_inst.get_opcode()=="ds"){
                //dont want contents to print on these 2 cases
                content="";
            }

            //adding to memory
            int num_content=atoi(content.c_str());
            m_emul.insertMemory(loc, num_content);

            //printing translation
            print_translation(loc, content);
        }

        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
    }
}
/* void Assembler::pass2() */

/**/
/*
NAME
    Assembler::RunProgramInEmulator()

SYNOPSIS
    void Assembler::RunProgramInEmulator()

DESCRIPTION
    Function checks if there are errors and if so does not run. Otherwise it calls function to run program.

*/
/**/
void Assembler::RunProgramInEmulator(){
    //if theres errors dont run
    if(Errors::GetErrors().size()>0){
        Errors::DisplayErrors();
        exit(1);
    }

    cout<<"Results from emulating program"<<endl;

    m_emul.runProgram();

    cout<<"End of emulation"<<endl;
}
/*void Assembler::RunProgramInEmulator()*/
