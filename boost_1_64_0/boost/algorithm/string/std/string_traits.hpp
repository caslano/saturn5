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
aQ5Cxfg642j/6XFmR9oKIscO666JzX2xuFBvjhCiYyWVOaabhHhAoM28yPf+IjgEDwozLJ6HZGk/7WSo+rBLa1sgKzd92PoiIumDisNppo/jHuY+5UahBrO4H9dG4GEtyHT2YtZx1nlEkujCs+INLfOgx7WwsygSxJ3lydRLAlB6GfRBMNMZZkF8Br9MdjHdcy+Wsb1Gv9nKkBPhufw/rM4lnL2pL5XE6qeda/9ZbHQqsqqPNaR4/XopIPa4F4u2DiAaj266DFDunC3IzkkGL+Zlodvs5gBbQfI0wKouYPKAanFfzZs0gVZoOcIXBC0a0m4O9xOUPe2a5W5/EWHp6E61Tq3cXmya7ulRq8tvfIXspNHhPzKCICF4pqsBefw09fvKNXTxmmZrITcKBa5y92cgdpTvniUekOcNPo2uGsWlK5V3QtkNWka7fmp8Z4LSW2lY6P4eL/Hpe/FZRQoE8tprAX1R53vjdVDsB1u1vlWWWvqlm+hwA3hnhZY1NY9IKZDCDEYtvr2mgNE0gVnX8IsKvTeIgxYoLC01BU+jawk8fcrSh3RLxtvsng==
*/