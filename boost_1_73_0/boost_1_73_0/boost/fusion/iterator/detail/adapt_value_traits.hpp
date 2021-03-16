/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADAPT_VALUE_TRAITS_05062005_0859)
#define FUSION_ADAPT_VALUE_TRAITS_05062005_0859

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct adapt_value_traits
    {
        template <typename Iterator>
        struct apply
        {
            typedef typename
                result_of::value_of<typename Iterator::first_type>::type
            type;
        };
    };
}}}

#endif



/* adapt_value_traits.hpp
8+Xac7bbaOZC0Uy+MvOz+vqiDLny6OZtMrJ8i9yuMUpFG2blkdmLpWbcId6KlYqmPJ6LZZT3uFx63NtG/YnU5xTlcaSrhef4IuahcUnSJY2tiU8k5EaUpoUKu6/BZqM4RT0xypLI+DdhbTK+hy/Te2GoeU5UQV7X/JJEf6Ojg9JJDnTUVy1+SmfLMI+dVmnh2Em2L6VS5bYdRCh9y1qolghVyrtfBT3fpn4skpDRb3ZW+Ch85S5PkmV5kpLcln8=
*/