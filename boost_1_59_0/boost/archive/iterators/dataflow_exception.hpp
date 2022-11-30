#ifndef BOOST_ARCHIVE_ITERATORS_DATAFLOW_EXCEPTION_HPP
#define BOOST_ARCHIVE_ITERATORS_DATAFLOW_EXCEPTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// dataflow_exception.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifndef BOOST_NO_EXCEPTIONS
#include <exception>
#endif //BOOST_NO_EXCEPTIONS

#include <boost/assert.hpp>

namespace boost {
namespace archive {
namespace iterators {

//////////////////////////////////////////////////////////////////////
// exceptions thrown by dataflows
//
class dataflow_exception : public std::exception
{
public:
    typedef enum {
        invalid_6_bitcode,
        invalid_base64_character,
        invalid_xml_escape_sequence,
        comparison_not_permitted,
        invalid_conversion,
        other_exception
    } exception_code;
    exception_code code;

    dataflow_exception(exception_code c = other_exception) : code(c)
    {}

    const char *what( ) const throw( ) BOOST_OVERRIDE
    {
        const char *msg = "unknown exception code";
        switch(code){
        case invalid_6_bitcode:
            msg = "attempt to encode a value > 6 bits";
            break;
        case invalid_base64_character:
            msg = "attempt to decode a value not in base64 char set";
            break;
        case invalid_xml_escape_sequence:
            msg = "invalid xml escape_sequence";
            break;
        case comparison_not_permitted:
            msg = "cannot invoke iterator comparison now";
            break;
        case invalid_conversion:
            msg = "invalid multbyte/wide char conversion";
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

#endif //BOOST_ARCHIVE_ITERATORS_DATAFLOW_EXCEPTION_HPP

/* dataflow_exception.hpp
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
*/