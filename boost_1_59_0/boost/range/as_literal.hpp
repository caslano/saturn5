// Boost.Range library
//
//  Copyright Thorsten Ottosen 2006. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_AS_LITERAL_HPP
#define BOOST_RANGE_AS_LITERAL_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/range/iterator_range.hpp>
#include <boost/range/detail/str_types.hpp>

#include <boost/detail/workaround.hpp>

#include <cstring>

#if !defined(BOOST_NO_CXX11_CHAR16_T) || !defined(BOOST_NO_CXX11_CHAR32_T)
#include <string>  // for std::char_traits
#endif

#ifndef BOOST_NO_CWCHAR
#include <cwchar>
#endif

namespace boost
{
    namespace range_detail
    {
        inline std::size_t length( const char* s )
        {
            return strlen( s );
        }

#ifndef BOOST_NO_CXX11_CHAR16_T
        inline std::size_t length( const char16_t* s )
        {
            return std::char_traits<char16_t>::length( s );
        }
#endif

#ifndef BOOST_NO_CXX11_CHAR32_T
        inline std::size_t length( const char32_t* s )
        {
            return std::char_traits<char32_t>::length( s );
        }
#endif

#ifndef BOOST_NO_CWCHAR
        inline std::size_t length( const wchar_t* s )
        {
            return wcslen( s );
        }
#endif

        //
        // Remark: the compiler cannot choose between T* and T[sz]
        // overloads, so we must put the T* internal to the
        // unconstrained version.
        //

        inline bool is_char_ptr( char* )
        {
            return true;
        }

        inline bool is_char_ptr( const char* )
        {
            return true;
        }

#ifndef BOOST_NO_CXX11_CHAR16_T
        inline bool is_char_ptr( char16_t* )
        {
            return true;
        }

        inline bool is_char_ptr( const char16_t* )
        {
            return true;
        }
#endif

#ifndef BOOST_NO_CXX11_CHAR32_T
        inline bool is_char_ptr( char32_t* )
        {
            return true;
        }

        inline bool is_char_ptr( const char32_t* )
        {
            return true;
        }
#endif

#ifndef BOOST_NO_CWCHAR
        inline bool is_char_ptr( wchar_t* )
        {
            return true;
        }

        inline bool is_char_ptr( const wchar_t* )
        {
            return true;
        }
#endif

        template< class T >
        inline long is_char_ptr( const T& /* r */ )
        {
            return 0L;
        }

        template< class T >
        inline iterator_range<T*>
        make_range( T* const r, bool )
        {
            return iterator_range<T*>( r, r + length(r) );
        }

        template< class T >
        inline iterator_range<BOOST_DEDUCED_TYPENAME range_iterator<T>::type>
        make_range( T& r, long )
        {
            return boost::make_iterator_range( r );
        }

    }

    template< class Range >
    inline iterator_range<BOOST_DEDUCED_TYPENAME range_iterator<Range>::type>
    as_literal( Range& r )
    {
        return range_detail::make_range( r, range_detail::is_char_ptr(r) );
    }

    template< class Range >
    inline iterator_range<BOOST_DEDUCED_TYPENAME range_iterator<const Range>::type>
    as_literal( const Range& r )
    {
        return range_detail::make_range( r, range_detail::is_char_ptr(r) );
    }

    template< class Char, std::size_t sz >
    inline iterator_range<Char*> as_literal( Char (&arr)[sz] )
    {
        return range_detail::make_range( arr, range_detail::is_char_ptr(arr) );
    }

    template< class Char, std::size_t sz >
    inline iterator_range<const Char*> as_literal( const Char (&arr)[sz] )
    {
        return range_detail::make_range( arr, range_detail::is_char_ptr(arr) );
    }
}

#endif

/* as_literal.hpp
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
*/