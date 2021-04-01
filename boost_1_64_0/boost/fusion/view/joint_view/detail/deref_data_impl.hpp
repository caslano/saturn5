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
yl0FMdNLKSPQB/l4TrOLFaMNtFNumTBzMV7ARQRHikeoS/xDpYlAEsPO5L+YPMJiD7wbwahatk5xPrwY2JY6JRl8Jh3vR8877PJsR43biQr+HOZVJDV18RADq3c7NLhubzqEBxFn2Q5HLjH2NPmVAtzEYF/z0jqv5l/zwssYuPFokbqbLrC4JJs/LgqTgR/PgfXz6R3FNZOe7ST/WYJ8/Pc56woAH7EVPsn9+jPV3TjVBawhbBFsOS6SoYsbe3gkHy+CgQxDeyF4wC3E6N0R9LPYccOmyFODssB8jI2Wm0jvwf7sGG4z7G4I9dt1+RlvX2yb9KkZ6d6i6AekuX1wuEya3oi5/5d/y+o0E1zjDuxUizjk5a9frq4MRzV+ETrFq9aenMLjhWNYTIPhywOFsPUTcNMMhNb8/XliC/YqxWwStlsgdYa11aX13ORQt6bYIf3ZcQyNKm8AmglPV1xQCvNw+7Ix+XJ7SRwVONsf1uHP1h77hEAvnpFNIyfirZFl4ftLFTJcr39cj/7yyu4FGiUU5wMY+HOtAirz2jMps2v0qs4BhSEpNfncGg==
*/