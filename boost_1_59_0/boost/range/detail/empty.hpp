// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_DETAIL_EMPTY_HPP
#define BOOST_RANGE_DETAIL_EMPTY_HPP

#include <boost/range/detail/common.hpp>

namespace boost 
{
    namespace range_detail
    {
        template< typename T >
        struct range_empty;

        //////////////////////////////////////////////////////////////////////
        // default
        //////////////////////////////////////////////////////////////////////
        
        template<>
        struct range_empty<std_container_>
        {
            template< typename C >
            static bool fun( C& c )
            {
                return c.empty();
            };
        };
                    
        //////////////////////////////////////////////////////////////////////
        // pair
        //////////////////////////////////////////////////////////////////////
        
        template<>
        struct range_empty<std_pair_>
        {
            template< typename P >
            static bool fun( const P& p )
            {
                return p.first == p.second;
            }
        };
 
        //////////////////////////////////////////////////////////////////////
        // array
        //////////////////////////////////////////////////////////////////////
        
        template<>
        struct range_empty<array_>
        {
            template< typename T, std::size_t sz >
            static bool fun( T BOOST_ARRAY_REF[sz] )
            {
                if( boost_range_array == 0 )
                    return true;
                return false;
            }
        };

        //////////////////////////////////////////////////////////////////////
        // string
        //////////////////////////////////////////////////////////////////////
        
        template<>
        struct range_empty<char_ptr_>
        {
            static bool fun( const char* s )
            {
                return s == 0 || s[0] == 0;
            }
        };

        template<>
        struct range_empty<const_char_ptr_>
        {
            static bool fun( const char* s )
            {
                return  s == 0 || s[0] == 0;
            }
        };

        template<>
        struct range_empty<wchar_t_ptr_>
        {
            static bool fun( const wchar_t* s )
            {
                return  s == 0 || s[0] == 0;
            }
        };
        
        template<>
        struct range_empty<const_wchar_t_ptr_>
        {
            static bool fun( const wchar_t* s )
            {
                return  s == 0 || s[0] == 0;
            }
        };

    } // namespace 'range_detail'
    
        
    template< typename C >
    inline bool 
    empty( const C& c )
    {
        return range_detail::range_empty<  BOOST_RANGE_DEDUCED_TYPENAME range_detail::range<C>::type >::fun( c );
    }

} // namespace 'boost'


#endif

/* empty.hpp
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
*/