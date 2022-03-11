// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/manage_additional_parameters.hpp
/// \brief Utility class to extract the additional parameters from the template parameters.

#ifndef BOOST_BIMAP_DETAIL_MANAGE_ADDITIONAL_PARAMETERS_HPP
#define BOOST_BIMAP_DETAIL_MANAGE_ADDITIONAL_PARAMETERS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <memory>

// Boost.MPL
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/bimap/detail/is_set_type_of.hpp>

namespace boost {
namespace bimaps {

template< class Type >
struct with_info
{
    typedef Type value_type;
};

namespace detail {

/// \brief Metafunction to check if a given type is a data_hook specification.

template< class Type >
struct is_with_info : ::boost::mpl::false_ {};

template< class ValueType >
struct is_with_info< with_info<ValueType> > : ::boost::mpl::true_ {};

/** \struct boost::bimaps::detail::manage_additional_parameters
\brief Utility class to extract the additional parameters from the template parameters.

\code
template< class AP1, class AP2, class AP3 >
struct manage_additional_parameters
{
    struct parameters
    {
        typedef -unspecified- set_type_of_relation;
        typedef -unspecified- data_hook;
        typedef -unspecified- allocator;
    };

    typedef parameters type;
};
\endcode

See also bimap, bimap_core.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class AP1, class AP2, class AP3 >
struct manage_additional_parameters
{
    // (1) manage_additional_parameters<
    //         not_specified,not_specified,not_specified>
    //
    //     set_type_of_relation: based on the left key type
    //     info_hook:            no additional info
    //     allocator:            default allocator

    struct case_NNN
    {
        typedef left_based set_type_of_relation;
        typedef std::allocator<void> allocator;
        typedef ::boost::mpl::na additional_info;
    };

    // (2) manage_additional_parameters<Allocator,not_specified,not_specified>
    //
    //     set_type_of_relation: based on the left key type
    //     info_hook:            no additional info
    //     allocator:            Allocator

    struct case_ANN
    {
        typedef left_based set_type_of_relation;
        typedef AP1 allocator;
        typedef ::boost::mpl::na additional_info;
    };

    // (3) manage_additional_parameters<
    //         SetOfRelationType,not_specified,not_specified>
    //
    //     set_type_of_relation: SetTypeOfRelation
    //     info_hook:            no additional info
    //     allocator:            default allocator

    struct case_SNN
    {
        typedef AP1 set_type_of_relation;
        typedef std::allocator<void> allocator;
        typedef ::boost::mpl::na additional_info;
    };

    // (4) manage_additional_parameters<
    //          SetTypeOfRelation,Allocator,not_specified>
    //
    //     set_type_of_relation: SetTypeOfRelation
    //     info_hook:            no additional info
    //     allocator:            Allocator

    struct case_SAN
    {
        typedef AP1 set_type_of_relation;
        typedef AP2 allocator;
        typedef ::boost::mpl::na additional_info;
    };

    // (5) manage_additional_parameters<InfoToHook,not_specified,not_specified>
    //
    //     set_type_of_relation: based on the left key type
    //     info_hook:            InfoToHook
    //     allocator:            default allocator

    struct case_HNN
    {
        typedef left_based set_type_of_relation;
        typedef std::allocator<void> allocator;
        typedef BOOST_DEDUCED_TYPENAME AP1::value_type additional_info;
    };

    // (6) manage_additional_parameters<
    //         SetTypeOfRelation,InfoToHook,not_specified>
    //
    //     set_type_of_relation: SetTypeOfRelation
    //     info_hook:            InfoToHook
    //     allocator:            default allocator

    struct case_SHN
    {
        typedef AP1 set_type_of_relation;
        typedef std::allocator<void> allocator;
        typedef BOOST_DEDUCED_TYPENAME AP2::value_type additional_info;
    };

    // (7) manage_additional_parameters<
    //         DataToHook,Allocator,not_specified>
    //
    //     set_type_of_relation: SetTypeOfRelation
    //     info_hook:            InfoToHook
    //     allocator:            default allocator

    struct case_HAN
    {
        typedef left_based set_type_of_relation;
        typedef AP2 allocator;
        typedef BOOST_DEDUCED_TYPENAME AP1::value_type additional_info;
    };

    // (8) manage_additional_parameters<
    //         SetTypeOfRelation,DataToHook,Allocator>
    //
    //     set_type_of_relation: SetTypeOfRelation
    //     info_hook:            InfoToHook
    //     allocator:            Allocator

    struct case_SHA
    {
        typedef AP1 set_type_of_relation;
        typedef AP2 allocator;
        typedef BOOST_DEDUCED_TYPENAME AP2::value_type additional_info;
    };

    // Some annidated mpl::if_ and we are done!

    typedef BOOST_DEDUCED_TYPENAME mpl::if_
    <
        ::boost::mpl::is_na<AP1>,
        case_NNN, // (1)
        BOOST_DEDUCED_TYPENAME mpl::if_
        <
            ::boost::mpl::is_na<AP2>,
            BOOST_DEDUCED_TYPENAME mpl::if_
            <
                is_set_type_of_relation<AP1>,
                case_SNN, // (3)
                BOOST_DEDUCED_TYPENAME mpl::if_
                <
                    is_with_info<AP1>,
                    case_HNN, // (5)
                    case_ANN  // (2)

                >::type

            >::type,
            BOOST_DEDUCED_TYPENAME mpl::if_
            <
                ::boost::mpl::is_na<AP3>,
                BOOST_DEDUCED_TYPENAME mpl::if_
                <
                    is_with_info<AP1>,
                    case_HAN, // (7)
                    BOOST_DEDUCED_TYPENAME mpl::if_
                    <
                        is_with_info<AP2>,
                        case_SHN, // (6)
                        case_SAN  // (4)

                    >::type

                >::type,

                case_SHA // (8)

            >::type

        >::type

    >::type type;

};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace detail
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_DETAIL_MANAGE_ADDITIONAL_PARAMETERS_HPP


/* manage_additional_parameters.hpp
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
*/