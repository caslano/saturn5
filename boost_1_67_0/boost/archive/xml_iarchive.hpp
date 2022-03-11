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
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
*/