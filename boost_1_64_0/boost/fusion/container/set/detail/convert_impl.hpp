/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1341)
#define FUSION_CONVERT_IMPL_09232005_1341

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/as_set.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct set_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<set_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef detail::as_set<result_of::size<Sequence>::value> gen;
                typedef typename gen::
                    template apply<typename result_of::begin<Sequence>::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
kOHbbeW3LbfEJ9Lf92uoi59kjc2MZblkuMSqcgxXIhLZltfqjLemtuXnbfnYC6uMk2txxK6KkPuRMo3cn1xpiNFGWfRxsXSxXbMSExOU7O3zTlanjTNsN7a6k/udjnFibePkyXeJmWUbtsVwb1OJfdTxVfu9ob0So2/XYf13yxH795fb6u+Fmt+7+/Pe8fhXv5vR/F5f+e/plfedjeb3Wl3fqzS/l+v6nqr5vWhX907L/+7H8t67dq+vDJ++rnWDAZ81X7SpwUOX9nW4OsF+LzTPIscXOe4o/WTr4ELZ0GvXIpYOeqA3emI7rIddsAEOx4aYhI1wBTbGx7EJrsKmuB698Sg2w9exJZ7F1nge26C9T7scV3CilEvbpz2C8eriKCnHaByIkTgGx+AdOBbH4R3qfOVYAekm8x3PeJ44AQPxLhyJEzEBo2U5YzAZY9FxTzlP5ntI5qu9p9yO8RphB2yPHTEAO2MUdsUc9JP688ddGIAvYTfch93xqsxf9t/s1+3fByj1i8pn400sB27CprgZ2+MW9MenMQ2fxWzcjvfiDjyKu/B9fBF/wZdQyWwv1seXsQ3uw0DcjwPxFYzCV/EiHsZqlOkI1sRj2AyPoz++jjPwJK7GU5iPb+BG/DvuwjfxQyzE3/EtrFqFPs5YHc9gZ/wAI/AsjsHzmIkX8DG8iKvxU/wdP8M27D8+R1/8J47BL3Amfolz8Wt8A7/Bb/EK/oBXsUk19rnYB69hP/wBB+OPaMXruBx/wsfwBq7D33Aj/o7Po4X1uxsr41Gsgm9iVfwAq+EnWB2/whr4M7phVdqBO9bFmtgQb8KtLGdYPXdLGimPtJN0hnSD1LK+uyWUlExaRiognSZdJ3k3cLeEkBJIuaStpOOkSyS3hu6WzqQIUjZpJWkf6QKpaiN3iy8pnGQlLSftJp0jWRq7l/gsgndj8sYgzOXvE3C+Mg3pOOkyyaOJu6U7KYo0h5RPOkK6RKrl5W7xJ0WSckhrSAdJRSS3pu4WH1IIaQJpPmkD6TjpMsnDm/mSokhzSPmkI6RLpFrNmC8pkpRDWtPMveKZiYpnJnTPTBxs5l7u5ybOME3V5rRLUigpuXnFMxQVn4pPxafiU/H5//38J+7/K5Hh/4z7/8p12NaadwCulD4AQyvzexZDcbCPEhRJdx3WXgBL2eLSb91viEuvf5dEic/HZ1uMz8fr49I31MV9V67iOacPMYnbLtePXFxf+POuH5X3mfPyPlv+Z12HMr/u8793fcr8OtRf3/ehdZoyvNO2r5ZfmzHtySbfzl8VMPJCuMRbqCTbhWwvvoaYZrUl9nMdbIF10Rc9MQAb4ABsiOHYGCOxCSajF1qxKS5Hb1yFrXArtsZCbIPvYnu8iL4SC7oD1sRO2A47423YBW/HAEzCQEzFbjgLu+M9eAsuxltxBfbAPRiEL2Nv/CcG45fYB3/DvtiauuiHPjgAO+MgvBUHYwgOwVAMQ+KKlvqcfm7Himf1K353/nvP6l+o+I1Z8an4VHwqPhWfik/F5y/4/Af6/ysv+lR+/v9bv/2VZ6sT+YGSn8ZzWvy0Dx3dP3r00CG8SXBqdHY2v2X4+0z+7pGu/F2e8Rw0IrL/iNuHD+0fro6nzCeoPvOxjed4kV90QmKS7c+Wrvz9BL/ZD8p8HM+H9x8YOWgUT4YNHRgdecft0bEJcdlxacr4kq91SonjS/bO/C0ZyvhJKYlpCUNDJXvHM7Ynyb9lhnN+g4cOCg9lLMmUcaQuTMaRjBhH6sOqKdeYUWMHyRiOvA41Yz5We51GUOzhgyj3aHUkdT55U2WcYZqx4pPVvHYyTstM+zjKU59j+0cO4s2EMiP7M3RXmjo=
*/