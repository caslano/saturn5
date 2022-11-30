//  Boost string_algo library slist_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003. 
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_SLIST_TRAITS_HPP
#define BOOST_STRING_STD_SLIST_TRAITS_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/algorithm/string/yes_no_type.hpp>
#include BOOST_SLIST_HEADER 
#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {

//  SGI's std::slist<> traits  -----------------------------------------------//


    // stable iterators trait
        template<typename T, typename AllocT>
        class has_stable_iterators< BOOST_STD_EXTENSION_NAMESPACE::slist<T,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<has_stable_iterators<T>::value> type;
        };

    // const time insert trait
        template<typename T, typename AllocT>
        class has_const_time_insert< BOOST_STD_EXTENSION_NAMESPACE::slist<T,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<has_const_time_insert<T>::value> type;
        };

    // const time erase trait
        template<typename T, typename AllocT>
        class has_const_time_erase< BOOST_STD_EXTENSION_NAMESPACE::slist<T,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<has_const_time_erase<T>::value> type;
        };


    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_STD_LIST_TRAITS_HPP

/* slist_traits.hpp
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
*/