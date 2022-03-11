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
    ~xml_oarchive_impl();
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
// via inhertance, derived from xml_oarchive_impl instead.  This will
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
    ~xml_oarchive(){}
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