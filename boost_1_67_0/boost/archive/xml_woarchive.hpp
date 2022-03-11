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
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
*/