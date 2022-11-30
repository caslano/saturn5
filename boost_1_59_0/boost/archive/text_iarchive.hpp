#ifndef BOOST_ARCHIVE_TEXT_IARCHIVE_HPP
#define BOOST_ARCHIVE_TEXT_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>

#include <boost/config.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_text_iprimitive.hpp>
#include <boost/archive/basic_text_iarchive.hpp>
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

template<class Archive>
class BOOST_SYMBOL_VISIBLE text_iarchive_impl :
    public basic_text_iprimitive<std::istream>,
    public basic_text_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_iarchive<Archive>;
    friend class load_access;
#endif
    template<class T>
    void load(T & t){
        basic_text_iprimitive<std::istream>::load(t);
    }
    void load(version_type & t){
        unsigned int v;
        load(v);
        t = version_type(v);
    }
    void load(boost::serialization::item_version_type & t){
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
        basic_text_iarchive<Archive>::load_override(t);
    }
    BOOST_ARCHIVE_DECL void
    load_override(class_name_type & t);
    BOOST_ARCHIVE_DECL void
    init();
    BOOST_ARCHIVE_DECL
    text_iarchive_impl(std::istream & is, unsigned int flags);
    // don't import inline definitions! leave this as a reminder.
    //BOOST_ARCHIVE_DECL
    ~text_iarchive_impl() BOOST_OVERRIDE {}
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

class BOOST_SYMBOL_VISIBLE text_iarchive :
    public text_iarchive_impl<text_iarchive>{
public:
    text_iarchive(std::istream & is_, unsigned int flags = 0) :
        // note: added _ to suppress useless gcc warning
        text_iarchive_impl<text_iarchive>(is_, flags)
    {
        if(0 == (flags & no_header))
             init();
    }
    ~text_iarchive() BOOST_OVERRIDE {}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::text_iarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_TEXT_IARCHIVE_HPP

/* text_iarchive.hpp
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
*/