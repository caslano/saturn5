#ifndef BOOST_ARCHIVE_ITERATORS_BASE64_EXCEPTION_HPP
#define BOOST_ARCHIVE_ITERATORS_BASE64_EXCEPTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// base64_exception.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifndef BOOST_NO_EXCEPTIONS
#include <exception>

#include <boost/assert.hpp>

namespace boost {
namespace archive {
namespace iterators {

//////////////////////////////////////////////////////////////////////
// exceptions thrown by base64s
//
class base64_exception : public std::exception
{
public:
    typedef enum {
        invalid_code,       // attempt to encode a value > 6 bits
        invalid_character,  // decode a value not in base64 char set
        other_exception
    } exception_code;
    exception_code code;

    base64_exception(exception_code c = other_exception) : code(c)
    {}

    virtual const char *what( ) const throw( )
    {
        const char *msg = "unknown exception code";
        switch(code){
        case invalid_code:
            msg = "attempt to encode a value > 6 bits";
            break;
        case invalid_character:
            msg = "attempt to decode a value not in base64 char set";
            break;
        default:
            BOOST_ASSERT(false);
            break;
        }
        return msg;
    }
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif //BOOST_NO_EXCEPTIONS
#endif //BOOST_ARCHIVE_ITERATORS_ARCHIVE_EXCEPTION_HPP

/* base64_exception.hpp
tl5GX9L3x0WhxkP1iyWVF27A/NA/N+kqRyqPJbWPhBcV6rvujEjlIgQMcqWHFxu8ys1R60Elke92+WfrIT+/sUDSeOtI5WTrGQgi9RtFT3E9Ncnz/e/g+XG+sRbz7WjJ7Y50Df8n5/ur/WP7i/1Tws/n08ALQ2EdKX84n3+3PRT6ovYf5T/YvzgfkV+cTyS8qOEl+e18fCm3lyNdW6AcfX6R8KJBfZfiM1R79H42kPaTCV7opPFtXn+4nxjy/fSjPF9uCutFzwdrSeF8UfsoQuo3lmw8btL+vjDDIFcOUn4s44/1lEjtNRXn63H+op4Gqd5jnfl6XL+oZ0Sq1yE4X2/ZL+o5keqF7p6vt/wX9cJJ9ab3zder+0W9FFK9BhLXF9NQrldIqvfaFEPxHBtI+81Aus+2/LN4hy3q97pjFDzfzyMsaVz4B/0M2AbSvLoi6H/0b2vuH/yvBsV7dDt6eKHTgB+aF/NpDlK29V+sx3++nBle7H/QH8bm9/1xk/oLJ+cd5KP9JYpMX3VI5acXY1Drh3wb1H5Q4LqZP+X5eJDyd/BQ9s9EUnn20fn9pyXrN4NsPvCa1y+b3/O30P+f4wWZvaDWSXk95OM2oMrR89U59Hv9GvvFfDEBP/Irjmy+bAGo8Ujl1Gi9CKA8H4zt7/dPMoDyfNRI+Y2qlPdPh1SevfPH8WJt/8J+fjGef8CP50FFbj8BKN6i12f3+/EyoB2l+deQ8r2FMRT95xmpnJmPcnw6Q6GcGq1HgT+X01DQj67IH/XfibQeul+sRySQ8no0SPkCapTXYx2Isg/UeEr2v9+/8EDK55UB+ejziiPXgUCU7qF4m40ej1JcGPjP+fMIqd1YJD2ZP1OOhyLJxmUMQvGXgt9yB/0+njJL5fopHqKCl+Q3P0P1j7ZfrMOPeshN0g+jb+cTRHk/jIJ+7y9OQZT9RdLx9+ftH0TZvi6S8t+i/IWKgj07kcWzKX8xXnbQn503Ndl8GoL+sfcf5OeNIfG/YTGG4vspNlL5PkPS+GTnzU0qF9+Ctm94OVGOFyS/tYd26Plg/mI+jJTmg+bf4d/vr9LXdn8SL5HzIvjH/Y0g50IwZf92OkxZb+S+2UPwn533T58XBP/ev2uC/yL+D/6FPhLn82l/Md+ZX8yXO+T3/icSQtn/som/Py+5kF+cVwhq/hTGcyGVP+QilZP1e4RUvmEJGX+cfx8fhIf8c3qTQWrXJfGj/2Q7/379hUi7X6fsqD/7/AkT/et6aHtKIeuP8S/sxcnlx/ljv96j9qvrF/MvPMNF0T4ZMaQUOt8uju3H8bpcfr9fbKH/3Pmg4gGKPJck9ZtxgOz9gStle2H7Nm7on/l3LLlekdqNkc4jjuzzGf/Q38fj5P5PS/65Ean9qZVk++v6Y7yl8XW/Uf6f8Yv11IT+Z/wx2+33/vjsD/f3p8/rSO1io/+9/FRyp8xPSdJ15g/nS/75GHfY9/n8W+c79hfzlQv7BX/Dfs976zDKvE/x+L3/eoT92ecf/0//T/9P/0//Kwm/ztaFaINccaQrwRb+M1/m5D6f5wiXbz/r1TXdS4CfZNoQHFw0HSwdSflQw8rGAefiSERlQiKi6zr/PZ/ggPzwkoBXdXRwQXdFSq4OTkRHF4IF1FB2cSE6Y1Djqzu4EezgR6F4NZwLDpWvZmNFcHYhZaPrk8ZCF8BPS5XtrGDWLtb2GEg4VxfrbwNBGYyPyiH1oww5MFUbCxzZIJAsHO2diARnZ3jy2A/9ouehSqqDagx7i4f/f70621g5fC+Be8JPqyTVR68SlU/a0Z/q4yjNGvK/zfjn/fr5SEjr19Pbq6mir6eui/kxH3bJxtzVheBsqgs=
*/