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
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
*/