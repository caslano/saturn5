#ifndef BOOST_ARCHIVE_TEXT_OARCHIVE_HPP
#define BOOST_ARCHIVE_TEXT_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <ostream>
#include <cstddef> // std::size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_text_oprimitive.hpp>
#include <boost/archive/basic_text_oarchive.hpp>
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
class BOOST_SYMBOL_VISIBLE text_oarchive_impl :
     /* protected ? */ public basic_text_oprimitive<std::ostream>,
     public basic_text_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_oarchive<Archive>;
    friend class basic_text_oarchive<Archive>;
    friend class save_access;
#endif
    template<class T>
    void save(const T & t){
        this->newtoken();
        basic_text_oprimitive<std::ostream>::save(t);
    }
    void save(const version_type & t){
        save(static_cast<unsigned int>(t));
    }
    void save(const boost::serialization::item_version_type & t){
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
    text_oarchive_impl(std::ostream & os, unsigned int flags);
    // don't import inline definitions! leave this as a reminder.
    //BOOST_ARCHIVE_DECL
    ~text_oarchive_impl() BOOST_OVERRIDE {}
public:
    BOOST_ARCHIVE_DECL void
    save_binary(const void *address, std::size_t count);
};

// do not derive from this class.  If you want to extend this functionality
// via inheritance, derived from text_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE text_oarchive :
    public text_oarchive_impl<text_oarchive>
{
public:
    text_oarchive(std::ostream & os_, unsigned int flags = 0) :
        // note: added _ to suppress useless gcc warning
        text_oarchive_impl<text_oarchive>(os_, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~text_oarchive() BOOST_OVERRIDE {}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::text_oarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_TEXT_OARCHIVE_HPP

/* text_oarchive.hpp
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
*/