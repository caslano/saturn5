/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NOT_EQUAL_TO_05052005_0431)
#define FUSION_NOT_EQUAL_TO_05052005_0431

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/not_equal_to.hpp>
#else
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    not_equal_to(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return result_of::size<Seq1>::value != result_of::size<Seq2>::value
            || detail::sequence_not_equal_to<
            Seq1 const, Seq2 const
            , result_of::size<Seq1>::value == result_of::size<Seq2>::value>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(a == b);
#endif
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_equality<Seq1, Seq2>
              , bool
            >::type
        operator!=(Seq1 const& a, Seq2 const& b)
        {
            return fusion::not_equal_to(a, b);
        }
    }
    using operators::operator!=;
}}

#endif

/* not_equal_to.hpp
G+fk77nYq/k9tTteO4wNPZsYNhm0u0rEgdHjduGf6dXiVAQFXA16IS8jE/aoy2SXSKW0duktUZwRC4ZT5mQb7/z6LL2w0ATvn5mItUmyIMcRywR47ByN9mocY5XI6vTetbtP4M1/P/ytgP8P74eQ2Qhv3tvg3psBx34LY/W9uBnH0tns3y/wpOWpaKBsGeVDi6WuQgbM2MQzuzS/pPvR5W4t3zIu7jD3T6Rvgb+Fl+xxUdKrObiH4icw2sARRmNpjvkghbwG4j20d3T5u1YCFY4HUu6izd+19rP55zo+8joih7znNPt1U/6Fg2yN58LfMkBux/9bX3QfqQOa36/AUfrcEoczphS395dvWEtdG2eZ3rEMvSfuVssLNp4pf764AaduX/LbBhwUQ2WsLdhweSTS/P2KwCnfjGr8mDGt9gCnWR9JcfWWm9cJyXI/UDg2O/T+T3Go9jXiMruDTzbiNL9rRze1celd28D7QTOeteZP3UzgNQQgoHyDolI1p+ia0oeEONpa0+fzgZe1DF1UCiegFOeLCLnTHp6hpKIa/4Em/rGiGyOKU7vEd8/MtI6M1tdizHVX0I8hm7gPy0aKe9EvghNx7vN1+cCY6a16nQQLDO6B5UkgWaOXFdPXO+b5SLyom8RRUNGVLBIZrb3/1E/3l2tvUuJYTNO7idCDfObxLRvDODt+ip8TCxaG9SZR3KQZbzTTOF9vxhFzmXAeugCc8k3AwtPlCBzxBmDj6Hh7eyqc7UYcuR+GfP+CyR7eLrBVz6Y6P3en5vPZgRNTDwnPSgeV7SFSdIJ2NDN3d/L76tTiPuQpzG5dkXN6fXRa0aTVrlmLyTPp1HyX4H8UB/CT/g+xP8i3o8PfEqNM+IX4sXOi5BmCjeQa08vgm+g/2OG+ITiSojxF0Im44puojhLvTJb8eoefM2Hag+168X/r/uRc/0/jRHP9Qoljd46c7OVc/9tjWg0Yeq5fxc+TFmwMugdKvJWbzMEbzais783DkefI/cn2AHh0jnBcU+/42xJv/llyao8Ft+zIrpU4zQFkzP3oYsBkknYCbbSIAVZ1fyJ9tPh9Zs037dGzLv4gdogkqVAHqvzPmOVnIhV7ELYxPU2dq5VXMuBzsgsdtJfgJX2yWkBzlJR+aB5NDEX+L4rNF7A9Fp72ba+Tg0GhfOJyHfkA/jmo5W+LEyRywovRXOWy3KPVnCz7xGyVftB+uMRplXXMLVASCPz7UW7aYmE+vpyqpE98+X/Gx5TVuHsX/jMupi7JUBPCpbaJqgl+1YaLqgi+sseCo3jNyyUBL8+BufzosvYSrlGeLuuagIvz4n8oC3cgwtVlaVuXJU/tRasjMw/UJY/79LURhyHyjQtvUfpLJtJfUs9UfbTvpbiTZlnH4M8TYNKJCAUi0u6MxJuEYpF4tXiNnaibuZ6hsVD7Na1dqjRUdwqf32EQ3ibw88y1y1jBBcu6XruK94O+yTuCBXhxCgTl2Ek+upTfy8QHy0j27nud5P+2l1P70MV7mG96OXK6xrgaOVK7zPesDbPuI7nvpVmAbQ52wOQPQ7gzn9n85BjcGEebyKpLyOrd7+5mvtBH9nyvQPw/SAwSzVVlvpiVGUZxJyqgpxGZn6lMaS9jzTvot0iHkDObC3muYN3nQv6RBGS7XX63gkBqO4Q9Ai5CN3K6C1gX+X/QDey9KeD/g27gTYRnn1N0X3dkW8WrEjvt9Xjs3Vkwxq4dxYiOhKgY2oPewF1sm3MC0nyAqHS+s4nVtLmzyefEQYabBgjTHsOjFsk6CZfk/aV2Pf4BjC8gaTm1YPHqzk9xmhidB0c9L+wm0HJBgN8czaAtQvbCGTpuyus71a7FoEo=
*/