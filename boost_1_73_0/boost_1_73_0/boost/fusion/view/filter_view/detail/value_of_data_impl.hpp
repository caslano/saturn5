/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
U5MfOmJKBlzE99M5ErHANolpTe3rb6HMwEiy48dcKur99Pw95RKheZ8uAF+CpENC0FdyKoWo3DHFWk/yQaQ6UiovsTode82ANV7Eqk7KL0e1Sue0bjK36Q3EVIQxhZlF0o0+PbZ7Q39U8YEyTbMn1Q8vrPU5wVExZjP8L3pacIk44Q3h7fpx1mJq0rUHJRoiWMJOgcCRGY0YtjAyZs1ltyHjUtbARLmni6EOeo52Aq5PBoqgoV9jtSMeFy+O256vbayQt5x/40znxyfPX9mDGJWFqUrVJRSrn1Cp+j7vJw6F/E94uYA/AKF7ZD54n4DLaQzFp9BHBbfnktF5eXqzuCzgkJ1eXpFezbFeJlokt77ASmEbIjNFWQEMbkSfY3Pr8IEXLw5BER06NvSVaZkJAGywQmGWhoLCcPmrdDud0c++JintuJTwlaQ9QCdXIGhPq6vJOGtpO8A31+dVCypMF9HbeJsgovQ9x8iNlhOJfzBlbRtXrMlylxxbuvtMijxaP9bxrBvpHY2qV6N8Jgv/xJtbLtOVgVyqlVpucdMnLFOMKRl/Droz54FuJ4shGT/aRuggaLqfudqx7sbH9ZxlDwKmRmJyMaZ3FB53rY39J+toJFb1tWo/yI3k45glQulVmD8ChvbAlWPis5sp
*/