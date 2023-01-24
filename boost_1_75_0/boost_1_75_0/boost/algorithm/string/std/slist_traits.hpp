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
afA89kzhb+UI+Ro39ZYENLg83Oux0vYvMPgV3QvBud/uy+ASOOD3qxGyy8ePvDFx8Y7Zd4Nn26pGVm/r4mose3ATgX3GQBubHe/Lp39rnZ4p5gmgHJIMN0Hqq0fBM8oROSOr/P6zLXS333TlL3FVIk7GMBFfsbwvK8M5pNmJg2ebKS9MmPNLui2OIXHWAPjvyzgOqx1QTYrEl7HluC++uIuNfCNJcBMlVFba8Qr423FrG79mZNV1QHv2sVzNsodaVjfekTsUKRHwdsEhG4BMh96g1uaeomHw7fbr4D53wsowqS3Xnrd7JPq/tmP05fDIzIAa8rIE++dWDvGbrLbdsz7zuQVjnqtRQuEglguBuUoAluKh80cFFCz5ItFjvjuyD/km6lahHsyl2sVQk21klzJesRW5AajyU4Ja5ha6xbcrk6Ibw9egqqm5Iz11AZcJkGdJZj/UN1/4UhTpyPHdzSrdHMzt6rour+iL3I6qn+374hWVYP4j1LCSy4+hct4E4f0sAeAjhsalTadlKMXRLFuNj6/a67uViuqt+QhQSyk8bkDvU/YzKLq13U7M7LR231rBLOZ4JtDch0t8f34Inqb5afPrNMrKZUzfjVjW6rkCqssoZ7WpypdD3/jV1rAMtF+qvoJayWjsqHKudyopbd/bTMbrH/56tG5vuLbRU54bv2ujBYZwKD8jfM4sScOWXdICtebHvlbmsn0v
*/