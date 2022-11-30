#ifndef BOOST_ARCHIVE_BASIC_TEXT_OPRIMITIVE_HPP
#define BOOST_ARCHIVE_BASIC_TEXT_OPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_text_oprimitive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// archives stored as text - note these ar templated on the basic
// stream templates to accommodate wide (and other?) kind of characters
//
// note the fact that on libraries without wide characters, ostream is
// is not a specialization of basic_ostream which in fact is not defined
// in such cases.   So we can't use basic_ostream<OStream::char_type> but rather
// use two template parameters

#include <iomanip>
#include <locale>
#include <cstddef> // size_t

#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/io/ios_state.hpp>

#include <boost/detail/workaround.hpp>
#if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
#include <boost/archive/dinkumware.hpp>
#endif

#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
    #if ! defined(BOOST_DINKUMWARE_STDLIB) && ! defined(__SGI_STL_PORT)
        using ::locale;
    #endif
} // namespace std
#endif

#include <boost/type_traits/is_floating_point.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/limits.hpp>
#include <boost/integer.hpp>
#include <boost/io/ios_state.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/basic_streambuf_locale_saver.hpp>
#include <boost/archive/codecvt_null.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

/////////////////////////////////////////////////////////////////////////
// class basic_text_oprimitive - output of prmitives to stream
template<class OStream>
class BOOST_SYMBOL_VISIBLE basic_text_oprimitive
{
protected:
    OStream &os;
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
    boost::archive::codecvt_null<typename OStream::char_type> codecvt_null_facet;
    std::locale archive_locale;
    basic_ostream_locale_saver<
        typename OStream::char_type,
        typename OStream::traits_type
    > locale_saver;
    #endif

    /////////////////////////////////////////////////////////
    // fundamental types that need special treatment
    void save(const bool t){
        // trap usage of invalid uninitialized boolean which would
        // otherwise crash on load.
        BOOST_ASSERT(0 == static_cast<int>(t) || 1 == static_cast<int>(t));
        if(os.fail())
            boost::serialization::throw_exception(
                archive_exception(archive_exception::output_stream_error)
            );
        os << t;
    }
    void save(const signed char t)
    {
        save(static_cast<short int>(t));
    }
    void save(const unsigned char t)
    {
        save(static_cast<short unsigned int>(t));
    }
    void save(const char t)
    {
        save(static_cast<short int>(t));
    }
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    void save(const wchar_t t)
    {
        BOOST_STATIC_ASSERT(sizeof(wchar_t) <= sizeof(int));
        save(static_cast<int>(t));
    }
    #endif

    /////////////////////////////////////////////////////////
    // saving of any types not listed above

    template<class T>
    void save_impl(const T &t, boost::mpl::bool_<false> &){
        if(os.fail())
            boost::serialization::throw_exception(
                archive_exception(archive_exception::output_stream_error)
            );
        os << t;
    }

    /////////////////////////////////////////////////////////
    // floating point types need even more special treatment
    // the following determines whether the type T is some sort
    // of floating point type.  Note that we then assume that
    // the stream << operator is defined on that type - if not
    // we'll get a compile time error. This is meant to automatically
    // support synthesized types which support floating point
    // operations. Also it should handle compiler dependent types
    // such long double.  Due to John Maddock.

    template<class T>
    struct is_float {
        typedef typename mpl::bool_<
            boost::is_floating_point<T>::value
            || (std::numeric_limits<T>::is_specialized
            && !std::numeric_limits<T>::is_integer
            && !std::numeric_limits<T>::is_exact
            && std::numeric_limits<T>::max_exponent)
        >::type type;
    };

    template<class T>
    void save_impl(const T &t, boost::mpl::bool_<true> &){
        // must be a user mistake - can't serialize un-initialized data
        if(os.fail()){
            boost::serialization::throw_exception(
                archive_exception(archive_exception::output_stream_error)
            );
        }
        // The formulae for the number of decimla digits required is given in
        // http://www2.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1822.pdf
        // which is derived from Kahan's paper:
        // www.eecs.berkeley.edu/~wkahan/ieee754status/ieee754.ps
        // const unsigned int digits = (std::numeric_limits<T>::digits * 3010) / 10000;
        // note: I've commented out the above because I didn't get good results.  e.g.
        // in one case I got a difference of 19 units.
        #ifndef BOOST_NO_CXX11_NUMERIC_LIMITS
            const unsigned int digits = std::numeric_limits<T>::max_digits10;
        #else
            const unsigned int digits = std::numeric_limits<T>::digits10 + 2;
        #endif
        os << std::setprecision(digits) << std::scientific << t;
    }

    template<class T>
    void save(const T & t){
        typename is_float<T>::type tf;
        save_impl(t, tf);
    }

    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    basic_text_oprimitive(OStream & os, bool no_codecvt);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    ~basic_text_oprimitive();
public:
    // unformatted append of one character
    void put(typename OStream::char_type c){
        if(os.fail())
            boost::serialization::throw_exception(
                archive_exception(archive_exception::output_stream_error)
            );
        os.put(c);
    }
    // unformatted append of null terminated string
    void put(const char * s){
        while('\0' != *s)
            os.put(*s++);
    }
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save_binary(const void *address, std::size_t count);
};

} //namespace boost
} //namespace archive

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_TEXT_OPRIMITIVE_HPP

/* basic_text_oprimitive.hpp
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
*/