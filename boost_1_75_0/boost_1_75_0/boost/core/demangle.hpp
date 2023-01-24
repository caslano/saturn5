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
Vt8lZ3i4g5fFP2XjtGifAkRh+19JC/jIx+ALHoOvtYHHfiDgGwnnxwh49IdvBLQc/0yT+FceEx9fxPFxH1LT+Jx/3vI36mvhO62JLYbPQ9H+Lr0NfK0o/TIb+Gsi/D4b+MfxB1/MzJQwOPeO47g9/+7MzcGxnHnb2BGrYDFh0zXmd0fR1JaT6N1Z9O4ienfl04YSNg9qzsdd9O4hem8nSuspevcSvbcXvXuL3n1E776iPP1E7x1E7x1FvPmL4J1E+XQWwbuI4AEieFfRe6DovZsofpAIHix6DxG9dxe9h4ree4jee4ree4new0Tv4aL33sBDAFdPpI8IHiF67yt67yfiuT+fdgZhcsPeZxJ2u4E5/kBR/EGi98GiOENE70NFcYbxeZYTtgfBDBdcHHvGm9Gk1GlUA/uZNIVyuVzoW3YMZ1JVm8pLDDwOfSRc3/AdyFX4+UjONzsIlXNoMOeb4zyDO8DPQ+EujYYxGOKu78ytvWREgd4EwbwBjZgEcHeIc38056dqgNk0aOidkM9xSH8SKnMU0DozhpCtEK6NhPJB8Af8oeFgy4zi5xvGgm6LBnqQ3xygoYQ0d6ASwgK5uf9QSOsAcRdHcfPb90E47sH3pRFQh9CQGmiomdCJ5kC+WyGfWmjQNMgjFCq7APLeCe8BUm6uSQLlzID4ekj7ECo9AXh/CPCtIDTZI7l5tfUQRgH/eoAnQV5HgNYN
*/