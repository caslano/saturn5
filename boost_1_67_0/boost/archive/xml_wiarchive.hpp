#ifndef BOOST_ARCHIVE_XML_WIARCHIVE_HPP
#define BOOST_ARCHIVE_XML_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_wiarchive.hpp

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

#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/archive/detail/auto_link_warchive.hpp>
#include <boost/archive/basic_text_iprimitive.hpp>
#include <boost/archive/basic_xml_iarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>
// #include <boost/archive/detail/utf8_codecvt_facet.hpp>

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
typedef basic_xml_grammar<wchar_t> xml_wgrammar;

template<class Archive>
class BOOST_SYMBOL_VISIBLE xml_wiarchive_impl :
    public basic_text_iprimitive<std::wistream>,
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
    std::locale archive_locale;
    boost::scoped_ptr<xml_wgrammar> gimpl;
    std::wistream & get_is(){
        return is;
    }
    template<class T>
    void
    load(T & t){
        basic_text_iprimitive<std::wistream>::load(t);
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
        basic_xml_iarchive<Archive>::load_override(t);
    }
    BOOST_WARCHIVE_DECL void
    load_override(class_name_type & t);
    BOOST_WARCHIVE_DECL void
    init();
    BOOST_WARCHIVE_DECL
    xml_wiarchive_impl(std::wistream & is, unsigned int flags) ;
    BOOST_WARCHIVE_DECL
    ~xml_wiarchive_impl();
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE xml_wiarchive :
    public xml_wiarchive_impl<xml_wiarchive>{
public:
    xml_wiarchive(std::wistream & is, unsigned int flags = 0) :
        xml_wiarchive_impl<xml_wiarchive>(is, flags)
    {
    if(0 == (flags & no_header))
        init();
    }
    ~xml_wiarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::xml_wiarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_XML_WIARCHIVE_HPP

/* xml_wiarchive.hpp
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
*/