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