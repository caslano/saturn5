#ifndef BOOST_ARCHIVE_XML_OARCHIVE_HPP
#define BOOST_ARCHIVE_XML_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <ostream>

#include <cstddef> // size_t
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/archive/detail/auto_link_archive.hpp>
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
class BOOST_SYMBOL_VISIBLE xml_oarchive_impl :
    public basic_text_oprimitive<std::ostream>,
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
    template<class T>
    void save(const T & t){
        basic_text_oprimitive<std::ostream>::save(t);
    }
    void
    save(const version_type & t){
        save(static_cast<unsigned int>(t));
    }
    void
    save(const boost::serialization::item_version_type & t){
        save(static_cast<unsigned int>(t));
    }
    BOOST_ARCHIVE_DECL void
    save(const char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_ARCHIVE_DECL void
    save(const wchar_t * t);
    #endif
    BOOST_ARCHIVE_DECL void
    save(const std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_DECL void
    save(const std::wstring &ws);
    #endif
    BOOST_ARCHIVE_DECL
    xml_oarchive_impl(std::ostream & os, unsigned int flags);
    BOOST_ARCHIVE_DECL
    ~xml_oarchive_impl() BOOST_OVERRIDE;
public:
    BOOST_ARCHIVE_DECL
    void save_binary(const void *address, std::size_t count);
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

// we use the following because we can't use
// typedef xml_oarchive_impl<xml_oarchive_impl<...> > xml_oarchive;

// do not derive from this class.  If you want to extend this functionality
// via inheritance, derived from xml_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE xml_oarchive :
    public xml_oarchive_impl<xml_oarchive>
{
public:
    xml_oarchive(std::ostream & os, unsigned int flags = 0) :
        xml_oarchive_impl<xml_oarchive>(os, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~xml_oarchive() BOOST_OVERRIDE {}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::xml_oarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_XML_OARCHIVE_HPP

/* xml_oarchive.hpp
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
*/