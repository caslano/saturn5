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
vKfy7KVm9WYCPe1xBWu96J5RJTrlFHuG8uTZ3b+W7FUa/r9CJbi4XfmYPjLFslqevGievFz52omUUj+Ko+l7UKdkO6HhLLF3D3a8WuhfJosnD+kS5RhdwS2fI3ofB1AkQ9k1GG8tWGdRmWSbygu0BfBsQ2pjkgJvICnwya9YCqy5FlniQfxAJ1c/qO7+v5S7/90Y7ltRvCD9l4r7IanpXUTcrito5n9FUzS+tdcZIouTf83cn5PZE6+Cx/vjxcrzrhfodR5JbVsbaFLbmpt0qY1EA4n1+51STKlTMT42wUJXAYLf0OIFhUE84z59G8skwQQg1oHoVePcA2CqGurHoT4ZC5Ejn0qmWyQVpE5h/Wa2lxKgqL6fp6WW7116M5j1YiIvwB5dRj/9Ja8OyfIZkP+rVf+K+xpJTeieyTJ0xV8wzX6wm31dq8P+DJnq0WMSuI569DiMo8dO0GBUSz56XLt6gbrm/eSaF1pI4nsIK35YPApap+a2HUIXZFtl7L9HiR02cSY9f/Qa8gnybH5T7KD/UFLlUChr1hmQ/0C6D4+V4zi1s1bG4FdYvVSGEewBlkl9e68nSAjKh4bfKY2Y8bIrvacXkaAGONnvStR7P1r2fl0jrfe/FLtrvdzjT0i3yj30VQwctgIEMuIxJDMnsb51I+U1+4GqaCvJkuYkVdK0NebzESGY9eafEpMvz1+A/JnJ8b9M2ssdcKqi85cQoyXmaRv2sljJi98hXqz4bNglR3kLWwzrlThan172wnl2g6ubJlM6VWdHMnEHRs7DSqky5yaylGCJ88sDWP/Ui6lx8JB2oHkR8y+f8c3lVwVBaD/qQffg79W/xvrvMI1/LB6t8w/ptDwoDpuj6ik0ylE4f54hfwieaIwDLv2mIa4Mc3V7+DcxX8yPQS84Jfn6O0sp3TGPBu+jhrgFyhJ5+/AgWpNYt8UizzfbDHy+oe5d2nhL7bz+RnVk/XkN4+QaRmEa7dUDP0OH6cvs6lpPcP0HH4xL2YVDAxQxbpTvFLGhfwIdW5WTNFvwO6HuJyIFUzQxhsjtEA7N3omi2RMPgLECK+JQjOcLq0E8LbY5JlF69CnvS1SpdOJnspNvnFOBEr6T9VwjaQmo+sn9KDVGffrxWirMNqjPNZ7kZ7U28BAPpSHCMA7fhWVhsARvJ82vnoBUJe5f5yfrLIuW9JVEpDVmlrQct4qUb0AZXUARfA+uGg18WMfcMcGmyDRioYsx8XDkYE89K4unZOcVLW2OPoR6lU9xSpX3HKeZNlwa3tR7/8VTS2PHrsIhFXZ/Uevxj3+m5isy/+ldyPfTfyM/iL766NmGWqhS1BCp60LVpx88GxTeMzq85wje0aYh678Br77+cDiA1dMf3mny139vClWf2z0I/GNnAuA38odvt1xYP6nef5wJOh+3hevvSQBHxbaKUOe3KDi85jo8A8F7uEmo89v9TOD4N5oC9LNPA/F9419vDHV+d/4QCH96IPze/vBF7IXnl/SC4ADL+fyLViTzuzlXZX5kVSUZ1CE8R87SIozTs90DE0THhmRgkpDfcXWBKqt8Ke80/9Ig1oASC92DSkSKYIXfYiPdVNuScFXoTMoqP2COWU/W6OsNMtmqpiCuBf3M5J9LT7ape+M1gC9WwU+T4Ic3IFFoKUShb8Tmr3V9IlUcblk1PmmEZdXCpDHlX5hj9pR/babkYfyDvuXq30bHnKCPUSgiv43kb7CGWm403P0yjJRA+He/QDlDqNNDuU/0M0f/5uRv+clF+1nEeCtCssD56Cd32j0YTDBrvujAvayZqR2dsHjuCClaF1CxzhlOOhRZS7+hEeZ9RxEJkss0gdc1EbAnqLCPoAQ=
*/