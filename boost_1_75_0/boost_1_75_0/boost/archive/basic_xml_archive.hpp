#ifndef BOOST_ARCHIVE_BASIC_XML_TEXT_ARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_XML_TEXT_ARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_xml_archive.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/archive/archive_exception.hpp>

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

// constant strings used in xml i/o

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_OBJECT_ID();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_OBJECT_REFERENCE();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_CLASS_ID();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_CLASS_ID_REFERENCE();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_CLASS_NAME();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_TRACKING();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_VERSION();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_SIGNATURE();

}// namespace archive
}// namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_XML_TEXT_ARCHIVE_HPP


/* basic_xml_archive.hpp
NVv510QndA46oamVpCB8TmhvX6/thJXs731uBMRT/FG2WPTzn/B5nx3u9D6JgI2pLb1PpOO/ep+kF4q7jUnyeUIoaV5joli8fOKdfugdlFXkCDsd26Mf+ni8nz4agNxq9kO7UlkLP9QEIPRDG+IafV6nb47CfNyCyebL4+7O980pmttJVvMYqPUrjubaI7/haKLl5+9oYl5zNDHZwtH8MVw4mligOZp/C72Lo0muie5oTm7SHc3vqls4mov0fcTnaGLdOxxNBP6qo0mscM70E8GWjuYds4YPp5odTcStO5qRIxvV2xxNLOcdR+JGCiybgLdp+PxHXjdSc26iAKy7jE3nW7iMRNExRKw5cPxTvMrAz8FHh4x4BA5ZDZT9qsdFQ31hhp/H1fyEG/WgMlqzlN4ZoBF2MNYnOmzBjNu8LjBqcbvzw82fheqFG4wrJOdWSPHfx/o0plgtqDfpq11vIH7TPOJgvS9u3HK8W9efyX+haMWVrjBNBfBJUIMFQQttEYiGsBTEl85Qiudq+iNrWrh+jy3XXT8zFKZ6g31dJFEJvxrT6PP4rj6LHt/PAGB/KNM9vo9eNIFg4kLk12LERxpmFT+s6aRYQoxGfuBWveoY/YDk+jMkrGm2R1jXW/gBC8Yt41shyaY0I1v+onAf+24XnuPWbeA5/qy4BuJOBxtaJwzkYXXvx19W4IRpkPaWpltZ01MYTsZREWAz
*/