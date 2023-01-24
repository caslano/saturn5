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
Ghkh7TGOjTtRUAsGbUy6av/GU2Div3RuEC3HdMGv7amZ5BzWBcN2UNO4Exv6eZ7Gzz48Jiue/KijF/FZ7laIzrMhADD+BMaAQCo5bwJC7z5YA+HaQ50HkaSNGNhnMPoiVvbJIGD2Rgxc5CgttLJ3Kbvdl30Nsuoeigz0/CB6MMZ/6owvi6rZRiyyn2MF9HuJ5cJv9FmoMY637iKCQYHcWjs0x+7IiAYtKuZ7Oiaz4r6WnKu2A8dO/l6v5Q0Sz+yjokUomvJCLdwhnikGJ13cZY7sj0hlqybgiwM0r9uIG81h3kNASeGzVsordPu4tLfUbRQX3CWAqY9vjdTdeD0heyWjXkQ6t8/Ty1V7eBrbqBckKnSHrmeC0ZpqA98TL5Rjj/uKJefRgcDie9NYA6i1BGuaXmU8VSGpGK6qOhNmPYTvIhpn6S8z976KV0rEROI1mz+qD7MhkfiyYCDlf4L8vaOAvw+zcVsQ3D6SdgxvbwysZYqkEoOo0Icq1DxAhEVf5+mAV7Dy+6HYZcksXae8NZR0yt5CNDjPYQSWdbhnZFAwlgWQTGN/ice/x9C0S+eFhXrpZCjFIEzFD+BOmXIDQ0uFs3WUy6RcT7aMctdCRVkm5epCG+jRBvxjKUhPYKkyvrIT35oPyzouPSu2neQsuAaiML22QfhZeF2TEfQp7PauMPjlMVDCujyCpAtWhiIe9/i4TspLeNUaWChX
*/