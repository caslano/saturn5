#ifndef BOOST_ARCHIVE_TEXT_WIARCHIVE_HPP
#define BOOST_ARCHIVE_TEXT_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_wiarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <istream>

#include <boost/archive/detail/auto_link_warchive.hpp>
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
class BOOST_SYMBOL_VISIBLE text_wiarchive_impl :
    public basic_text_iprimitive<std::wistream>,
    public basic_text_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_iarchive<Archive>;
        friend load_access;
    #else
        friend class detail::interface_iarchive<Archive>;
        friend class load_access;
    #endif
#endif
    template<class T>
    void load(T & t){
        basic_text_iprimitive<std::wistream>::load(t);
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
    BOOST_WARCHIVE_DECL void
    load(char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_WARCHIVE_DECL void
    load(wchar_t * t);
    #endif
    BOOST_WARCHIVE_DECL void
    load(std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_WARCHIVE_DECL void
    load(std::wstring &ws);
    #endif
    template<class T>
    void load_override(T & t){
        basic_text_iarchive<Archive>::load_override(t);
    }
    BOOST_WARCHIVE_DECL
    text_wiarchive_impl(std::wistream & is, unsigned int flags);
    ~text_wiarchive_impl() BOOST_OVERRIDE {}
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

class BOOST_SYMBOL_VISIBLE text_wiarchive :
    public text_wiarchive_impl<text_wiarchive>{
public:
    text_wiarchive(std::wistream & is, unsigned int flags = 0) :
        text_wiarchive_impl<text_wiarchive>(is, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~text_wiarchive() BOOST_OVERRIDE {}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::text_wiarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_TEXT_WIARCHIVE_HPP

/* text_wiarchive.hpp
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
*/