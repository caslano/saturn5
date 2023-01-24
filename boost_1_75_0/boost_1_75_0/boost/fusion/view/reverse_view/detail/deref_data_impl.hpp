/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<reverse_view_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::deref_data<typename It::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref_data(it.first);
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
kuPh/ZqRMb/I2uLHTxku6+JjO6QidoZWFuTPpO7xtg3X2d2dRVHbB9Tff6ZgEy65Q+fG4wjLYRCWryzTu42VSPmI3q1h//ixrErRgMWwbfpQeyYr8NNRBzdt6ImymdlLNdeWxhOcZ11GvVJyp85xsuhlj7opGXf95vmvg+bOBHchNg49iIzafkNujlMJPycpkv99ngdYWOUmfHmCV3pluaQEOd1BwEVdhpdclEorAiGCRVVbHYFn6+3aXRW4ycQ9qoPojQ1ZEj7jxayueYozOrzCHNa3TRuv1/1lz/fI0Ce+U041e4udrU9KbtvLaE3ANjjQo5a8DpXGBqnV306YU5KU7R4q27EVVa350zhLq0wZoXm9y538n35BTPKzdM+MF50FKefdwyHgOq3jmceHdr0vkjQ/kME8+cs5W18JCfyQlUMt3zE4/8AXs8PsUgfRQ6tVegiu5b2kSjxFtd/97tU2w2bzlzIfpb3jbi4yfN+Qt3EPLp1RvDEeDUwZSOn7i8fEbRL7ujsBtNDp70lvipI6E5bzBdctQE55RkYg4sBp/Z0HBx8cCFhL5nl7RCU+8Ezo0ezRaugLTHw2UOIpuwl1E2hqibZFKSq8CpzoV9ndKndILrbGoDnF/OAznXeJ5LzQ3UsQ5+Y9BbeGNXbRLP0LaXfRfUnQzHzvmFqJ2/xd1T4/vvdrW6rI0EokdA5kT8QZXnPGKDWBr0Md
*/