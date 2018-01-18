//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"

/**/
/*
Name
    FileAccess::FileAccess()

Synopsis
    void FileAccess::FileAccess()

Description
    constructor- opens file and makes sure enough arguements come in.
*/
/**/
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        cerr << "Usage: Assem <FileName>" << endl;
        exit( 1 );
    }
    // Open the file.  One might question if this is the best place to open the file.
    // One might also question whether we need a file access class.
    m_sfile.open( argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        cerr << "Source file could not be opened, assembler terminated."
            << endl;
        exit( 1 );
    }
}
/*FileAccess::FileAccess( int argc, char *argv[] )
 */

/*
Name
    FileAccess::~FileAccess

Synopsis
    FileAccess::~FileAccess()

Description
    This function closes the file.
*/

FileAccess::~FileAccess( )
{
    // Not that necessary in that the file will be closed when the program terminates.
    m_sfile.close( );
}
/*FileAccess::~FileAccess( )*/

/**/
/*
Name
    FileAccess::GetNextLine

Synopsis
    FileAccess::GetNextLine(string &a_buff);
        a_buff

Description
    This function gets the next line.

Return
    Returns false if at the end of the file. Returns true otherwise.
*/
/**/
bool FileAccess::GetNextLine( string &a_buff )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) {

        return false;
    }
    getline( m_sfile, a_buff );

    // Return indicating success.
    return true;
}
/*bool FileAccess::GetNextLine( string &a_buff ) */

/**/
/*
Name
    FileAccess::rewind()

Synopsis
    void FileAccess::rewind()

Description
    goes to beginning of file
*/
/**/
void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
}
/*void FileAccess::rewind( ) */
