/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_20061213_2207)
#define FUSION_CONVERT_IMPL_20061213_2207

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/convert.hpp>
#include <boost/fusion/container/deque/deque.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace result_of
    {
        template <typename Sequence>
        struct as_deque;
    }

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<deque_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef result_of::as_deque<Sequence> gen;
                typedef typename gen::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq)
#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
                        , fusion::end(seq)
#endif
                    );
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
wJb4XflAcjP9P7lUltg05rRuHNyizE1XH/aevWloLaO3H9SGVQZPGcJk+nJOi4bb41dLlzPXMbJIDanAS6tUva2eEHUvXBV7dE9CKsfWbw/bemP0alOl2Ra7XzIodJLbKtff13GQWz1pztSiGj5thERy3GU8TjVYHpDIrwqUeMOuY6wfydaxDX8/Q/kRLj82JQ7uzDiHHykHj88o3YY/JA39otCwimXWucDDEnvLaN0+o71L5GzVLyU254Ac93Bz02AxT8Upmi7FCix+5ExJ6oNj5P/TYTSDYE+pXQYezPmP89bcsq7cGCx6H8rB1RG7v6uGu5bGc0+dLTye/Rr0qiwlnYiyN45q0Q87GtDxtm6dEUVDWS3LV913NfIJqv0oOk1+4JxLi+L76Jz+BpY465kxWIzgbi+/feVr++ftGXhPonrIaC87tIQMT0cF4CZk6oOAPRvQ+XhpJ1cdkt3zCFY+labBILgfY6CIc7ebmgmgETVQALVsu3NCLPSnAeVbJlwtT+SA2S0Z8R3IYoB3asIpzr9GNtExvASQLuHbEw0VBW/cLpApsUJWzw==
*/