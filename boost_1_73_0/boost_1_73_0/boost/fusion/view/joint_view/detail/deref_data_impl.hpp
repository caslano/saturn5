/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<joint_view_iterator_tag>
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
SEKPLAKrRrBljcy8sT3Bd2AIFM4Xl44dTGsxNYDKHW97Pgksx0FY0M+2Aka2RQacPTVsRuZAsR3iW+C5AaK6nnqzREPgI0KZLHwXEAEfoNHYAzbXyMIdWz5tTEcuUHCeUgZrRRPTOyaeC8SQp60B6QyekkszsIMa+dQZfuhdDMmnVr/f6g4/k94JaXU/I7CPne4xiN4GZD6xbua+FQByn9izuWNbY45zfa/tjY1tZrRd75pisWaWC5Tv8dE1quTCtW/IV+AjaANpYOHYv77x6/g/aaAE/Z0GmYRzQl41muSfMODmW9Lc3dttkrnvXWGPZgpMsywYsJo3JAKzmwKzmwFDXw32T0vNSw4muJ05tvsXFjlLDYnUD+l7c2dnB3u/qpLj3oAE4a1j4fedRr35tg6UNxrQ5fyMvDvu9A8FfmD632x35CzGFnmKJmMEVriYb02fYsUEVG9Cji76p8ZxZ9D6/bRtnAzPpS7vsAsztemhDApKxmZoIpy4EFXVdidestQB0wqTRaC0oedNJqliYEKmADuDwwAuJavoWCbuzAxHU0XNzJp5/m2yYrZwQtueYOH2JnU1jhmEJGpAXRl3WpfWHjJP6mzNxtbl4opyDrqbjgOOh1wuJhMwH+r3yLXtOOAo3NAE5+i5AN+G
*/