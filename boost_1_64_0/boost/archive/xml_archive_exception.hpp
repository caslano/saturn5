#ifndef BOOST_ARCHIVE_XML_ARCHIVE_EXCEPTION_HPP
#define BOOST_ARCHIVE_XML_ARCHIVE_EXCEPTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_archive_exception.hpp:

// (C) Copyright 2007 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <exception>
#include <boost/assert.hpp>

#include <boost/config.hpp>
#include <boost/archive/detail/decl.hpp>
#include <boost/archive/archive_exception.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

//////////////////////////////////////////////////////////////////////
// exceptions thrown by xml archives
//
class BOOST_SYMBOL_VISIBLE xml_archive_exception :
    public virtual boost::archive::archive_exception
{
public:
    typedef enum {
        xml_archive_parsing_error,    // see save_register
        xml_archive_tag_mismatch,
        xml_archive_tag_name_error
    } exception_code;
    BOOST_ARCHIVE_DECL xml_archive_exception(
        exception_code c,
        const char * e1 = NULL,
        const char * e2 = NULL
    );
    BOOST_ARCHIVE_DECL xml_archive_exception(xml_archive_exception const &) ;
    virtual BOOST_ARCHIVE_DECL ~xml_archive_exception() BOOST_NOEXCEPT_OR_NOTHROW ;
};

}// namespace archive
}// namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif //BOOST_XML_ARCHIVE_ARCHIVE_EXCEPTION_HPP

/* xml_archive_exception.hpp
wpMiHM0hH/LzsQkG4VqUnndHqGeRLcaMrDHKrzRJGwQlXb3gbMOBopenz3rWb2qcEeAcyHcfBRuGq8DN+h3yZSvf3FqytJVDRQn9u/j1muGEwwfEiCLD0UtHV4aRa4lJx6uhqSps8CHtlg/2RGxnpdkHUowimwmBn6pzFLOaiNt4AH/Uplu4RbQvRGVpQ1CUMTYWA6BsVwvQt1i3AtWegxnaXZzetju1t9RPw9wIKwTuaJOb3myGeNzTvIK+jDWs9ulO0taA6QQ/RgQsp9VkmRzc2wD20CS0C/7mkdhj0+38bLuRoSNe7PeiJ/X2cOR45y8DS+CocmU1XEQGpl8pUt/LO9aF5JDgSet5OeifYjmhHAa4YgP4jTaWuaE8ig5MicLCrNhGR3plAgZxpp0qPWqjJOfrOWnlJmIU4WqsfER9bkcUua9IxjNokZTH8xf+bRm9UBWmVGfoWTyuYSPSzp3JROzvij8YDC8IxCPoQIAHveJHEH/PSEzgmraaUacnNJc1/p+z27QvWgbs7p7KXFb/QSrIsgtKcTbealhES/Q5wckoVOhoe30A8A==
*/