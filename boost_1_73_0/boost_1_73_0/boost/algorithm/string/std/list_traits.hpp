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
x7uLOyEdFZbTkdUPkyyTbBsCm5FLZG45LrakVK5lygDYkH/ErjaCJx7zD0eWA1+6tvzIbDouoT58pjC9h6BxtNcVQp7nXmow0pcK9hjU2LiRhFit9gdnm9w3ebas+K9BhhJUu8refMOCICQosd5xiPFxfosgfptutSXVt7GnU71IoxWfeZtZUynVz6nPi0icyCmxdWbb/aNRAPxo1EgPkGwDwts8opNNIhH64AlQAEXY3gOSVl46qwPOt0lpWVyTdZeYDTnx5eEmqLK6AGfw2apGsicTgkeo2h3rteTpqUMzGKYjsZqJYMiKRPIClCWrnCDjVcxxTryKc12UWnGQBC9vdFpH+N3PK6AHtn22778+2hy9zmL+hK/mc7R88/m994eb4Ymngdc+CtjSmp2mDT0dkhVvT5BaZvCYeTI++TH+/gSofNEyswJBIp98yjbEnjT++x7kidAvG/qcviVT//59Jbl8pp20dByuRkk/36yEu0j8cHl28fmy1WEoyQpa8vb/4/Pq+eM+sAkvsHoQfzw5PRWDvwOrbOZQMO2nNSHXHhviwiDxw+TPP0xOxOAurdvLsEbpRSCwBXP0bjn4UBoWOQwgvqWdSLVay01lQv2W/DUTT3FMiiEZU7p9Ctt/4sqLHdoOCpzSZ1++
*/