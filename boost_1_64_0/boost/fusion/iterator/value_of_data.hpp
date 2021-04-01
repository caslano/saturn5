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
VYnm/FVRQDRojj7OqLBt3ITamOhDUBt2s6U+FVltUN7I9q9ZhmjkiHObVW1Qyx+5g8lYB/gUnaL9Y9ZJQi9/kd64sjwlQfCdVnRpCCEJbAYf2OUpDGKLrbAUJnfiLAbQT1UaMCsxvirntRu6mQ1uCdXjgJuVig5IIjYzhNxOMLe9Pu0fMQhOviVsIk6ncemh64K5uBegnjEmPXbFwApdxmBpbFkXx+0dXWh3HFwFgAuEAIryVB+VmrrL8PPHLMzmXahsDCf00NxUwis/Os3wXgQ7OFuwafH6fs1Zj6M2NDfQUTTsQsL0bNbsOHkEPAqOLvM6LsC07S9lHhUoBUUqgWBBp0P7BaPsjEuERYzst7hr9LSAu6ZcLkxI0cBgSav3RkrUbvqmbY/mZVPt1EUBepW9WI5e4UvdXVVoiC8qTosWIyT/+NBTccgmzoJYjuiaGqXb+JC4IXVmovHjg2UjLKQeEpFBkLHum9MZ9FUPGnucbbuF26aIAoph+kNKEPCQqyI23AIHOC/3byCPoQHpNFAVwYfPbNUsndJcdZqs12gcowM8xbunNhAMNw==
*/