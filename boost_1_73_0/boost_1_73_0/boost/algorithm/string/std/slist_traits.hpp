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
N7Jaf9Hw2sY8FbJlfWS9Qy/R4JA4YVKXL9VcaxiBHYF2hNnh0+mofIuYcZgiUV4+TDUhIkfle0Q6aJl0GCVpqg3nId8DtvcBUvFqPxN/C31LDG75h7j7+ECYNffDf0VtVYSdvlOLwdxRucV0d5Wg2eU5Ns6J4iS3eiYWProFDMGx5WDrXGlnU9+FJ5amBRycAnSh6/5penJ68uNk64ocDesGxVuPkXZW95t+QkLebSxVjBGPL4d26JnAIoRJ1wpVVax4BGQwf7z48vnzPz+GKr9q68Vf9jh8OehxzCwnuYGwXJFUTnNu+dLlvJQ+x5wfN74+m0BS7ra62mx7qR7j/ZoFa8WXV103wmawrM1R3Q1lsGhuQ3Wj4gtSF8gNirJaTWD69GCMmjpDHF7wuJnyXGNdtV4Ph42+Ayrw5gca9s77pMl6sJdFgQmLaaTQTr50k3FTEUeE1Nx84CIpxCCKznNdZWtQAAo41xuAIlz5OY2YmGbiSn7l33eKmgvDucbua75lKrS/n6qNXS4AWVpVm+U3JHLaYFYOe/BzJvjSTu3/C9Dl4wtZHJL6ZxR1fxZ0gni3vzqIW2AElmQyzNvsdvhbovtvAViI4yhq17PvvmsyhOtl4rjRkZlIcuuJNptpptNpxhpjfhTjWMzn
*/