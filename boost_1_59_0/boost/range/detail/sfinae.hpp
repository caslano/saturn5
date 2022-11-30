// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_DETAIL_SFINAE_HPP
#define BOOST_RANGE_DETAIL_SFINAE_HPP

#include <boost/range/config.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <utility>


namespace boost 
{
    namespace range_detail
    {          
        using type_traits::yes_type;
        using type_traits::no_type;

        //////////////////////////////////////////////////////////////////////
        // string
        //////////////////////////////////////////////////////////////////////
        
        yes_type is_string_impl( const char* const );
        yes_type is_string_impl( const wchar_t* const );
        no_type  is_string_impl( ... );
        
        template< std::size_t sz >
        yes_type is_char_array_impl( char BOOST_RANGE_ARRAY_REF()[sz] );
        template< std::size_t sz >
        yes_type is_char_array_impl( const char BOOST_RANGE_ARRAY_REF()[sz] );
        no_type  is_char_array_impl( ... );
        
        template< std::size_t sz >
        yes_type is_wchar_t_array_impl( wchar_t BOOST_RANGE_ARRAY_REF()[sz] );
        template< std::size_t sz >
        yes_type is_wchar_t_array_impl( const wchar_t BOOST_RANGE_ARRAY_REF()[sz] );
        no_type  is_wchar_t_array_impl( ... );
                                     
        yes_type is_char_ptr_impl( char* const );
        no_type  is_char_ptr_impl( ... );
        
        yes_type is_const_char_ptr_impl( const char* const );
        no_type  is_const_char_ptr_impl( ... );

        yes_type is_wchar_t_ptr_impl( wchar_t* const );
        no_type  is_wchar_t_ptr_impl( ... );
        
        yes_type is_const_wchar_t_ptr_impl( const wchar_t* const );
        no_type  is_const_wchar_t_ptr_impl( ... );
        
        //////////////////////////////////////////////////////////////////////
        // pair
        //////////////////////////////////////////////////////////////////////

        template< typename Iterator >
        yes_type is_pair_impl( const std::pair<Iterator,Iterator>* );
        no_type  is_pair_impl( ... );

        //////////////////////////////////////////////////////////////////////
        // tags
        //////////////////////////////////////////////////////////////////////

        struct char_or_wchar_t_array_tag {};
        
    } // namespace 'range_detail'
    
} // namespace 'boost'

#endif

/* sfinae.hpp
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
*/