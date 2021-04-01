/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
Function-templates for discrete Datatypes like int, unsigned or
    any class that provides a ++ operator c.f. iterators
-----------------------------------------------------------------------------*/

#ifndef BOOST_ICL_TO_STRING_HPP_JOFA_000712
#define BOOST_ICL_TO_STRING_HPP_JOFA_000712

#include <stdio.h>
#include <string>
#include <sstream>

namespace boost{ namespace icl
{    

/// Static class template for the string representation of values
template <class Type>
struct to_string
{
    /** Converts all values of types to std::string that implement an operator << */
    static std::string apply(const Type& value)
    {
        std::stringstream repr;
        repr << value;
        return repr.str();
    }
};

}} // namespace boost icl

#endif



/* to_string.hpp
h/rl1i335n9hfLtXMiDula3374eae20Ly5Zk3rNOC8ghYqq47mwtm5N1LxXZvLxJTBWAvXKSbgXoyvVf4WGh2lmzhU6naboRh3CIPX/Kge9hkyClHg253znhKlkUplivLq6ToocDOrwHKsdmHHPHdeXxC/+Lb0QmsGWmTwACO0hwoPCUYjVjedvZCmoHIXlw3Efa5kJXBhP9JHvxotvhu09L6KyetWrT6B3ZFnOc0cA48n7dqWOCw20jNMnDIslEhD+mYrV9pM3DaXoF+pilwX8LQkwVOVVQoFRX/OOsTu4/Is6vbEGD0g5iOCgwX1dJdaOMhAt4ZbZyUfTu1SS2QW9a84MLUSOrvwAKyXnJMU8BYTz3LaaMMMRKCYhHeb447Ze2WA6Js/Dqq24EIk7J+DlkdRNEm8H5cL/fulQN2DYFJKWQYUVRO8lJM7ll6LaW4sFgN+FPmStr2N2c0gH2Z+5gD6vYdGP9fIuyP7Q0UrPXyIPCJDAtiFOZB47BCdgqbbszmrbNCGgcJGvQhp/AcpP6RrAXEgJi8xPpKEpgUMe4VdX8YCL1of0OFg==
*/