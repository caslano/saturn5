//  Boost string_algo library list_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_LIST_TRAITS_HPP
#define BOOST_STRING_STD_LIST_TRAITS_HPP

#include <boost/algorithm/string/yes_no_type.hpp>
#include <list>
#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {

//  std::list<> traits  -----------------------------------------------//


        // stable iterators trait
        template<typename T, typename AllocT>
        class has_stable_iterators< ::std::list<T,AllocT> >
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
        class has_const_time_insert< ::std::list<T,AllocT> >
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
        class has_const_time_erase< ::std::list<T,AllocT> >
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

/* list_traits.hpp
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
*/