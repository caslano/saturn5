//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_056F1F266C1311DE8E74299255D89593
#define BOOST_EXCEPTION_056F1F266C1311DE8E74299255D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //FILE * f=fopen(name,mode);
    //if( !f )
    //    BOOST_THROW_EXCEPTION(
    //        file_open_error() <<
    //        errinfo_file_name(name) <<
    //        errinfo_file_open_mode(mode) );
    typedef error_info<struct errinfo_file_open_mode_,std::string> errinfo_file_open_mode;
    }

#endif

/* errinfo_file_open_mode.hpp
ACIb9V/sV9UI1KUYVeO+2khVkxUHkXXn8RxMc+YhbjaRM648U6uYmepDKIXV6dYuJwC77eFh/5CHUbEDBcSGlY2SNh3JF6SFwAz5Aq1PvMhpgqQLFgdRgNtRXXsly+9LSwV2FQfcGnTYp02J402GjGECBfq1UcetW2izVvKDnTNXp797pZMh+c9OkgtdU8z1+eQphslszX9/rw5SMqpxhJybgq10lGOY5hGAknxAGxXBL8wNb/C3nE89a1wA32mhzCexz+31YnhTVE7KKpmSowvXtE1Z0N5CRsWOn+VVjua5clcPqw2T6oF9oGCgwd+TXutubFDlX5jrTZP+0x9xS61+MI7eh1kHiX3p6oYX0eaDxs5GO9hnfJP0RjQJgai9yPXdJ3R5OYbkNfbK6tLSI0HlFLY7y9mC01gNogzu+PBVmqBhXnaL171GwEtbyWa0D4aKpaMPhIxN7TX+diO7YRdTjIoCoI0j2RiagFG2Vx4bB47Zl11Cla/IiVcjAdgxseMb5LrocYNb2jh4aBdywJnr4ht90g/Y9jtFhS9epF5cM+wr+bZng7CoYg==
*/