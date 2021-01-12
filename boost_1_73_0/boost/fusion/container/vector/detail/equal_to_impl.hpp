/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_05052005_1215)
#define FUSION_EQUAL_TO_IMPL_05052005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<vector_iterator_tag>
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
VLZK2HaoPhKXabXGf6O4uT82/tYws64tYR4YENGbUuqDPyCoOeH2/JsZ7hQexRn2LJahcyPrte8RZsu5ebOP+TN5fmfZu9WEp8TsITDl502xd6L5vlVrTbtNhCMg3x57gYBkcISkYVJTDtG3cky6yTenrkDJ+r66C4Vwg7ukhBVzww29b5y1NWvMIcwb6j5BwmHW7jNa+OTembSKF3+7qb/0qyRd4hOS4lekhIsJVHq11GlC
*/