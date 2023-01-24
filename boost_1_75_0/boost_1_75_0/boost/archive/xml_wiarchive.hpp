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
gDlakoX5KZvNPktiQ+cSy7t6ofK+IrjEP4zEX3Hw3Z6om28HkPxzL0megyT3KXIIQn77GM65h0iZPcekefKrh8ng7mVx8DnPRSigK48gndzJxwodkYtwEyDuEgRGgRGkrzuhMofjq3yktzsJup0QTfr7aFH/DxP9P5AHwPN6i9TVx+eRreWqkzNhcHyhr+84A7oZTzbgT2l7gdcfAhpXEuv5g32wfwEsiQDf7QM2AnANgWaRl3liYsjvTcM2OVDCkVduYDM6J0P3NP1woe11UCLHAf24Tj+ybkS2ONfBFJCDPye+HBfDD5dKu1ZeKL6DVqerBwq6gwg5Uoz+QuE0lOjckjvC2W66Cb3VuMThP8tL6IOOxq/wai4bTLSWV8aQQIItu4D1dQEVYzLNJrYYNc1a/ISsAuqOyaH4xAm958X9KFY+jHzSv7H4juRbmedj6K/rcud/nYp8/Kv4jvB4njwicS6xxczCXctbppJv4GOtaThhu5Cp02EUzvTmB3Hejug2pBb8Ya7A9C02oudgAQSGZn4i+U6kWXE/mtAWpGz5PZYvnkraTx6vcYnyGP7+KowcU7AaTY+WjyOJbi0fOZV4aJYvbH/H32Hyi+HZVlTMz59KJuvaieSnN84jhTFHNRWbt1pt7lQIALoSOnxEN75UJecdppJ3AKP5WypCHcp/C3hvIqecXs46v6mDFP6wqpjc5W/Wkrv3m7vJ
*/