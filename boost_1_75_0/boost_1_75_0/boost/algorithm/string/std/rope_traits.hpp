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
+MuZq1FlEIam4hfK5i9fzo0wY+Bq5YfnOzdSgaEy/f12NmNVx/3yIMrkFUZmGE5o/De+ixWuAt6bqOu0UA/Qg61FIY5teqWsej2eInbwF7z00Qp+j9GtEwrIjNZvu4b2Zww6UD7U4635b+vI1791qG7q8G6yrb67PjNfIZrHGBjq+whaePVypIP8ZTkBn+reCMVaiEekxC/gLVIQrEhp4VMvh8G9ccS4yIjC/i/H7Xx8WKHPFqI7G4ra8E7RH0xp5zCRSu6Kl5hOvUeSbD6wsChYPRNL+4qBje2NYWUydIIHe5Ed2v1WpqPZCEV9nQwmk7OCw/EWF+HPsY88Ka1f2fNZQdtq0WQvWckqAPmvR1MLE/816p8uikF0sMmUF39zkehc/sdlWQVEFW5RWEBKrqR0SUu3NCPdJd3d3R2C0t2N0t2KdHdL59AwpMMQA8wMl1sv9+2cddb+1t77/A+/6D0VscUP3fEjpFOkT3jyHeOxb9xqIuvMdZ/PsB8NI8aKtqZ31Qu/XFaHkG7WH8Q6TWNv9bIy3lIosPaJZDzy+6oXIIlPlzM+BxWigooVZoYptgcNowpCZ6zA9XG80+1j+P27OZu3riOY8TX+K8P63i/PjCbEthfDgugl9MSkfsb53gT7Lhw8SFcdgiUUDaGAHVrIe9kujhn1Yb4XX/nu7ZV8vEieO4JEbs/vxZ0xJWNDb4IOTBiMWh4etezA
*/