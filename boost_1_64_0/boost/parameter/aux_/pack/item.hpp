// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_ITEM_HPP
#define BOOST_PARAMETER_AUX_PACK_ITEM_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A parameter spec item typelist.
    template <
        typename Spec
      , typename Arg
      , typename Tail = ::boost::parameter::void_
    >
    struct item
    {
        typedef Spec spec;
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
        typedef ::boost::is_const<
            typename ::boost::remove_reference<Arg>::type
        > is_arg_const;
#endif
        typedef Arg arg;
        typedef Tail tail;
    };

    template <typename Spec, typename Arg, typename Tail>
    struct make_item
    {
        typedef boost::parameter::aux
        ::item<Spec,Arg,typename Tail::type> type;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* item.hpp
pB6ZjTQgRzBfCc9GN4NKPQJORfp0sngZ91chq5F+mH2aFMkZxX6AmycJt+16gxEvmMSslPmB3xlz5o4d4RGzGG02ZoxptvtDbTbKNNtpmWWbZpsss5Gm2VcsM+3HYsss0zR7/wPTbLR272XLTLv3kGWm3bvdMssyza6wzLQfy7TZqDNNs7Mts7Gm2VjLTKfBUye0mfb3PG2WPdo0O8sy02mVbpnpeJx8X5vp8B3QZiN1WG62zMbouFlm2t+llpn2d7plptN0mGWmw9LJMtNx+9txbabT9G3LTIf5RW02Qqdpb8tMu7frPdMsS8ft25aZjtvXLTMdt980azPt3pOWmQ7fg5aZCl8HzG7RZmeq6/X6emyr3k2TlJn07Zgl6Pf7Gm2m7UobZz8L399NFsp5Le6gbu/hkAnrGWmV871ftU/UXHTk3HlzL5dPMOOrdBfasBGI61ghbrs837iPE6Ib6bu/oRvZu78foK/Cal3fYVxLnq37JDQfl2HmzMc5mNnzMUtfj1XXZ+jrMeq6rb4era4/+Juuv+r6NX2drcerCB15p9K5VeMU5lyzw+mByPdvQ7oJN6FbeCoojyVr3fM2EU7/1DCriJrMv2s4ldV8Lj78d8P8Vh9jOL4cXzTnSPa35mV+Ztz7BesovPo9+Yjyd6knN9y8tVPu5eMSeb4sUff7tBlLCZnGzLmTMMtb6HnZG+d513evp2N0rGcYMhMpR9YjW5CfIAeREzyLlcd09twUE+v5NvII8kvkSEyc5xOYHBvnGaaeOyQspFgOfiynJz8FR3mneL7B29Bv8W9FVJynCdFlVuy4PHu7P2ej6/KcrdO8Ud3v7E3D5UGel/UzUkeVFw/z5ozfki7nqbS+nTkgWa7P2OKX8zlUr0vfru7fqmZRNig9zOHzyjw65Fm0n6TRHer+ElKhP/NirvPsw//zvdM893q/5j0zqrvz+VQ/S96sys1QnpjiAu+P3ShLaYGzoP0xG97X4/Dy/ig6ajD2qKGTdLVfj/86dDLQ+bOh0+nqJc73UMezkuJbCLXFel6S3+OF8tzEb+vZqUYko9Ppno3cn69WRjQX0g8wjyLXbNccDqjbqVJ+O58d5mDmfHYYbpnp/ivOMtN97h+82ixL95GWme5fm7RZtu4jp1lm2r0JlpnuI3taZtqPdpaZ9uNdTKRf13H7lWWm4/agZabDstky0/FdjYnzWSQfE+ezyGzLTMdjlGWm48F7hPNZhLG50GeRLG02Qvvb1TLT/notM+3vO5+GPrP8xjLT/u6zzLS/8dosS/v7wd+1mfb3Ssyc/VrJ34P7talybfZra059/n7q8z6zmOPuOb1C9wH8HnUuL8Y2T720rKihsr7AWHzOTiEtPhPYx43G9pY1UzJe1tkbGC8rtNyXb6Pu42WlSi/BZbxM3OA/Y9wwl3gcQNR4WcxMf4eOntOOmdWK2MfO7GNmlydj/jnHzMxnhSMS93Sx0BO523gejLXivqy0Xn/QkHdt7jXodn2v0u3u6YS7bmmAWxE+p9nXNDQEPbee6iNnEiLtkLHIrYSz2TWcBUtXG8sWJLztVX5Z4ySfKjuJbmEV97zKXpHyuVjp7ZX9xBpc9jNMbaPyn2s9jlLDP9q/Aep+tM7rK6QvyIkgLcx9AblWYSgK1LmgtGnqG7D4kjxjHES68eCV2yY4bWrZaLO4tJZKsrqmNLgs6+8PecrOzykfUZ7l7mmEu5JGem8Vq49/RN07n9SId32+F7vOcT/9TDJf3f8FXwgZe5M0bbC+3eg0f1vpDdZ7RgbrLdfPTduU3mTOrfLq9O+eKHs8tmJdgjnXh/iG7tMoYbO3Wdn9HHOZZG1N3jvWMzjrako=
*/