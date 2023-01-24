/* 
   Copyright (c) Marshall Clow 2010-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#ifndef BOOST_ALGORITHM_SEARCH_DETAIL_BM_TRAITS_HPP
#define BOOST_ALGORITHM_SEARCH_DETAIL_BM_TRAITS_HPP

#include <climits>      // for CHAR_BIT
#include <vector>
#include <iterator>     // for std::iterator_traits

#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/array.hpp>
#ifdef BOOST_NO_CXX11_HDR_UNORDERED_MAP
#include <boost/unordered_map.hpp>
#else
#include <unordered_map>
#endif

#include <boost/algorithm/searching/detail/debugging.hpp>

namespace boost { namespace algorithm { namespace detail {

//
//  Default implementations of the skip tables for B-M and B-M-H
//
    template<typename key_type, typename value_type, bool /*useArray*/> class skip_table;

//  General case for data searching other than bytes; use a map
    template<typename key_type, typename value_type>
    class skip_table<key_type, value_type, false> {
    private:
#ifdef BOOST_NO_CXX11_HDR_UNORDERED_MAP
        typedef boost::unordered_map<key_type, value_type> skip_map;
#else
        typedef std::unordered_map<key_type, value_type> skip_map;
#endif
        const value_type k_default_value;
        skip_map skip_;
        
    public:
        skip_table ( std::size_t patSize, value_type default_value ) 
            : k_default_value ( default_value ), skip_ ( patSize ) {}
        
        void insert ( key_type key, value_type val ) {
            skip_ [ key ] = val;    // Would skip_.insert (val) be better here?
            }

        value_type operator [] ( key_type key ) const {
            typename skip_map::const_iterator it = skip_.find ( key );
            return it == skip_.end () ? k_default_value : it->second;
            }
            
        void PrintSkipTable () const {
            std::cout << "BM(H) Skip Table <unordered_map>:" << std::endl;
            for ( typename skip_map::const_iterator it = skip_.begin (); it != skip_.end (); ++it )
                if ( it->second != k_default_value )
                    std::cout << "  " << it->first << ": " << it->second << std::endl;
            std::cout << std::endl;
            }
        };
        
    
//  Special case small numeric values; use an array
    template<typename key_type, typename value_type>
    class skip_table<key_type, value_type, true> {
    private:
        typedef typename boost::make_unsigned<key_type>::type unsigned_key_type;
        typedef boost::array<value_type, 1U << (CHAR_BIT * sizeof(key_type))> skip_map;
        skip_map skip_;
        const value_type k_default_value;
    public:
        skip_table ( std::size_t /*patSize*/, value_type default_value ) : k_default_value ( default_value ) {
            std::fill_n ( skip_.begin(), skip_.size(), default_value );
            }
        
        void insert ( key_type key, value_type val ) {
            skip_ [ static_cast<unsigned_key_type> ( key ) ] = val;
            }

        value_type operator [] ( key_type key ) const {
            return skip_ [ static_cast<unsigned_key_type> ( key ) ];
            }

        void PrintSkipTable () const {
            std::cout << "BM(H) Skip Table <boost:array>:" << std::endl;
            for ( typename skip_map::const_iterator it = skip_.begin (); it != skip_.end (); ++it )
                if ( *it != k_default_value )
                    std::cout << "  " << std::distance (skip_.begin (), it) << ": " << *it << std::endl;
            std::cout << std::endl;
            }
        };

    template<typename Iterator>
    struct BM_traits {
        typedef typename std::iterator_traits<Iterator>::difference_type value_type;
        typedef typename std::iterator_traits<Iterator>::value_type key_type;
        typedef boost::algorithm::detail::skip_table<key_type, value_type, 
                boost::is_integral<key_type>::value && (sizeof(key_type)==1)> skip_table_t;
        };

}}} // namespaces

#endif  //  BOOST_ALGORITHM_SEARCH_DETAIL_BM_TRAITS_HPP

/* bm_traits.hpp
Z35u369HbjCs/JGKHEPD36OHn/Tir2PJS0K/+Kcdzqh4fWlNLkJy8TqraiJUcl9dSMJBrOLHe523RlkELmE9NzdKrpCYKG+af4KspbEiDHpZTMqzJzx1j+ewM6NPNHowYBwm7lp2quiyolPMIShcIqu66vk1sdYD9b5s3UZkgNuRqGpVUj6RMKuIH6snDqLoeH6EfBV64h4wzLFoY0UcZaCfl1HxLE+pIP0L+hwryZxwrZCW6Da+lzempHe1ZqvWlXaCnu5sdLp0vvo36zb18z6h5EjPC/r7OpYWgoRzrZOU4R7YEMCijk39dM2tJkBI4mGETF2llOYgl7jGrEbIdaz5kDSKCu437tuxcbNlxKjqzpJel5OKPPqTReun64Z3wi/FWeUUlEp0SXx7hhF4wA8Jh1SUC9bBrHxJDR/2OM0A++S/WxmMf4D+oRHvjqyU7wZCZLIezdPb3jVXCZeNknw9AarPcsi9PagFHK+SUsPNFXQLcZDiDq61DIuUKy/Fxzgl067Ovh1Q0ZdRjJuZYkpOLy7Z3q1InE/t0N9H/l3rU97KFuExbFNAwM8vLtqZWWVTIyfq/KyDrXR6hpGbJFf5cKKpGMnx3aM39T7g1pDrbklB651WpgxXk8LNy3B7x6IEWkI77bzG2Ag8bMTuoApRZGj582D23qVPuvXBttxf85E9D/mScYZqwnYRabR6tVTbj5uix4BqpGKM
*/