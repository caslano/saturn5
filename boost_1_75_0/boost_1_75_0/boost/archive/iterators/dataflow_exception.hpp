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

    virtual const char *what( ) const throw( )
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
d4ljNIwbJeyzjE6q5x8CFINJLe4bJcpRVdxR7j4+BI9si5KzGjnntsWnibsOLrUr5+i/hNapuBvcmKpT+pscmhrAh63gi2phmvhYtq2uCWdwB5DYCAxqk+Us/XeLA+tsi6Itp7AjboYwmcH17ynlqlguVM7RO2GEdeW8tfwjtSRMhbLXgwKmlF5K4lwM62iqrtVBm0PZNsr5Z2pJ71uTTFr3IS4DQcTa/QYUS6q38xPjuOs5NBfrTbZjfGws+Prxxsfl6NkZAmylDDfR55R/7IzyOYYACkwsQm6kH2MDg7kQNXRUD2GPBc9ex/kph45f4tgSEDuj9BT4ce7cSi+3ilKvsZRr1QXMvbuaLAR9PMKxfIbxcRoIula9Qaa1wF46Vc+inkNm+DTl0I93XXKtqev6YURjNL8UmgNdOmSG0MJoDCX4t6A1OQrejeTh2fVNOn+MBwypNGVYKrexMstMx9vQsrGyAPBSS2EeNIaoyTyI/EE0JYziZgx9QW+xCwNi/cqGcSG+rKLGFrJw6whsgiFApp9iSPeaQcFQNouEsLg1tKHVZoMs3Y3eZnIr6ByaCNC18nPcfWzo3SDihhnqxGUwWf2Q+/fezsL+vc8Q+/dKZ7J//1D//fubNf9h+97QNkMYVprAhnJoo4cGd9Me5+qJfNnEy4KIf3ld8K2EfQlQgByctq5felVwWMhvAxO8zxiD8Wtj1ani0ewE
*/