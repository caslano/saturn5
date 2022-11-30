#ifndef BOOST_CORE_DEMANGLE_HPP_INCLUDED
#define BOOST_CORE_DEMANGLE_HPP_INCLUDED

// core::demangle
//
// Copyright 2014 Peter Dimov
// Copyright 2014 Andrey Semashev
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>
#include <string>

#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

// __has_include is currently supported by GCC and Clang. However GCC 4.9 may have issues and
// returns 1 for 'defined( __has_include )', while '__has_include' is actually not supported:
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63662
#if defined( __has_include ) && (!defined( BOOST_GCC ) || (__GNUC__ + 0) >= 5)
# if __has_include(<cxxabi.h>)
#  define BOOST_CORE_HAS_CXXABI_H
# endif
#elif defined( __GLIBCXX__ ) || defined( __GLIBCPP__ )
# define BOOST_CORE_HAS_CXXABI_H
#endif

#if defined( BOOST_CORE_HAS_CXXABI_H )
# include <cxxabi.h>
// For some archtectures (mips, mips64, x86, x86_64) cxxabi.h in Android NDK is implemented by gabi++ library
// (https://android.googlesource.com/platform/ndk/+/master/sources/cxx-stl/gabi++/), which does not implement
// abi::__cxa_demangle(). We detect this implementation by checking the include guard here.
# if defined( __GABIXX_CXXABI_H__ )
#  undef BOOST_CORE_HAS_CXXABI_H
# else
#  include <cstdlib>
#  include <cstddef>
# endif
#endif

namespace boost
{

namespace core
{

inline char const * demangle_alloc( char const * name ) BOOST_NOEXCEPT;
inline void demangle_free( char const * name ) BOOST_NOEXCEPT;

class scoped_demangled_name
{
private:
    char const * m_p;

public:
    explicit scoped_demangled_name( char const * name ) BOOST_NOEXCEPT :
        m_p( demangle_alloc( name ) )
    {
    }

    ~scoped_demangled_name() BOOST_NOEXCEPT
    {
        demangle_free( m_p );
    }

    char const * get() const BOOST_NOEXCEPT
    {
        return m_p;
    }

    BOOST_DELETED_FUNCTION(scoped_demangled_name( scoped_demangled_name const& ))
    BOOST_DELETED_FUNCTION(scoped_demangled_name& operator= ( scoped_demangled_name const& ))
};


#if defined( BOOST_CORE_HAS_CXXABI_H )

inline char const * demangle_alloc( char const * name ) BOOST_NOEXCEPT
{
    int status = 0;
    std::size_t size = 0;
    return abi::__cxa_demangle( name, NULL, &size, &status );
}

inline void demangle_free( char const * name ) BOOST_NOEXCEPT
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

inline char const * demangle_alloc( char const * name ) BOOST_NOEXCEPT
{
    return name;
}

inline void demangle_free( char const * ) BOOST_NOEXCEPT
{
}

inline std::string demangle( char const * name )
{
    return name;
}

#endif

} // namespace core

} // namespace boost

#undef BOOST_CORE_HAS_CXXABI_H

#endif // #ifndef BOOST_CORE_DEMANGLE_HPP_INCLUDED

/* demangle.hpp
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
*/