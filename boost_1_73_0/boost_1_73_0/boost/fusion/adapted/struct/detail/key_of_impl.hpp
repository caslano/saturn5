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
P8K1znasqpT0iVVHmyudqJHz6fwCknby1AitJH/XbQdWnLK9p8jYbHj101QD9ibUE4jXnOrgNUUL2OC5HNoFfQx96m6DfRJiLfnzEGvJB0KsHX8Z4jnjqxCvDnwd4k0Lfw9xQLpvQhz69GCIQ+8Qo+u+6IRZNssKc6iUXKJYPMojihYJEV2B4kSvJkpMqCMYZIdZFgubOWa09NnRuu9cINhMwRYKtliwGwS7SbC7BLtHsD7BnhHsz4LtEQwfbjA=
*/