/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_09172005_1120)
#define FUSION_EQUAL_TO_IMPL_09172005_1120

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<cons_iterator_tag>
        {
            template <typename I1, typename I2>
            struct apply
                : is_same<
                    typename I1::identity
                  , typename I2::identity
                >
            {
            };
        };
    }
}}

#endif


/* equal_to_impl.hpp
TTl1PjnNfqtmUhA5tMZIXShM5H5W2kD4dUclTmVFtlAAHdNc0gVECsjB1GROVaq6mwQivzXF4dRBwO/QPgN4jkO2ojDwLfQnMy9d6Ti6OywFGlZ6ajTL3/QUhC2k54fs/MCEEnfd4qyMdiWtWLqqGMvFrZrGUS6LOWBVUFEXVW3U3SBMgNMaPO1RG0RWdKftJIptHDQpnD6K90hsI1oxiYw35afGN2Y0urkn5emWm7Z6if/wBApKt+ao0IR+LR0=
*/