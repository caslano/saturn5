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
OpUbMdJzxhBLCFTjBmAuhShEmqZsmnxBQGWUjrU2rd9EtVJEkNGr9SCgClmXN91lhiqcTjpu6+IHgXrSp9CZ/lTET7YZS7WI8pPoeYd8kBmMzuSl9f3rc+402sFrcbn7g6yYS/kCxtmgG9ubi335p86LAr4SFW5rLDEBXlsT8i2oHo5Ma1s/TFhTH8f8B4sBaezSn11C2hflqsobryxjexNMtuZP7WTXQWwBOuLEC8Kr2cER9K6Q6iqt8flAwtjYOewnhlt/YN5wa1m8k/xcyhUzgtAxmLd15/MLTnZDfcOUmo3IHXtE92oeeCYxznnL97fxKu46ECIaKHyRJxd+MZXVkOCLaCwf4XPA2O/P5PKXSoBKZBAcTLNJHafR4wn4+4b5VztQVxOigYAffMTu42ryyOThaQr7xx46ZlVZ5MC8Dv6HGsMX7a2BDWQFjncBqAevja7xodPr7w1ix+qNHuzFhsXEfGsxqMFcxpP/GjCq5sgZmfO6buOwDYD/aAdH0mbgN1OM/CCiQ/s3lkxmL6T7L9VXlEXcXiRdp0C9d3cNNwZT8kkRGJ0vsg==
*/