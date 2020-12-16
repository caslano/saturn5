/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05042005_1142)
#define FUSION_END_IMPL_05042005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::size size;
                typedef vector_iterator<Sequence, size::value> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
Z35CfU7C5AYm23TIn3IS6ynlNKSZ030S06anqW0ljvdIvNizEgPHsg6Hvy9c10x9VuL0a5tVPSsxQn0GImmuz08MJs31+Yn1SHN9fuLHSc3cnp94gDTX5yduI831+YkrSHN9fuK/RjZze1bi61qamucdWpqa5/WkuT4rMVtLU/OcoKWpeQ7R0tQ8+2hpkmfH+05KW5TrfSeVxJrfe1L9/JbqfH63u3x+L3bvSdd2qyCXdivX5xvmXOQ5FHKdx+w8Mqc9K1GWM8v3wXGf3e9ZQaJZvr+OaRHSVuZ+X8okx+3KNmIdtxthH+uitP2k8N1Rns//yOhmevdTYE63ezKobW2O43VKyYMyfUfhBuJZ9Fa+g+PV76B89SJq3E7peqxK0RmPNNXx/arB/Uhqcu8Rx3uNKOU0lTLKbmg/Lj05Xisns95xTObfJPP73qLNH+0yv2sZLm9ksk0vR1CG+ALayrDEtQwjf/dlaNbK0Gkfd/rYMxkm57Qeck4rO+qwj7/jc9pq3qNCH/t7+8PR6s9pyvzbZf5NFdWf06ra/kuamGxTnD/lJJ7lRdm7ajnluJ7PMmtwPjv0ufP5bKfytxyjW3zmfj47c9L9fPbWSffz2a6T7uezO066n88KTrqfz64/6X4+iznpfj7zq3Q/n332gfv57ICWpuZ5B2mu57PVWpqaZ4uWpuY5XktT8xxCmuv5LFfnPFGocx/lJR6epbRa/Tymqg9TkmcKu52nSnTOUwk656RY12f16pyTwnTOSdE65x+zU1qEx2f6xuucf0Jdzj/a2EnPYxj1xxLWXZ+Mpz6iNVYlPTx/Z4eyMxuWzX3GmrW5+YE5nvqOaj/W0lNf0z7bdjdtKC/2/i645Yn6yfkbBuTcU9VHJL/7pT7g4+XcR/SI9BGVYV/8M16Fu3Ay8z6Oc3A3rsQnsASfxEfwKXwO9+Db+DR+hnvx+3r8fsfL6pNHDMFnZAxlYT35nS2/u5V8JTrcu/yg5Ot1DMM3sT++hSPwCE7HdzAXj+I3+DdcwLoqcDMew2DW+S4+iO/hU3gcX8b3sQI/wM+wEpuQzw8xEP+BvfEEPoQfYw8qh59gGH6K/fAk3sf5+zPchZ/jC3gKj+CXeAL/iQ353H+FbfE0huIZ3IZfYzDH/m9wMJ7Dv+C3GMvn/TwOwh/wBbyAI+lC+xFvxJ/wK/wZrdynyMuLazOxHi5Hb7wDG+AD2BAPYiM8hj74OTbG77EJNm7CNZO4Cv3QuynHCGyKl2Er9Md22BxDsAXuwJYY7kefI/bFNjgYA3AMtsOp2B6XYQe8HQNxK3bC3dgZ92MQXsYHuAu2xWDsjN1wIHbHPdgDY/hc9cR0vBxXYS9UPn8lXvIbU357+vDCzOt1WNV3GogtMQJb4Qhsg+OZJwizsAsuxK64AkOxGHvKNa+X4xa5j1Q3uY/UTt7P3hjF+xSOeynnPnhlU/KAB9nPCBxDJiLxKPmOwikckKPxREu5V3lr+vzxDJnqh/PpwI1FpeO2PzbAAbiOgcYDsSUduHH4p04cC7GL3EdqOztxBfZhJ+LxSX7MXImDuvMjAPczoHooXsVODcO32KnhOIGdGYGV7MxInMFOJOA/2YlRWEDmr8ZVeA3ehUn4EDtzLT6H1+HbOBbPYnLV8cFLfr/K71ofXoTxOhuVaby8P5MwAifjCMzAFJyBN2IWWjEHF+NsbKgce3A9788cuad7Ht7N+5OPwXyvrLiD96cAzXzu5+JTvD/zcHAz8ocHeH/mYyK/iBbgEd6fhTiRD0sRfsj7cxNmtuVaafyK92cxnsUlyueG92cp1mNHluEa3p+b0b8zx2e579cK7BRsv1Z6G+/PKgzrxph4fJw=
*/