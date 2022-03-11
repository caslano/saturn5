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