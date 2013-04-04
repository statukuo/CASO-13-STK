#include "TcpListener.h"
#include "Dsm.h"
#include "DsmBrailleServer.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string.h>

namespace PracticaCaso
{
    void DsmBrailleServer::run() 
    {
       map<string, string> a;

        a.insert (a.begin(), pair<string, string>("A","*     ")); 
        a.insert (a.begin(), pair<string, string>("B","* *   "));
        a.insert (a.begin(), pair<string, string>("C","**    "));
        a.insert (a.begin(), pair<string, string>("D","** *  "));
        a.insert (a.begin(), pair<string, string>("E","*  *  "));
        a.insert (a.begin(), pair<string, string>("F","***   "));
        a.insert (a.begin(), pair<string, string>("G","****  "));
        a.insert (a.begin(), pair<string, string>("H","* **  "));
        a.insert (a.begin(), pair<string, string>("I"," **   "));
        a.insert (a.begin(), pair<string, string>("J"," ***  "));
        a.insert (a.begin(), pair<string, string>("K","*   * "));
        a.insert (a.begin(), pair<string, string>("L","* * * "));
        a.insert (a.begin(), pair<string, string>("M","**  * "));
        a.insert (a.begin(), pair<string, string>("N","** ** "));
        a.insert (a.begin(), pair<string, string>("Ñ","15"));
        a.insert (a.begin(), pair<string, string>("O","*  ** "));
        a.insert (a.begin(), pair<string, string>("P","*** * "));
        a.insert (a.begin(), pair<string, string>("Q","***** "));
        a.insert (a.begin(), pair<string, string>("R","* *** "));
        a.insert (a.begin(), pair<string, string>("S"," ** * "));
        a.insert (a.begin(), pair<string, string>("T"," **** "));
        a.insert (a.begin(), pair<string, string>("U","*   **"));
        a.insert (a.begin(), pair<string, string>("V","* * **"));
        a.insert (a.begin(), pair<string, string>("W","**  **"));
        a.insert (a.begin(), pair<string, string>("X","** ***"));
        a.insert (a.begin(), pair<string, string>("Y","** ***"));
        a.insert (a.begin(), pair<string, string>("Z","*  ***"));
        a.insert (a.begin(), pair<string, string>(".","    * "));
        a.insert (a.begin(), pair<string, string>(",","  *   "));
        a.insert (a.begin(), pair<string, string>("_","    **"));   
        a.insert (a.begin(), pair<string, string>("!","  *** "));
        a.insert (a.begin(), pair<string, string>("?","  *  *"));   
        a.insert (a.begin(), pair<string, string>("¡","  *** "));
        a.insert (a.begin(), pair<string, string>("¿","  *  *"));
        a.insert (a.begin(), pair<string, string>(" "," "));

        PracticaCaso::DsmDriver * driver = new PracticaCaso::DsmDriver("127.0.0.1", 1234, "dsm.deusto.es");

        try
        {
            driver->dsm_malloc("BRAILLE_ALPHABET", sizeof(a));
            cout << "Adding the BRAILLE_ALPHABET: " << driver->get_nid() << endl;
            try
            {
                driver->dsm_put("BRAILLE_ALPHABET", &a, sizeof(a)); 
            }
            catch (DsmException dsme) 
            {
                cerr << "ERROR: dsm_put(\"BRAILLE_ALPHABET\", a, " << sizeof(a) << ")): " << dsme << endl;
                driver->dsm_free("BRAILLE_ALPHABET");
                exit(1);
            }
        }
        catch (DsmException dsme) 
        {
            cerr << "ERROR in dsm_malloc(\"BRAILLE_ALPHABET\", a, " << sizeof(a) << ")): " << dsme << endl;
            exit(1);
        }
        sleep(20);
        delete driver;

    }   
}
