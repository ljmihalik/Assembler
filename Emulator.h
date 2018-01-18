//
//		Emulator class - supports the emulation of VC3600 programs
//
#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H

#include <string>
#include <cstring>

class emulator {

public:
    const static int MEMSZ = 10000;	// The size of the memory of the VC3600.
    emulator() {

        memset( m_memory, 0, MEMSZ * sizeof(int) );
    }
    // Records instructions and data into VC3600 memory.
    bool insertMemory( int a_location, int a_contents );

    // Runs the VC3600 program recorded in memory.
    bool runProgram( );

    int get_mem(){
        return *m_memory;
    }

private:
    int location;
    int addr;
    int m_memory[MEMSZ];       // The memory of the VC3600.
    int acceumulator;// The accumulator for the VC3600

    //functions for assembly codes
    void add();
    void sub();
    void mult();
    void divide();
    void load();
    void store();
    void read();
    void write();
    void branch();
    void branch_min();
    void branch_zero();
    void branch_pos();
    void halt();
};
#endif
