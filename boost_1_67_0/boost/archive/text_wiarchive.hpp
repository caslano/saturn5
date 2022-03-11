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
    ~text_wiarchive_impl(){};
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
    ~text_wiarchive(){}
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