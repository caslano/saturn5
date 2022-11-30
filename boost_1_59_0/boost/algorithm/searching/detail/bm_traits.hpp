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
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
*/