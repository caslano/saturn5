// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_DETAIL_COMMON_HPP
#define BOOST_RANGE_DETAIL_COMMON_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/range/config.hpp>
#include <boost/range/detail/sfinae.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <cstddef>

//////////////////////////////////////////////////////////////////////////////
// missing partial specialization  workaround.
//////////////////////////////////////////////////////////////////////////////

namespace boost 
{
    namespace range_detail 
    {        
        // 1 = std containers
        // 2 = std::pair
        // 3 = const std::pair
        // 4 = array
        // 5 = const array
        // 6 = char array
        // 7 = wchar_t array
        // 8 = char*
        // 9 = const char*
        // 10 = whar_t*
        // 11 = const wchar_t*
        // 12 = string
        
        typedef mpl::int_<1>::type    std_container_;
        typedef mpl::int_<2>::type    std_pair_;
        typedef mpl::int_<3>::type    const_std_pair_;
        typedef mpl::int_<4>::type    array_;
        typedef mpl::int_<5>::type    const_array_;
        typedef mpl::int_<6>::type    char_array_;
        typedef mpl::int_<7>::type    wchar_t_array_;
        typedef mpl::int_<8>::type    char_ptr_;
        typedef mpl::int_<9>::type    const_char_ptr_;
        typedef mpl::int_<10>::type   wchar_t_ptr_;
        typedef mpl::int_<11>::type   const_wchar_t_ptr_;
        typedef mpl::int_<12>::type   string_;
        
        template< typename C >
        struct range_helper
        {
            static C* c;
            static C  ptr;

            BOOST_STATIC_CONSTANT( bool, is_pair_                = sizeof( boost::range_detail::is_pair_impl( c ) ) == sizeof( yes_type ) );
            BOOST_STATIC_CONSTANT( bool, is_char_ptr_            = sizeof( boost::range_detail::is_char_ptr_impl( ptr ) ) == sizeof( yes_type ) );
            BOOST_STATIC_CONSTANT( bool, is_const_char_ptr_      = sizeof( boost::range_detail::is_const_char_ptr_impl( ptr ) ) == sizeof( yes_type ) );
            BOOST_STATIC_CONSTANT( bool, is_wchar_t_ptr_         = sizeof( boost::range_detail::is_wchar_t_ptr_impl( ptr ) ) == sizeof( yes_type ) );
            BOOST_STATIC_CONSTANT( bool, is_const_wchar_t_ptr_   = sizeof( boost::range_detail::is_const_wchar_t_ptr_impl( ptr ) ) == sizeof( yes_type ) );
            BOOST_STATIC_CONSTANT( bool, is_char_array_          = sizeof( boost::range_detail::is_char_array_impl( ptr ) ) == sizeof( yes_type ) );
            BOOST_STATIC_CONSTANT( bool, is_wchar_t_array_       = sizeof( boost::range_detail::is_wchar_t_array_impl( ptr ) ) == sizeof( yes_type ) );
            BOOST_STATIC_CONSTANT( bool, is_string_              = (is_const_char_ptr_ || is_const_wchar_t_ptr_));
            BOOST_STATIC_CONSTANT( bool, is_array_               = boost::is_array<C>::value );
            
        };
        
        template< typename C >
        class range
        {
            typedef BOOST_RANGE_DEDUCED_TYPENAME   boost::mpl::if_c< ::boost::range_detail::range_helper<C>::is_pair_,
                                                                  boost::range_detail::std_pair_,
                                                                  void >::type pair_t;
            typedef BOOST_RANGE_DEDUCED_TYPENAME   boost::mpl::if_c< ::boost::range_detail::range_helper<C>::is_array_,
                                                                    boost::range_detail::array_,
                                                                    pair_t >::type array_t;
            typedef BOOST_RANGE_DEDUCED_TYPENAME   boost::mpl::if_c< ::boost::range_detail::range_helper<C>::is_string_,
                                                                    boost::range_detail::string_,
                                                                    array_t >::type string_t;
            typedef BOOST_RANGE_DEDUCED_TYPENAME   boost::mpl::if_c< ::boost::range_detail::range_helper<C>::is_const_char_ptr_,
                                                                    boost::range_detail::const_char_ptr_,
                                                                    string_t >::type const_char_ptr_t;
            typedef BOOST_RANGE_DEDUCED_TYPENAME   boost::mpl::if_c< ::boost::range_detail::range_helper<C>::is_char_ptr_,
                                                                    boost::range_detail::char_ptr_,
                                                                    const_char_ptr_t >::type char_ptr_t;
            typedef BOOST_RANGE_DEDUCED_TYPENAME   boost::mpl::if_c< ::boost::range_detail::range_helper<C>::is_const_wchar_t_ptr_,
                                                                    boost::range_detail::const_wchar_t_ptr_,
                                                                    char_ptr_t >::type const_wchar_ptr_t;
            typedef BOOST_RANGE_DEDUCED_TYPENAME   boost::mpl::if_c< ::boost::range_detail::range_helper<C>::is_wchar_t_ptr_,
                                                                    boost::range_detail::wchar_t_ptr_,
                                                                    const_wchar_ptr_t >::type wchar_ptr_t;
            typedef BOOST_RANGE_DEDUCED_TYPENAME   boost::mpl::if_c< ::boost::range_detail::range_helper<C>::is_wchar_t_array_,
                                                                    boost::range_detail::wchar_t_array_,
                                                                    wchar_ptr_t >::type wchar_array_t;
            typedef BOOST_RANGE_DEDUCED_TYPENAME   boost::mpl::if_c< ::boost::range_detail::range_helper<C>::is_char_array_,
                                                                    boost::range_detail::char_array_,
                                                                    wchar_array_t >::type char_array_t;
        public:
            typedef BOOST_RANGE_DEDUCED_TYPENAME   boost::mpl::if_c< ::boost::is_void<char_array_t>::value,
                                                                    boost::range_detail::std_container_,
                                                                    char_array_t >::type type;  
        }; // class 'range' 
    }
}
        
#endif


/* common.hpp
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
*/