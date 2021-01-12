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
pHmkqFGcNYVEvitG1OECAduD1HMZqal88CxF5Vv0S7RvgQUgiDuCTP3GmoSuqX90WYWeIX2dXDG7zFZRRRklR8VcpLRLX9JOV3AXq0agcjNFI4LhbLs51FeZwGJrUDR8i8DSZ9fPYEZ+b+T3JpkIZ9TuFvUdR/UVsFSFKwupu1UzZKu9o9os1NChdcDgx9ljPP6EvH/+CBff1Yf3q43FljWOD/cTTyibyGzATYCXL/rAfL23
*/