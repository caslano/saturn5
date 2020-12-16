/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_20061024_1959)
#define FUSION_DEREF_IMPL_20061024_1959

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    namespace detail
    {
        struct poly_deref
        {
            template<typename Sig>
            struct result;

            template<typename It>
            struct result<poly_deref(It)>
            {
                typedef typename remove_const<
                    typename remove_reference<It>::type>::type it;

                typedef typename mpl::eval_if<is_same<it, unused_type>,
                    mpl::identity<unused_type>,
                    result_of::deref<it> >::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_deref(It)>::type
            operator()(const It& it) const
            {
                return fusion::deref(it);
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_type operator()(unused_type const&) const
            {
                return unused_type();
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<zip_view_iterator_tag>
        {
            template<typename It>
            struct apply
            {
                typedef typename result_of::as_vector<
                    typename result_of::transform<typename It::iterators, detail::poly_deref>::type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(It const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_deref()));
                }
            };
        };
    }
}}

#endif

/* deref_impl.hpp
oRnpmY0BG30+/ATlAubNLC7qaBG0ZGFdmi3oSP2JNTeEDz2AViDsxPYyztTDMHNbfWFGTzStsAjd0edoccL8ncaPRUsS9vca3x9o6cLqfHn6DC1X2H9ejNhHcxhubpOellajBQl74hu+AS1KWID2YRJaorCz2X+3QUsV9nfPEpPQssGcmcXW8fmGlgfmxax3nZFkqhHwOs+s7GzbMzQHsNLM9v/qfB5NB4bvqWPBBteKCvtj+yyNYIb/3/lZFvssbR9+aYsWOJLu/G+bEvl8MFoss9lgI+aMLI1mArP///+7eS7Y8VMll6OlguFnIiPYwYIRddHSwKyYdWs77wraETBLZvmXxnRHSwcrwiwgc8AQtAww/Fw3H2zpkjuJf2y/ZQGY8//Puchiv6VV9AQTmmoUfvb+YxZnNjVDCwHD3/WXgNl10R5ESwDD18+lYHHBRbzRksFsmXVcelCJlibq4rvnTEXLBfNl5m8Y8zedM8G8btfkwaF0TjAls7ZbI+eh6cAqMDNdOPsYLRHMj5lrvqIkWqqoW5vin0DnBLNj9jRgTyZlDebCrFL/mOPUw2j4fsTPOfP4EbQAMHdmJyYtd0LTgtkzq775aQM0PRjf713dVovQ4kRd697zstAMYj/ngmAtmgnMgdmMQSllKBfRw/mVXyjPDFHXvO+xXWjZYCWZORUMDEBTjDE/50x1rVGUGZgtM+vSp7ahaURd/v2uy9ECwdTMVs/YXwtNB8bPWe3amCFoUWB8tvuimw+mPEXdzzux3ylPMC9m8U2Cb1GeYGWYVfLYMAMtC6wqs8nNfOej2Yw1v/NPDVefowWBeTCzK9E7Bk0PVo1ZT6sph9GSwGx4706v7dGSwXyZbepv34bOCcZzscq0MqDlgJXnc7eLaIqmHme+38eRm3qhBYC5MFtcauEltJBx9Fnqt5WceZH604KpWN2l0akHaX5g9szaVD1fm+YHxjM7f8uOZmQEUzPzMUQp0FLArNlZHjcedQotTex362feBLQMMAdmm9db+KBlg7kx80/f3REtT/T3fPIvDZrNePN71nZH43DKE4zP6OSbDt5oQWDuzLqtX5GIpgdzZXZjTLE8ygyM99esq1NzNAOYktuWjz8pTzBnvl+/GR3QksH43Lereq9ASwdzZHZ5XKe5aFlgPBdF6O7yaLmyztT7PloBGJ+tw+NidK/VE+CvEDJbcqrjVcoMzIXn4v3KBU0Hxs9yvFSTE2ixYs3x2n5b0BLBeJ7dy3po0ZLAHJidcK8fS5mB8bn/yj7XGC0DjM+26O79zygXME9m8U9+nEGz+ds8s23KOpUpFzB+zvKtlK3QAsCKM7OdvWIGmhaMZ72iSvgRygWMZzZh0I5jaAYwnnXf9d3WUy5gvIexRyuOQUsD470vf/tzAVo2mJJZSPpZe8pFnDPy0YcllIvB/O6u69vYCk0D5sYzaxXQBS0IzInZ7n8cLqDpwLyZOQ72SkZLAPNl1tWuWye0lWD8tce6croz2gawYsweuR4JRksF4++bfjtr7kdLB3NgljjmpAYtS6wZ46JsSnmC8dfy7x/vWFKeYs2rg5vHoBWI/haWLzac8pxofif8Aou1oDzBeA/++cPt0LRgjswW+Pc7gKYH4/Prvv5tebQ4MD73GcMdXdCMYB7MrmV1Pk95gnkx850Xcp8yA9Mwe7BpwSXqHcydWVz5Tw/R1JPM78vhWSP6ogWCuTFreLVSZeodjO83vdp9W+pP1B07WnYrWiIYz6zExxPuaElgLsyie4xRUe9gfsz61e9D9zobjM89VJmbjJYLxufwY+XZI2iKyeL1s9bb4pQLmCfPpaBp4Z0A4/01epXZGU0HpmTW8s0=
*/