//  Boost string_algo library string_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_ROPE_TRAITS_HPP
#define BOOST_STRING_STD_ROPE_TRAITS_HPP

#include <boost/algorithm/string/yes_no_type.hpp>
#include <rope>
#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {

//  SGI's std::rope<> traits  -----------------------------------------------//

    
    // native replace trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_native_replace< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };

    // stable iterators trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_stable_iterators< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };

    // const time insert trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_const_time_insert< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };

    // const time erase trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_const_time_erase< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };


    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_ROPE_TRAITS_HPP

/* rope_traits.hpp
SO4UMUExXY8X60VFt2aYQi/fR4iWV8ndy44Ww2GZpVzqIAGMg0s+yV4ZQopbDh0K3Hwnmz877W3sg9hFaa/V5XBWkzslYJEx28LJu+IgbgC+X/IrxX0Sts1fBF4js5pl76NNwKbG59pidpGge2ot3CSBzCKMiHOzMpqwOzgwHxnPouBnvut2yCip0HGPmZ94FYypzk79BAOIr2tnjoBGHNphN2+zRvKHoAgLn2V/FlqnfWIDDADZ4dd00EiSSSY31V+xSgQZKQ2FG6VLavRST4+LDeJQVT5i6eeDufnUA17c0vLwYJbpSgI9azWF0JNkOoN9YsODwmMXpHadxkrEniy3q8pCMZMsgHuzhNwxu2zEouCGOFGAhN+QN+VqU1chKrXZ3B/YDcbSnXLNK/FQtsxfrTOAOOEUXbYL+G6dvij0bzH4148z1EdwnFtQgpc8gRpGViqM5otTCduteHqJxM6drKMCL1aGImd8ETaUzmSVZOeTINmacPZdwNBSTSvlCpbQXM7KTaTjfaCVhnxeVq4ST1LydyQBHDPFvskcJAFsDCZFU5KKDR2A3g==
*/