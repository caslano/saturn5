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
kbNWZ7mxwQ9anU1yy/vHIeC3bd+YGzp9R04/cj64fccZOWzTEF5wEMa0m+O0m0a3bxNqK3eLlosQBVrI9c/Ztnn4hL7n2+7aBONbxhfrBa6l+vz9t8p9H0nKs7UZfid+FO1Tv8jLhYpc6Swo6eTQ4xEaHrudAR7udHapzt/lhTSzSdv3nLLcpD+WJ38pmh+d5sytfj1xDnaSC00VwrrtV0mWP7fRIKzbomxrYWeArtQszJRpn/bUtK1bO1rZEodTudwESlCFafahp2m6feXGtP/dEGpXlIv2dfnwGR9+psnRVSRq8xxS22uyfzY2Pt/1961cm968qV/dBLLfATxjKcHr9f5adeYA703yGo9pooJsV4wfDGb5FYmf4tUPpmy7SeCpnZJJ8dXFIfk3uDVeOwxQy3aYvEaf6aUBzzllwnm5rY8zbWns8Gm1Hb+s7W6vLRYu1ZZ5+zo7+N1hfx3Zs8DDCTQebfv39xtc1cP17e9DjIvbManO7C3lzsI5hp0Hu1vSKBXs/DprqanT0jj5/UafWuOc/eruCB4S237/O50X8rJauGf9I88L/3wGUvIHciX73WeibaiKqE1s2/eNDGwyuKbgUEPXhwPu+g6c/mphNr+/K4DrMxv/PCeRN51UFDf22rfU4NSNy3JBSzM810lbn+d+0y48uzkgODyYgW8b9aPbndl3T71aiX6XHz1HeqYeU9WohPsP9c7WBOypgjXhv1E551Adxn+n5tmMwwj43yI9h/D+W53P8+o7wPm+o4/2+m1sPDe1cf9EuVKju/KAa14WdTCGmykJFvzCt8ypDWKzhSM6G93Ir5QlckV+89CcKUh9znv79byUp01dc8m+fM1/D0HVs+R0nX3/fFmXxe9sjqrbqI6h65UuT//ZfLJHqe/46UOOse+klxsHDD5r+0K7LrEe4bhQ3vAiaaN65NlWzTs0sHa4QM8T5BOKv0wkssNLDT6cYy9bSvLtS48mzh0IxuBszP1qobO5gQgZzI0lx3oxzs9JsfTbPl64lOEI8GX3Nz8vMnjJW/ieho/Tze064OP70H+TO/g4K9vd15glJNYXnI9H+wK44tfpGY/KWGNxbeWxsXz3Nd7+Ri0GaBvb/9A+hM6yU78zZ/xmfX59uNdLz95KxbnOtNR5W0pm+Lwxuj9LZXVQ+52tlQMfWxX1scccncUvtAHcm/sA9k90do8DmUsguz86Fpek8032bJhPSXkvn+0yXs1lS0Tz+S2GBjl/fdbZ812qcZgjur2/5r/dtp0uT02b9fsdBo6x2Wf4Gr3e6eJZd182/MTK7uy8A+dDUb9+zLGxe+UDJob3pi2zk0Yc0M1H09+/Zn6atevmpVm9fn4+a/sRT9xYo9EIAErZtC5/LeAL7o8v+xfg7hy/iQh4Sox3cGCgXpqXuPfBuNYy0NlUxnUi4xZPhk+Pjqf0HxX6lx2m6RXs4wI7/7A5ecAwWuYnhP7cwy2PTwvsWYfPzUMZznwj6+HUG82dxcx0MCLn4k8+NpajfYlzqQKWPMJ9BTgUWybUW9earfWBrwU4HErlkvykRwOFAjIe26+bNcLEXN6b15JSs1ilayd8H+6baIsNf0VdR8zqUt9qIROLge4B2q+ch1Z/ktHJvr/Vu2S7onH5JtmjJgXE3xCOp9Si8GLJo/+uyU+BisLBiuA3p3DztqmBf1/D5ZeHa6k//xiwfvhuDvjzOoptaqxisW0y6n9nZbqmh6BoS/WjW9PxAYzW2du8s9tiklfXtAtcz/0VaMaeOIA7mPo6aibr1wYuV0dJj98anFyRPcg6+r5oY9DvUh2tg7IefwRuFAc4apXqbA6rMnbMhmdFbXinV//kbxIOmjM=
*/