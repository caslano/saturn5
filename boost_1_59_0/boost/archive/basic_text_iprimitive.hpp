#ifndef BOOST_ARCHIVE_BASIC_TEXT_IPRIMITIVE_HPP
#define BOOST_ARCHIVE_BASIC_TEXT_IPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_text_iprimitive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// archives stored as text - note these are templated on the basic
// stream templates to accommodate wide (and other?) kind of characters
//
// Note the fact that on libraries without wide characters, ostream is
// not a specialization of basic_ostream which in fact is not defined
// in such cases.   So we can't use basic_ostream<IStream::char_type> but rather
// use two template parameters

#include <locale>
#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
    #if ! defined(BOOST_DINKUMWARE_STDLIB) && ! defined(__SGI_STL_PORT)
        using ::locale;
    #endif
} // namespace std
#endif

#include <boost/io/ios_state.hpp>
#include <boost/static_assert.hpp>

#include <boost/detail/workaround.hpp>
#if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
#include <boost/archive/dinkumware.hpp>
#endif
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/codecvt_null.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/basic_streambuf_locale_saver.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

/////////////////////////////////////////////////////////////////////////
// class basic_text_iarchive - load serialized objects from a input text stream
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4244 4267 )
#endif

template<class IStream>
class BOOST_SYMBOL_VISIBLE basic_text_iprimitive {
protected:
    IStream &is;
    io::ios_flags_saver flags_saver;
    io::ios_precision_saver precision_saver;

    #ifndef BOOST_NO_STD_LOCALE
    // note order! - if you change this, libstd++ will fail!
    // a) create new locale with new codecvt facet
    // b) save current locale
    // c) change locale to new one
    // d) use stream buffer
    // e) change locale back to original
    // f) destroy new codecvt facet
    boost::archive::codecvt_null<typename IStream::char_type> codecvt_null_facet;
    std::locale archive_locale;
    basic_istream_locale_saver<
        typename IStream::char_type,
        typename IStream::traits_type
    > locale_saver;
    #endif

    template<class T>
    void load(T & t)
    {
        if(is >> t)
            return;
        boost::serialization::throw_exception(
            archive_exception(archive_exception::input_stream_error)
        );
    }

    void load(char & t)
    {
        short int i;
        load(i);
        t = i;
    }
    void load(signed char & t)
    {
        short int i;
        load(i);
        t = i;
    }
    void load(unsigned char & t)
    {
        unsigned short int i;
        load(i);
        t = i;
    }

    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    void load(wchar_t & t)
    {
        BOOST_STATIC_ASSERT(sizeof(wchar_t) <= sizeof(int));
        int i;
        load(i);
        t = i;
    }
    #endif
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    basic_text_iprimitive(IStream  &is, bool no_codecvt);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    ~basic_text_iprimitive();
public:
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_binary(void *address, std::size_t count);
};

#if defined(_MSC_VER)
#pragma warning( pop )
#endif

} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pop pragmas

#endif // BOOST_ARCHIVE_BASIC_TEXT_IPRIMITIVE_HPP

/* basic_text_iprimitive.hpp
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
*/