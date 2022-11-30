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
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
*/