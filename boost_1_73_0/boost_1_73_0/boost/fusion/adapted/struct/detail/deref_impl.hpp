/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
        {
           typedef typename
               access::struct_member<
                   typename remove_const<typename It::seq_type>::type
                 , It::index::value
               >::template apply<typename It::seq_type>
           impl;

           typedef typename impl::type type;

           BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
           static type
           call(It const& it)
           {
               return impl::call(*it.seq);
           }
        };
    };
}}}

#endif

/* deref_impl.hpp
yVLolrCTti5qamYV89O6/jjmSBorvDEMdpAK5JAGD3uqoyCPpWQxLBwMN7IWbynfSPlsVU2/i+m3jH62x989/rtIGdaO+mldht30MU9JvC84Ejdeb7CtIdZMt4fYUL4jxBrom0Srib4V4ujVL4ZYE30pxGG2cHyeOQ6DHMlJXVca/CqDY4PTK0R/afA7DH4f0deI4hl2EYUBlFq96zVTbpcphx4wTXrANM3ZDYI1C7ZYsE7B7hRsrWBQlhjLdSw=
*/