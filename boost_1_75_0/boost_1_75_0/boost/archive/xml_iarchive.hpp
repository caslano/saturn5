#ifndef BOOST_ARCHIVE_XML_IARCHIVE_HPP
#define BOOST_ARCHIVE_XML_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>

#include <boost/scoped_ptr.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_text_iprimitive.hpp>
#include <boost/archive/basic_xml_iarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_iarchive;
} // namespace detail

template<class CharType>
class basic_xml_grammar;
typedef basic_xml_grammar<char> xml_grammar;

template<class Archive>
class BOOST_SYMBOL_VISIBLE xml_iarchive_impl :
    public basic_text_iprimitive<std::istream>,
    public basic_xml_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_iarchive<Archive>;
    friend class basic_xml_iarchive<Archive>;
    friend class load_access;
#endif
    // use boost:scoped_ptr to implement automatic deletion;
    boost::scoped_ptr<xml_grammar> gimpl;

    std::istream & get_is(){
        return is;
    }
    template<class T>
    void load(T & t){
        basic_text_iprimitive<std::istream>::load(t);
    }
    void
    load(version_type & t){
        unsigned int v;
        load(v);
        t = version_type(v);
    }
    void
    load(boost::serialization::item_version_type & t){
        unsigned int v;
        load(v);
        t = boost::serialization::item_version_type(v);
    }
    BOOST_ARCHIVE_DECL void
    load(char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_ARCHIVE_DECL void
    load(wchar_t * t);
    #endif
    BOOST_ARCHIVE_DECL void
    load(std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_DECL void
    load(std::wstring &ws);
    #endif
    template<class T>
    void load_override(T & t){
        basic_xml_iarchive<Archive>::load_override(t);
    }
    BOOST_ARCHIVE_DECL void
    load_override(class_name_type & t);
    BOOST_ARCHIVE_DECL void
    init();
    BOOST_ARCHIVE_DECL
    xml_iarchive_impl(std::istream & is, unsigned int flags);
    BOOST_ARCHIVE_DECL
    ~xml_iarchive_impl();
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE xml_iarchive :
    public xml_iarchive_impl<xml_iarchive>{
public:
    xml_iarchive(std::istream & is, unsigned int flags = 0) :
        xml_iarchive_impl<xml_iarchive>(is, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~xml_iarchive(){};
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::xml_iarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_XML_IARCHIVE_HPP

/* xml_iarchive.hpp
76/H+2ExtmSgiKprZd8SjMJSprsnmPi1ThjKMq4n+xQKIBHOPqYahCKKvaNn3HIcxjh0R/Fvw3y688UoiopoVgz4La+lp1LFz4fio94/3q+HXdsAxGph1+5pJz7SF7X7Qe1BrRvUaWzF/Xocwo0A0OIQrsEA88kRaK2PBa0Ud1PaPBJ+p6n2nqkzRKAe9gU+djwUzu9tg70OaO41rI3e64HWdAwkjNU/SNN3Cj9CgDY8GOyogFn8QjCuNmj0QqnHZCHr4FiwruySQNmNhfXIeqwFZRcDKWWqKfBYdEiUelJJCeG4N8MWoFSlsnNz8AvATnwJ2KQlySqGN6tz1DdJzgi87vhzreJnqR+Rk/M3qM0vjG1sxvcFr26ZHQqIJsTVr+5aETw3kY8CfwxzrSuChyTyovPEywqQ309SKNpdgNhfzg6hd/8ToRxvgHr/HMhK3Tms3C/6eqI3OTYjXHI2AMD7kyM/ArYEE5jW3guO/IGQDsH0vyqMBh4LqUS+Av5i7tVvCIGS0UmxN3hD9KSS3BOY4DoJRmB+mCE3sCLA4DqLmXDMBOIR2tbYSy5ekIaXYmA3kAGqW6fgqxF7F0F1f0F1jujHu8N13f4D7W9KGZ8DwLFxX64Oz3Lj8x6eMKqR8mY8xnTi5QYK+hfIPpzpz4ZTgwnhOqjLXp6pr/X9g4WJVfRvmPxRs6ypLDNFRJaXQR4jwaNrKrqJn0Xl
*/