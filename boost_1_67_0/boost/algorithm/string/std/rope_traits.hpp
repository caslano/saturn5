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
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
*/