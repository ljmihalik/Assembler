//
//      Implementation of the Errors class.
//
#include "stdafx.h"
#include "Errors.h"

//needs to be here
vector<string> Errors::m_ErrorMsgs;

/**/
/*
Name
    Errors::RecordError()

Synopsis
    void Errors::RecordError(string &a_emsg)
    a_emsg --> error to be put into vector

Description
    adds errors into vector
*/
/**/
void Errors::RecordError( string &a_emsg ){
    m_ErrorMsgs.push_back(a_emsg);
}
/*void Errors::RecordError( string &a_emsg ) */

/**/
/*
Name
    Errors::DisplayErrors()

Synopsis
    void Errors::DisplaayError()

Description
    prints error vector
*/
/**/
void Errors::DisplayErrors( ){
    for(int iter=0; iter<m_ErrorMsgs.size(); iter++){
        cout<<m_ErrorMsgs[iter]<<endl;
    }
}
/*void Errors::DisplayErrors( ) */
