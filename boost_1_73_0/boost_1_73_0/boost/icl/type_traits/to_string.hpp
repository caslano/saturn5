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
MYEmWXJUPNBCNDR74aegGrH05zwr1OailqUIORmtTnxSlWJWDngllx1E87QQwQJFWqH2QepslSQhX3IwP/GptGjGuWK8tIy3LbE0C2e/1ysF9Zk/gVrFbAZqRPx+9pCV1lQSI2zkL1EmtFko5oscbVRMUwogl46TdYrj7P27ix/ZOTzev+uwX+NFxEZ+uLzn6VyBjnm6FBk6KAoJwnZAiGTdgWAAzPAENt6CGaYiy1NxvyJpQS1ZPMufkBG0kR+tEVeySpM44+xJ5OTW+IxXoCpOzoFOcr9m8xRCiE876KWPYspLKZl/Hz+SrMFGAPA/EXClDECSlPwWQ0nC/RRdBHwWZ4qKMwx05ljX7p1m68xw2Ni2bo2+3mctzYHfLaaZfQLSJu7AslnfcHpDzQDf0oZDBrNszXQN3UFcd4Y7YLZ+o9kwxYJZgK/EbfaGk75h3tBEYzQeGkClRMCsa8Qx0u3eAL5oV8bQcL8Q+WvDNXXH6QIOZlpMv9VNlzkDxFPh7EpnQ0O7Gurs2rIRlWZ+Yc5Y7xnasAN823rP7QCK4g2mQO5z9N8mgA5gWF8baTfIiE1T1U8SbKC5jgV0bRDPmQxdFOPatkZsaDnIOZs4OtDQXA1ngw6BZacD83Rg0Ea+NZNY6rmGZeIEIO3a
*/