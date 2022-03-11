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