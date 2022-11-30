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
        typedef std::allocator<char> allocator;
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
        typedef std::allocator<char> allocator;
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
        typedef std::allocator<char> allocator;
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
        typedef std::allocator<char> allocator;
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