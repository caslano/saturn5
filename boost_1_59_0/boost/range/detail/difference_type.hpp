// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_DETAIL_DIFFERENCE_TYPE_HPP
#define BOOST_RANGE_DETAIL_DIFFERENCE_TYPE_HPP

#include <boost/range/detail/common.hpp>
#include <boost/iterator/iterator_traits.hpp>

//////////////////////////////////////////////////////////////////////////////
// missing partial specialization  workaround.
//////////////////////////////////////////////////////////////////////////////

namespace boost 
{
    namespace range_detail 
    {        
        template< typename T >
        struct range_difference_type_;

        template<>
        struct range_difference_type_<std_container_>
        {
            template< typename C >
            struct pts
            {
                typedef BOOST_DEDUCED_TYPENAME C::difference_type type;
            };
        };

        template<>
        struct range_difference_type_<std_pair_>
        {
            template< typename P >
            struct pts
            {
                typedef BOOST_RANGE_DEDUCED_TYPENAME boost::iterator_difference< BOOST_DEDUCED_TYPENAME P::first_type>::type type;                
            };
        };

        template<>
        struct range_difference_type_<array_>
        {
            template< typename A >
            struct pts
            {
                typedef std::ptrdiff_t type;
            };
        };

        template<>
        struct range_difference_type_<char_array_>
        { 
            template< typename A >
            struct pts
            {
                typedef std::ptrdiff_t type;
            };
        };

        template<>
        struct range_difference_type_<char_ptr_>
        {
            template< typename S >
            struct pts
            {
                typedef std::ptrdiff_t type;
            };         
        };
        
        template<>
        struct range_difference_type_<const_char_ptr_>
        {
            template< typename S >
            struct pts
            {
                typedef std::ptrdiff_t type;
            };         
        };
        
        template<>
        struct range_difference_type_<wchar_t_ptr_>
        {
            template< typename S >
            struct pts
            {
                typedef std::ptrdiff_t type;
            };         
        };
        
        template<>
        struct range_difference_type_<const_wchar_t_ptr_>
        {
            template< typename S >
            struct pts
            {
                typedef std::ptrdiff_t type;
            };         
        };
        
    } 
    
    template< typename C >
    class range_difference
    {
        typedef BOOST_RANGE_DEDUCED_TYPENAME range_detail::range<C>::type c_type;
    public:
        typedef BOOST_RANGE_DEDUCED_TYPENAME range_detail::range_difference_type_<c_type>::BOOST_NESTED_TEMPLATE pts<C>::type type; 
    };

}

#endif


/* difference_type.hpp
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
*/