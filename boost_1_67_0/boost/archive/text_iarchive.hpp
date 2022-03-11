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
    ~text_iarchive_impl(){};
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
    ~text_iarchive(){}
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