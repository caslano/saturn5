/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_VALUE_OF_DATA_HPP
#define BOOST_FUSION_ITERATOR_VALUE_OF_DATA_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename>
        struct value_of_data_impl;

        template <>
        struct value_of_data_impl<iterator_facade_tag>
        {
            template <typename It>
            struct apply
              : It::template value_of_data<It>
            {};
        };
    }

    namespace result_of
    {
        template <typename It>
        struct value_of_data
          : extension::value_of_data_impl<typename traits::tag_of<It>::type>::
                template apply<It>
        {};
    }
}}

#endif

/* value_of_data.hpp
nQ0RNjdRD7O61E6cfZqI+BJNGsfBqF9gM5/P7E3a1meuno+r1/jM8snRPrOP1Ez4K4e/Kp/ZRfcJn9kddjXO1vlkaQ6dcddC71C5zWd2SdqL+A4iviO+8D1mP2nFXafQbmCCXy8tOEm+HwzrBk4bV1g6zgwz2lYyoti/4VEhXql3gQT9xPel46A3dNTxAukcskmRXV5295cRvb55Mv0rKPrQOXEJ/rHqLz4zZPU/PmbdYV+ldbQYRt84k+dumTE=
*/