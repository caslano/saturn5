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
Fvk92ZWvv9PYdwQ2BDrG9o9uv/uQ8dMYuC7Q1sl1+y73cWwyiew7y8Gl0fjfL3vA+fFtQfuk+L5T48Hdxv+DgY2B0B7ERZL2yda4XmLCn0ibSLHG/qp54XwtII4Jps9Mkz3gHDRhznH3DDj2ngGNFfeb524LXB7oZftTXxfZW3Cv8fdl8p9J/JH4SID73bTWPO87yGTMUX8fybfOlzb9d3fq5C+Zof77s9i/x9874LNwPwy6vQwPqk+HGNOvw+b79my9h7Hj+3dvs/pgyS9OOwbyi/8tOcWjJY94tOQOT7oyeP/evbf+YvSD7zx5x5xRP/j+T6573k/e8cMvdyg5B37/ReRQymPkHM6QXMenJYdypi0fpnDdFc6WB+klOYfeMEvyHV1kl74n/dYgfQpv63vqK/m2fnCQ5EKGwAHw45L7OBMOhDPhIFgsOZFaOBg2yJ/Sq+9vpddPHk7pzVV6setsWX2j6ju7HNPDyK9xSZ6jJ9wIT5O+sclwl+SHnoFzpdepSnqd6mEjXCH5uXVwC7xNcpqb4b2wCd4HvyY5lSckp/Ky9Cn9Bj4I90seq5POBh4FH4dj4TfgePgkvBQ+Aq+AO+Ey+DTcAHfBW+Ezyrf7jQNHe7SP5ySH9zw8A37flj9U/eZ5lPcrKu9XYY7kqHrAn1jhCxS+g0f4F9UufwhT4W7YHr6k8IXhcVRjcLnG4zHQkTxf0D4angzPgUPhZ+Ap8Dw4Co6D+HXP/j5f9XoBnCE9caVwEiyHF8OF8BK4BE6Fy+BMuAp+Fm6BRfArcDb8KiyFO+Ec+AqsUH1+Dv4JVsJgZubDzrAW9oSLYB+4GA6HS+B0eAWcA6+D18FVcC1crXq+Hm6Ca+AWuBY+AG+EL8Cr4EvwGvgqvBYuTwnJI52xrHl5pNbo5kogd4S8UctljWz9XbEyRavgNozkiLxliDzkhzzlhob6ygpJD5iXbBBurjxQQlkgyQHZ8j/xusPqMBF5n+ZlfSTnIxmfGLmew5Tp8ZLhWeevhyxWTseV0Zkp2Zx1mCm0rWrMOswOzCuYA5iMa5HHwZxxbVK+Jnklr+SVvJJX8kpeySt5Hf3r2Kz/l845Guv/wXX+cmudP1O6vd4L6g6Br8HngnP068PrlRPGfKZo2qiiU4db64FVi+oic9DyO8HYL8F+u7E/EMjGf74j/6gwsM4TUZgCd81unbF/I9CBMKnmPJ3puI02axT3GLf7AlrPUdjFWt9Bu8kGs+aNPfy86eZphDdrHo3G/3YTflJUeOxW+GB6O2VpvbOoqqLUWutbZsLcY639KB6t0eQF8OumfdE8cw6E5ttvCD0/shYUE3YQ9yJlRViVlbseFON/qJ61J9usHZFM7Jp732j8PRQIhy2ICTtSYY2aBsLyKFcfzO+Mv1GByJx9hbsGMPALQbeX3DWAQ8Y+OdwmuEppXU7oGTByf3ZdjVUWo0y4p4y/Avm75QSTFhYpIjopnjdpKQ54yQbMD+j5zKhkG3c9X+UW1hWQZfx8ysTxYjdXL4W7Vhdej+2cxfvLOzEP05+/T5SpDNrF9OyQLqucrNCc/bOO53UOzryLp2c1mrXTgFmbJa1Ra7NYtDbLe6G12Xbae8o9vSvSUcd92hT3p5uw3eQPO75MWNP2aLfcc9ut8TvIDUub0nOGuuHVzuR3JPdpT9ynPYXvuWvIlK3uFbj3qFdrfYLy5V6wfHWuj9a47tAaV3DLTlc4CH6fBOzeEF5rC/V9FQvmVKHVcXZVaegszqXmPazmwZH1nXdNmONS7kIrqfoexdNPfgLOi7di5+1EQ4QdD4lV3+OG6eOuh/3F2DNTDgbaePYB2dJj8ifjr0PKEGeP+iLFRYs=
*/