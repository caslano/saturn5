/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_KEY_OF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
          : extension::struct_assoc_key<
                typename remove_const<typename It::seq_type>::type
              , It::index::value
            >
        {};
    };
}}}

#endif

/* key_of_impl.hpp
3rlH1rk9FTjtt799mfgvUIqbql/GHLHeX/S+9NVI5zhz50VEP8GMly4R9y6OquD1WaOQJF/o/vTMvdLeReZN01dpJ3YbRcVwsOBgzseP90VpP9TYjZzn1bsiwu/4yM+YPSijcEpY/Fbe7dhNEbMHSqyr5mGwf9aMsLpsuJhtQH6pIeYPlrL+1FTLYxPxc6uo+zzdrGROx05nM/vThDvV5+ccR8ZTUSlWw6gY08c/KHH5gU0v
*/