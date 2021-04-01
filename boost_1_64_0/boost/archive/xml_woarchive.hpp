#ifndef BOOST_ARCHIVE_XML_WOARCHIVE_HPP
#define BOOST_ARCHIVE_XML_WOARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_woarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else
#include <cstddef> // size_t
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <ostream>

//#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/archive/detail/auto_link_warchive.hpp>
#include <boost/archive/basic_text_oprimitive.hpp>
#include <boost/archive/basic_xml_oarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>
//#include <boost/archive/detail/utf8_codecvt_facet.hpp>

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

template<class Archive>
class BOOST_SYMBOL_VISIBLE xml_woarchive_impl :
    public basic_text_oprimitive<std::wostream>,
    public basic_xml_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_oarchive<Archive>;
    friend class basic_xml_oarchive<Archive>;
    friend class save_access;
#endif
    //void end_preamble(){
    //    basic_xml_oarchive<Archive>::end_preamble();
    //}
    template<class T>
    void
    save(const T & t){
        basic_text_oprimitive<std::wostream>::save(t);
    }
    void
    save(const version_type & t){
        save(static_cast<unsigned int>(t));
    }
    void
    save(const boost::serialization::item_version_type & t){
        save(static_cast<unsigned int>(t));
    }
    BOOST_WARCHIVE_DECL void
    save(const char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_WARCHIVE_DECL void
    save(const wchar_t * t);
    #endif
    BOOST_WARCHIVE_DECL void
    save(const std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_WARCHIVE_DECL void
    save(const std::wstring &ws);
    #endif
    BOOST_WARCHIVE_DECL
    xml_woarchive_impl(std::wostream & os, unsigned int flags);
    BOOST_WARCHIVE_DECL
    ~xml_woarchive_impl();
public:
    BOOST_WARCHIVE_DECL void
    save_binary(const void *address, std::size_t count);

};

// we use the following because we can't use
// typedef xml_woarchive_impl<xml_woarchive_impl<...> > xml_woarchive;

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from xml_woarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE xml_woarchive :
    public xml_woarchive_impl<xml_woarchive>
{
public:
    xml_woarchive(std::wostream & os, unsigned int flags = 0) :
        xml_woarchive_impl<xml_woarchive>(os, flags)
    {
    if(0 == (flags & no_header))
        init();
    }
    ~xml_woarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::xml_woarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_XML_OARCHIVE_HPP

/* xml_woarchive.hpp
7aQX7D3SqCxD5xxWp2s8G38/ZfwgRVspOn3Dbtm5tnrZeyfUTy3hxQ2pyrRgr2M8aPZ1jgZnyKp/Cyeg+lQTsHWHDs6VbMn1T/zHkXNfG3TRiQiBTdHTKb2c1nhGbymsKHesskqLfd7pvevi7/5U3KC9QHJXNKlsRVjbgEpwmdy9EMo3F0IUAFTmgCkj8Ngq/RqCHgNKBWZ1T+njj109nT1RNVfekGMDBqwnUkS+4RG4mGLT0Sh89BGe+TFpVj1TNnuHcoI/rncUL1KP2i+AgOYggB+boGwJ2beWaECOmFg7YODrg75sKaUujEa43K+Yf/JDzkwcx3IRZqm+T1WTCkr6BA7GwUGtxmEq4Lrb6MtlVH4b9ZYKbCqs0240qMdWEgV77JWKvcK3j0A9reOpSOCOwlkVHx2leH/PfG+wFlT1Yf3Bz/OSJwS0gTqnhLXAYVfWpB2/nJ78dWX1noe6pU00176KMebOdT7HQJzAreCR6MiynW2xvXkQdxDnwRBqDfXdx46eLksKf1ch5CcfJUAdnm8VX+OTMbLdk8ZTJ2Xl3yk1YX5Ose1aqQ==
*/