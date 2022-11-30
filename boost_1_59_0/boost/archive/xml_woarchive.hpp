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

#include <boost/archive/detail/auto_link_warchive.hpp>
#include <boost/archive/basic_text_oprimitive.hpp>
#include <boost/archive/basic_xml_oarchive.hpp>
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
    ~xml_woarchive_impl() BOOST_OVERRIDE;
public:
    BOOST_WARCHIVE_DECL void
    save_binary(const void *address, std::size_t count);

};

// we use the following because we can't use
// typedef xml_woarchive_impl<xml_woarchive_impl<...> > xml_woarchive;

// do not derive from this class.  If you want to extend this functionality
// via inheritance, derived from xml_woarchive_impl instead.  This will
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
    ~xml_woarchive() BOOST_OVERRIDE {}
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