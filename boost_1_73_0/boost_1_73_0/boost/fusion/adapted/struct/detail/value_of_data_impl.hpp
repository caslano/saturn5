/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_DATA_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<struct_iterator_tag>
      : value_of_impl<struct_iterator_tag>
    {};
}}}

#endif

/* value_of_data_impl.hpp
jYwR1rPrFVimK9DH/oE/lsCTK+JTmXCYEct/4GrGRFMEqxnIn27yw85UKamty3Mt1Imfv/YEWWrbG2QN6aMgS20fE8WL7Qsyf3wWZGP550GW2j4NstEc+Ykm/09E9wdZigN+usnj/HOFv87NtlIYYzMFaxVsoWDXCOYKtlawewXbLNizgh0UDA6nGct3LFYk2CjBThWM93ZZDrtKwViUPiplGwqr8L3pHNY2/zDjUCpu/Pc3x6NFyzzF8AxoUag=
*/