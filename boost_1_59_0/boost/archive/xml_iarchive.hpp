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
    ~xml_iarchive_impl() BOOST_OVERRIDE;
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
    ~xml_iarchive() BOOST_OVERRIDE {}
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