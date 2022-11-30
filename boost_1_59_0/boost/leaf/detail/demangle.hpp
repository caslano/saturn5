#ifndef BOOST_LEAF_DETAIL_DEMANGLE_HPP_INCLUDED
#define BOOST_LEAF_DETAIL_DEMANGLE_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file is based on boost::core::demangle
//
// Copyright 2014 Peter Dimov
// Copyright 2014 Andrey Semashev
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/leaf/config.hpp>

#include <cstring>

namespace boost { namespace leaf {

namespace leaf_detail
{
    template <int N>
    BOOST_LEAF_CONSTEXPR inline char const * check_prefix( char const * t, char const (&prefix)[N] )
    {
        return std::strncmp(t,prefix,sizeof(prefix)-1)==0 ? t+sizeof(prefix)-1 : t;
    }
}

template <class Name>
inline char const * type()
{
    using leaf_detail::check_prefix;
char const * t =
#ifdef __FUNCSIG__
    __FUNCSIG__;
#else
    __PRETTY_FUNCTION__;
#endif
#if defined(__clang__)
    BOOST_LEAF_ASSERT(check_prefix(t,"const char *boost::leaf::type() ")==t+32);
    return t+32;
#elif defined(__GNUC__)
    BOOST_LEAF_ASSERT(check_prefix(t,"const char* boost::leaf::type() ")==t+32);
    return t+32;
#else
    char const * clang_style = check_prefix(t,"const char *boost::leaf::type() ");
    if( clang_style!=t )
        return clang_style;
    char const * gcc_style = check_prefix(t,"const char* boost::leaf::type() ");
    if( gcc_style!=t )
        return gcc_style;
#endif
    return t;
}

} }

////////////////////////////////////////

// __has_include is currently supported by GCC and Clang. However GCC 4.9 may have issues and
// returns 1 for 'defined( __has_include )', while '__has_include' is actually not supported:
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63662
#if defined(__has_include) && (!defined(__GNUC__) || defined(__clang__) || (__GNUC__ + 0) >= 5)
#   if __has_include(<cxxabi.h>)
#       define BOOST_LEAF_HAS_CXXABI_H
#   endif
#elif defined( __GLIBCXX__ ) || defined( __GLIBCPP__ )
#   define BOOST_LEAF_HAS_CXXABI_H
#endif

#if defined( BOOST_LEAF_HAS_CXXABI_H )
#   include <cxxabi.h>
//  For some archtectures (mips, mips64, x86, x86_64) cxxabi.h in Android NDK is implemented by gabi++ library
//  (https://android.googlesource.com/platform/ndk/+/master/sources/cxx-stl/gabi++/), which does not implement
//  abi::__cxa_demangle(). We detect this implementation by checking the include guard here.
#   if defined( __GABIXX_CXXABI_H__ )
#       undef BOOST_LEAF_HAS_CXXABI_H
#   else
#       include <cstdlib>
#       include <cstddef>
#   endif
#endif

#if BOOST_LEAF_CFG_STD_STRING

#include <string>

namespace boost { namespace leaf {

namespace leaf_detail
{
    inline char const * demangle_alloc( char const * name ) noexcept;
    inline void demangle_free( char const * name ) noexcept;

    class scoped_demangled_name
    {
    private:

        char const * m_p;

    public:

        explicit scoped_demangled_name( char const * name ) noexcept :
            m_p( demangle_alloc( name ) )
        {
        }

        ~scoped_demangled_name() noexcept
        {
            demangle_free( m_p );
        }

        char const * get() const noexcept
        {
            return m_p;
        }

        scoped_demangled_name( scoped_demangled_name const& ) = delete;
        scoped_demangled_name& operator= ( scoped_demangled_name const& ) = delete;
    };

#ifdef BOOST_LEAF_HAS_CXXABI_H

    inline char const * demangle_alloc( char const * name ) noexcept
    {
        int status = 0;
        std::size_t size = 0;
        return abi::__cxa_demangle( name, NULL, &size, &status );
    }

    inline void demangle_free( char const * name ) noexcept
    {
        std::free( const_cast< char* >( name ) );
    }

    inline std::string demangle( char const * name )
    {
        scoped_demangled_name demangled_name( name );
        char const * p = demangled_name.get();
        if( !p )
            p = name;
        return p;
    }

#else

    inline char const * demangle_alloc( char const * name ) noexcept
    {
        return name;
    }

    inline void demangle_free( char const * ) noexcept
    {
    }

    inline char const * demangle( char const * name )
    {
        return name;
    }

#endif
}

} }

#else

namespace boost { namespace leaf {

namespace leaf_detail
{
    inline char const * demangle( char const * name )
    {
        return name;
    }
}

} }

#endif

#ifdef BOOST_LEAF_HAS_CXXABI_H
#   undef BOOST_LEAF_HAS_CXXABI_H
#endif

#endif

/* demangle.hpp
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
*/