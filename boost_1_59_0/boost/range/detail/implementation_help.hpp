// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_DETAIL_IMPLEMENTATION_HELP_HPP
#define BOOST_RANGE_DETAIL_IMPLEMENTATION_HELP_HPP

#include <boost/range/config.hpp>
#include <boost/range/detail/common.hpp>
#include <boost/type_traits/is_same.hpp>
#include <cstddef>
#include <string.h>

#ifndef BOOST_NO_CWCHAR
#include <wchar.h>
#endif

namespace boost
{
    namespace range_detail
    {
        template <typename T>
        inline void boost_range_silence_warning( const T& ) { }

        /////////////////////////////////////////////////////////////////////
        // end() help
        /////////////////////////////////////////////////////////////////////

        inline const char* str_end( const char* s, const char* )
        {
            return s + strlen( s );
        }

#ifndef BOOST_NO_CWCHAR
        inline const wchar_t* str_end( const wchar_t* s, const wchar_t* )
        {
            return s + wcslen( s );
        }
#else
        inline const wchar_t* str_end( const wchar_t* s, const wchar_t* )
        {
            if( s == 0 || s[0] == 0 )
                return s;
            while( *++s != 0 )
                ;
            return s;
        }
#endif

        template< class Char >
        inline Char* str_end( Char* s )
        {
            return const_cast<Char*>( str_end( s, s ) );
        }

        template< class T, std::size_t sz >
        BOOST_CONSTEXPR inline T* array_end( T BOOST_RANGE_ARRAY_REF()[sz] ) BOOST_NOEXCEPT
        {
            return boost_range_array + sz;
        }

        template< class T, std::size_t sz >
        BOOST_CONSTEXPR inline const T* array_end( const T BOOST_RANGE_ARRAY_REF()[sz] ) BOOST_NOEXCEPT
        {
            return boost_range_array + sz;
        }

        /////////////////////////////////////////////////////////////////////
        // size() help
        /////////////////////////////////////////////////////////////////////

        template< class Char >
        inline std::size_t str_size( const Char* const& s )
        {
            return str_end( s ) - s;
        }

        template< class T, std::size_t sz >
        inline std::size_t array_size( T BOOST_RANGE_ARRAY_REF()[sz] )
        {
            boost_range_silence_warning( boost_range_array );
            return sz;
        }

        template< class T, std::size_t sz >
        inline std::size_t array_size( const T BOOST_RANGE_ARRAY_REF()[sz] )
        {
            boost_range_silence_warning( boost_range_array );
            return sz;
        }

        inline bool is_same_address(const void* l, const void* r)
        {
            return l == r;
        }

        template<class T1, class T2>
        inline bool is_same_object(const T1& l, const T2& r)
        {
            return range_detail::is_same_address(&l, &r);
        }

    } // namespace 'range_detail'

} // namespace 'boost'


#endif

/* implementation_help.hpp
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
*/