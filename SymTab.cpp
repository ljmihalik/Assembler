//
//		Implementation of the symbol table class.
//
#include "stdafx.h"
#include "SymTab.h"
#include <iomanip>
#include <string>
#include "Errors.h"
/**/
/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( char *a_symbol, int a_loc );
    a_symbol  --> the symbol to be added to map
    a_loc  --> the location to be added to map

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.
*/
/**/
void SymbolTable::AddSymbol( string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st;
    st = m_symbolTable.find( a_symbol );

    if( st != m_symbolTable.end()){
        st->second = multiplyDefinedSymbol;
        return;
    }

    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}
//void SymbolTable::AddSymbol( string &a_symbol, int a_loc )

/**/
/*
NAME
    SymbolTable::get_sym_loc() -gets location of symbol

SYNOPSIS
    int SymbolTable::get_sym_loc(string symbol);
    symbol --> symbol that needs location corresponding to it

DESCRIPTION
    This function will handle the error if the symbol is not in the symbol table.
    If the symbol is in the table it will assign the integer sym_loc= m_symbolTable[symbol] and return the location.
RETURN
   Returns an integer of the symbols location.
*/
/**/
int SymbolTable::get_sym_loc(string symbol){
    if(m_symbolTable.find(symbol) == m_symbolTable.end()){
        string error=symbol+"symbol not found";
        Errors::RecordError(error);
    }
    int sym_loc=m_symbolTable[symbol];

    return sym_loc;
}
/*int SymbolTable::get_sym_loc(string symbol) */

/**/
/*
Name
    SymbolTable::DisplaySymbolTable - prints symbol table

Synopsis
    SymbolTable::DisplaySymbolTable()

Description
    This function prints the contents of the map that holds the symbol number, and the symbol, location will also be printed.
*/
/**/
void SymbolTable::DisplaySymbolTable(){
    int count_map=0;
    cout<<"Symbol#" <<
        '\t'<<"Symbol"<<
        '\t'<<"Location"<<'\n';

    for(auto const& size_map : m_symbolTable){
        cout <<count_map<<
        '\t'<<size_map.first<<
        '\t'<<size_map.second<<'\n';
        count_map++;
    }
    cout<<"Press enter to continue..."<<endl;
    cin.ignore();
}
/*void SymbolTable::DisplaySymbolTable()*/

/*
Name
    SymbolTable::LookupSymbol - find symbol

Synopsis
  SymbolTable::LookupSymbol(string &a_symbol, int &a_loc);
    a_symbol - the symbol that will be checked if it is in the map.
    a_loc - the location at which the symbol is.

Description
    this function will use string's find function to check if the symbol exists in the map.

Returns
    returns true if the location from the find function is equal to the location brought in (a_loc).
    false if not found.
*/
bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc){
    //new map to keep track of the symbol found
    map<string, int>::iterator found;
    found = m_symbolTable.find(a_symbol);

    if (found->second == a_loc){
        return true;
    }
    return false;

}
/*bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc) */
