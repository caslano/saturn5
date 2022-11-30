#ifndef BOOST_ARCHIVE_TEXT_WOARCHIVE_HPP
#define BOOST_ARCHIVE_TEXT_WOARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_woarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <ostream>
#include <cstddef> // size_t

#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/archive/detail/auto_link_warchive.hpp>
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
class BOOST_SYMBOL_VISIBLE text_woarchive_impl :
    public basic_text_oprimitive<std::wostream>,
    public basic_text_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_oarchive<Archive>;
        friend basic_text_oarchive<Archive>;
        friend save_access;
    #else
        friend class detail::interface_oarchive<Archive>;
        friend class basic_text_oarchive<Archive>;
        friend class save_access;
    #endif
#endif
    template<class T>
    void save(const T & t){
        this->newtoken();
        basic_text_oprimitive<std::wostream>::save(t);
    }
    void save(const version_type & t){
        save(static_cast<unsigned int>(t));
    }
    void save(const boost::serialization::item_version_type & t){
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
    text_woarchive_impl(std::wostream & os, unsigned int flags) :
        basic_text_oprimitive<std::wostream>(
            os,
            0 != (flags & no_codecvt)
        ),
        basic_text_oarchive<Archive>(flags)
    {}
public:
    void save_binary(const void *address, std::size_t count){
        put(static_cast<wchar_t>('\n'));
        this->end_preamble();
        #if ! defined(__MWERKS__)
        this->basic_text_oprimitive<std::wostream>::save_binary(
        #else
        this->basic_text_oprimitive::save_binary(
        #endif
            address,
            count
        );
        put(static_cast<wchar_t>('\n'));
        this->delimiter = this->none;
    }

};

// we use the following because we can't use
// typedef text_oarchive_impl<text_oarchive_impl<...> > text_oarchive;

// do not derive from this class.  If you want to extend this functionality
// via inheritance, derived from text_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE text_woarchive :
    public text_woarchive_impl<text_woarchive>
{
public:
    text_woarchive(std::wostream & os, unsigned int flags = 0) :
        text_woarchive_impl<text_woarchive>(os, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~text_woarchive() BOOST_OVERRIDE {}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::text_woarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_TEXT_WOARCHIVE_HPP

/* text_woarchive.hpp
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
*/