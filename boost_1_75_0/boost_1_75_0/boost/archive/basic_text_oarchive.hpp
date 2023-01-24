#ifndef BOOST_ARCHIVE_BASIC_TEXT_OARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_TEXT_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_text_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// archives stored as text - note these ar templated on the basic
// stream templates to accommodate wide (and other?) kind of characters
//
// note the fact that on libraries without wide characters, ostream is
// is not a specialization of basic_ostream which in fact is not defined
// in such cases.   So we can't use basic_ostream<OStream::char_type> but rather
// use two template parameters

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/serialization/string.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_oarchive;
} // namespace detail

/////////////////////////////////////////////////////////////////////////
// class basic_text_oarchive
template<class Archive>
class BOOST_SYMBOL_VISIBLE basic_text_oarchive :
    public detail::common_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_oarchive<Archive>;
    #else
        friend class detail::interface_oarchive<Archive>;
    #endif
#endif

    enum {
        none,
        eol,
        space
    } delimiter;

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    newtoken();

    void newline(){
        delimiter = eol;
    }

    // default processing - kick back to base class.  Note the
    // extra stuff to get it passed borland compilers
    typedef detail::common_oarchive<Archive> detail_common_oarchive;
    template<class T>
    void save_override(T & t){
        this->detail_common_oarchive::save_override(t);
    }

    // start new objects on a new line
    void save_override(const object_id_type & t){
        this->This()->newline();
        this->detail_common_oarchive::save_override(t);
    }

    // text file don't include the optional information
    void save_override(const class_id_optional_type & /* t */){}

    void save_override(const class_name_type & t){
        const std::string s(t);
        * this->This() << s;
    }

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init();

    basic_text_oarchive(unsigned int flags) :
        detail::common_oarchive<Archive>(flags),
        delimiter(none)
    {}
    ~basic_text_oarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_TEXT_OARCHIVE_HPP

/* basic_text_oarchive.hpp
bqz4boE/K6aov8WKFeuFfMc3M0E2w9gJ4LiSeON8D7XvfqRCcp5c4if7W5f4ZF801qRQ7inWija/ZiEJ7iQTX7AErQxcAs7DigfryK3cRv7oEnwdbeRj4XdkmT04ZqrRbpxwt2G1pWGB4TVBG5qwt+LK7RnE0f7DGsU8hCNphIB9OR+GJ+2RJmh1q+zt/XHyn3AXpqo++y7jSbL2cEP+DgpTvRKlT2f7cM5gI6kKLycQWiDs0msUkAUAzHNcN2bf3iWM2Xq8mmN4H2HM7hjXSMZsx9P/b4zZVMDvM2aRST5jFtMwvO3z/I3ZnHXNxuz8ebox28xczZi9YgEfyNl6PJ52fkBe76hLlJz1GH+0bqIMbvtkyeWFXFMl/wF+7mLikgngM3FRmAz8Y6h5m4n7FoLAxH0NfzUTdxumwcQ9hQGQixG7h0xcsGDJdn1yXOPtJi7t/WgDk4krqs3Gli7NxK0CE9d1VxMXB85ezwTL8UuMnurqRKvP5CbrRkloEMpAoaz7LqWDxNYjPTW0LS5+UvTfjEPeNSC3cJO4SVYejPLfCH9mZxBmHy8Y2WxCbw1qYUJPBK7zezHy7KJ5sNdLrhfBDNJ2Dv4spKOvownQVresxXbS764GdmWGphpQ+r3Boo6mWuytHFRLpdX07kmUT48wY2WbUqbhgEyG6EoVmyoa5VFNv2GUf7PAZ5Q7/w5jFhRNYPEZYjmXWwU1
*/