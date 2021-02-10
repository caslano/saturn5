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
jM+o79LGdUkt92qx8kEJGXyaNcJkZkM1lUjZfdElTfCxJJNNH0MImvnMRJJMWYSvzdzd6tOGCesSQEk5mUacxSR/BZas/BNaAJOXjV+baYOEp3waFmmZQOb9GbstVeracM6Jp2LNYxOCMQv57SAVbtDNMO1FuyxNFZjw4pSKo+kr5B2i2t8WXGNIQegqphCt0pwmS2faTQTU3MEphcaqaudlce9BV8Uo58vjkey7SQYH1ean4yQqD3HYIxiYn3Y4qS6JMBoUfk8FQSYibPQdurAHtqg1msWemLy3GmU7EW2Uj/YF2zrIpJAKEJOjEKbEs1AKPJkHRrelr5VtDFoxBcX8RR5dZnJgVF9GockQ5TT0fv+FgOqsUMcgkaqhLQ2MSVZw0na1ChtaQrBIIV8rZuC0+jS1kFaMMTxC8xYKJbwSwVYKATzNxCpGhQTwVnaMTcwWbato/MWlRYw+GPkwhDYPwF4YKLiniZdr6oNlLIzc/Z5NceTfCpF2HfsBt0pd0g/MSO8qcgzu6nVvrrRg1utAdGGEaDu+u9TYqzoUEs8Qg1KiBQngyVYsEw10T380pl99rntLUo1eXmNYWHDu+aTQVKm/v4bf9a5msUU+k4EYLFdP+B1VMtJlWRoJG0/iaBN1N/vYtPOxiTof
*/