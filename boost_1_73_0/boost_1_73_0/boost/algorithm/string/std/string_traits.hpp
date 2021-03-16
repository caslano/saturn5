//  Boost string_algo library string_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_STRING_TRAITS_HPP
#define BOOST_STRING_STD_STRING_TRAITS_HPP

#include <boost/algorithm/string/yes_no_type.hpp>
#include <string>
#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {

//  std::basic_string<> traits  -----------------------------------------------//


    // native replace trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_native_replace< std::basic_string<T, TraitsT, AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true } ;
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )

        typedef mpl::bool_<has_native_replace<T>::value> type;
        };



    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_LIST_TRAITS_HPP

/* string_traits.hpp
f7NYzROON8ORjRxITdrdI20uf8KY9DHPrvRGmpoPHH9VD2t/P/79+V9V7uTx5zOf/zckV7vfBEu/8Z0n/xC/7W6/729eOj+/f9nvOz+GN3d+CoTmX4+34/Hq/LpkdN78+F/mvgQ+qur6/04IIQaEJOyIEDEqi0A2IiiVrDCByWIybBKdLBPCSJYhM2FxnQiIOOJS9x0VK261Lq1ba1HcaxVr1Vpba611+WnVWref2vI/59zl3fvem0lo7ef3Hw0=
*/