/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<po_array_iterator_tag>
    {
        template <typename It>
        struct apply
          : remove_extent<typename It::seq_type>
        {};
    };
}}}

#endif

/* value_of_impl.hpp
rgsAADIACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1RJTUVPVVRfTVMuM1VUBQABtkgkYK1WYW/bNhD9rl9x8L44hSKn7YCua1dMddxUq2MbltMugAGBlqiIKyV6ImXHW/ff90jJjpO2aD9UQSyL4t29e/fu6GDZo0c/7PIC646+eSXuP8GF+95oVqu/eGq+bJAkn6j9g+ES9+8INaA7q0/JCX2X1SfqO6uki/XSfk+S7wi3tCDtx8AaLxP7FSutZWc/VOtdLW4KQ/3hCT1+/vwXOqUnZ0/OfDpnleCSYsOrFa9vfHqZuZXfC3Z7G2j+yiduiMngnsNFITRplZstqznhuxQprzTPiGnKuE5rscKDqMgUnHIhOQ2ns+tocuHTthBp0fnZqYZ0oRqZUcE2nGqecrFp3axZbUjl8AD/mdAGPhsjVBUgPCfD61J3biwIJrUitmFCshXCMUOFMWv962CQNrVEJoNMpXqQ7qkIClM+yOoaaEq2I7U2ZBQ1mvtk9/tUqkzk9g6KsLhuVlLowr+DhYBVNlA1aS5l5w6mgus2BU5xx5Zvd9Ia6IWxN60qbaNtC1Xe2whaO0d5U1cIB1qwL1Mg3qemynjt9jsi9lE6lh3l3yjZHfaMVAVU
*/