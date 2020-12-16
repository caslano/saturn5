//  Boost string_algo library sequence_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_SEQUENCE_TRAITS_HPP
#define BOOST_STRING_SEQUENCE_TRAITS_HPP

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/algorithm/string/yes_no_type.hpp>

/*! \file
    Traits defined in this header are used by various algorithms to achieve
    better performance for specific containers.
    Traits provide fail-safe defaults. If a container supports some of these
    features, it is possible to specialize the specific trait for this container.
    For lacking compilers, it is possible of define an override for a specific tester
    function.

    Due to a language restriction, it is not currently possible to define specializations for
    stl containers without including the corresponding header. To decrease the overhead
    needed by this inclusion, user can selectively include a specialization
    header for a specific container. They are located in boost/algorithm/string/stl
    directory. Alternatively she can include boost/algorithm/string/std_collection_traits.hpp
    header which contains specializations for all stl containers.
*/

namespace boost {
    namespace algorithm {

//  sequence traits  -----------------------------------------------//


        //! Native replace trait
        /*!
            This trait specifies that the sequence has \c std::string like replace method
        */
        template< typename T >
        class has_native_replace
        {

        public:
#    if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = false };
#    else
            BOOST_STATIC_CONSTANT(bool, value=false);
#    endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )


            typedef mpl::bool_<has_native_replace<T>::value> type;
        };


        //! Stable iterators trait
        /*!
            This trait specifies that the sequence has stable iterators. It means
            that operations like insert/erase/replace do not invalidate iterators.
        */
        template< typename T >
        class has_stable_iterators
        {
        public:
#    if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = false };
#    else
            BOOST_STATIC_CONSTANT(bool, value=false);
#    endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )

            typedef mpl::bool_<has_stable_iterators<T>::value> type;
        };


        //! Const time insert trait
        /*!
            This trait specifies that the sequence's insert method has
            constant time complexity.
        */
        template< typename T >
        class has_const_time_insert
        {
        public:
#    if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = false };
#    else
            BOOST_STATIC_CONSTANT(bool, value=false);
#    endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )

            typedef mpl::bool_<has_const_time_insert<T>::value> type;
        };


        //! Const time erase trait
        /*!
            This trait specifies that the sequence's erase method has
            constant time complexity.
        */
        template< typename T >
        class has_const_time_erase
        {
        public:
#    if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = false };
#    else
            BOOST_STATIC_CONSTANT(bool, value=false);
#    endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )

            typedef mpl::bool_<has_const_time_erase<T>::value> type;
        };

    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_SEQUENCE_TRAITS_HPP

/* sequence_traits.hpp
Ta3/f2jNBB6TLCpzrDMK6YlmSMya1dwMvwTU/HkDv0+RTPq3TMP3581/JX3zt2gvjnPEx4izH/5pYv8XNkVHl9tuaKET8KKqDN449dnOekuIXH4mCnueVJD2EgJp4/C5vGsuFJPFLWN5olADFIBS95hl2wLu45ej+0x3wUhSeMsRuUAIxGR5xryUDR4qyfoTC5DhoUkZwmNny+G52DjO2SYK7wdGt/ndeeJ+8js8Nb8tbyTlNxqRwkPHZ4PLsQWH7u1KFH7/ZEqoyhXNCCG89QgkyJD5Lor+7Bs0kTmZYlT1SRReOrAgTSEM5gs3aNImnR1BgUThICBgOlO4Z3SWTOvmD+Zj+8BIFCYUcL0CnmklcaY5HAhqG9Kt3A6kjo1FX4Y6Rg12QJ3vK/ip8X+zrR+0nLatm/0vLQwPD3W57KrFXDZroFW1W7OSqnawVO2Fy6lqV2apqk0/ya7agVa9DDRPBNLnaxHJ93XZ69mjKJPzhDK6q7oc13viryqAq45HgfGPG0qMX4dLQl3edaHYqVuL6ET2JhxwBteTg90lxm5f7KeOROEYsI3RjpKMBdomoAEBYO8yn9GaKDzdgp4B6BtJ0EThURaoL0BrUkCaArlvJt+6WOSa357gnzugoc8F3LBTX63By3AgvLEdVm5zlkkl2egz6pECLnLiXbUgPi1R+OIJBWlD6t1h8fVQBSPzwgQJusEhpIsneB//95/X8qkcsipOFI5D9oHxTeR8KhA7B5nVXN0jMNcmIbyh3fSYXHWUGNKxI2OnJ5bFOFlatBevskixB3fIgNu3G5Ouqny6u6kXZn2J3rlpmP7RnYh/AHmD++IcCBWYnM8Nzqr0DMXHjVOzMW1LVA8+rKrdaHLP39YXSVQWgzBHcMiCqb0rjAV8R+xS84GX2hIImvIDnEv4CYa8x5G6UbtvGu757X0D4ep0rAlQ/NM6438X8ekrVvio7kqjkL52yLeRFoXkIaQV64V99cF9g27/elafKlwB7+tmA08iwUUGuMgAF8V+6LFW+/4z1otx/8Pciehd5invWwPAN86wB4BRgHi3QOESXbWlDBIJatDfUTu9z3SxTehyivzon9rk1khl6Geu5pP0vJYje7xJNMredFrVwfhxCji+EZNp4pZ3ebhwR+aoe0thxmKRWAwRQHaue/E9n2cFA5ZCMqYVw1gy21d6bOVR4d34dPG9YW7faupKGyDBLfvAq2lOInlGxpD17tBu2CH4MrUKYwmf+koUVgI3QP1uRjFW51YylJbocNlk7ZK2hPYR4r5Utn72upkvzKekGMFsnEvtzlQhtlCL/BOFk5BcyJBaodODt6IKRXbfv41lN9X1pV+j8Eb7YkVRmnjku1YTnzU4pYm5DaBU06XHOxKFl9Oo2IFTlUnV7IoNc7Q0ikHjjUNyyQzIhSSd9vFn0frKe/Qd0n7SXjc6GIHWxR5yUm3n0/j+MtUjX3CpG9v1Idu5So29unvkHr1sO5wgXs+WILQVPDozEJuwfO7z/54oPJYHkBkubfXsHTMXwGC+jm4cLdwJ5sH9d9I2A14kajhHZC6UhAyhFhMOWpTzrzZqk9smbatqG15Y+Uqbx1s92FHZUwRUDxZQN56eVtVGEmq/85UiPqSk7mkJGB/K7HjWJhljbxibhm1HcooT5xNhYSFJpMemdmBc63DPGUHbpnr78OLkpf4mvKXHN3jkDRvFiuQtw9oSMCITUHnLYmg1qiyyLI0TDvhiM1zBeJuGrUg7V8cG1evuOYfi73wn/hvuoF1mTfRGOcgb5SBvlIPuXZbTGL24nb4zIYQJrZE+KKtguN6FL29jtAJcUQEHihvJJwdjY6+Uf3sE2dbQ9rc=
*/