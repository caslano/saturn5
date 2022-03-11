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
// via inhertance, derived from text_oarchive_impl instead.  This will
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
    ~text_woarchive(){}
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