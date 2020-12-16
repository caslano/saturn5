/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_PP_IS_ITERATING)
#if !defined(BOOST_FUSION_SEQUENCE_DEQUE_DETAIL_DEQUE_KEYED_VALUES_CALL_04122006_2211)
#define BOOST_FUSION_SEQUENCE_DEQUE_DETAIL_DEQUE_KEYED_VALUES_CALL_04122006_2211

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define FUSION_HASH #
#define FUSION_DEQUE_KEYED_VALUES_FORWARD(z, n, _)    \
   BOOST_FUSION_FWD_ELEM(BOOST_PP_CAT(T_, n), BOOST_PP_CAT(t, n))

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/deque/detail/cpp03/deque_keyed_values_call.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_DEQUE_SIZE)
#include BOOST_PP_ITERATE()

#undef FUSION_DEQUE_KEYED_VALUES_FORWARD
#undef FUSION_HASH
#endif
#else

#define N BOOST_PP_ITERATION()

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(BOOST_PP_ENUM_BINARY_PARAMS(N, typename detail::call_param<T, >::type t))
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
        #if N > 1
                        , BOOST_PP_ENUM_SHIFTED_PARAMS(N, T)
        #endif
                        >::construct(BOOST_PP_ENUM_SHIFTED_PARAMS(N, t)));
        }

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
        template <BOOST_PP_ENUM_PARAMS(N, typename T_)>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(BOOST_PP_ENUM_BINARY_PARAMS(N, T_, && t))
        {
            return type(BOOST_FUSION_FWD_ELEM(T_0, t0),
                        deque_keyed_values_impl<
                        next_index
        #if N > 1
                        , BOOST_PP_ENUM_SHIFTED_PARAMS(N, T_)
        #endif
                        >::forward_(BOOST_PP_ENUM_SHIFTED(N, FUSION_DEQUE_KEYED_VALUES_FORWARD, _)));
        }
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

#undef N
#endif

/* deque_keyed_values_call.hpp
QM/f/+ebFj7W/YruxrK31tpdz/vsPcvsNqn7oB7G/IO1ttfzP3vPMrtN7o2rehjrPkRr+/sd+Tf8Waatj23QvKdRh05a++s6NOy5pUOsb+NxeU9jG4RqNqDnf3afUZaatENwpFGHMM0OdB3O7jPKUpNvxDWiw/VIBFKKPMG7YMUah98v51haU9Ln+rDPhjwXij90gRXo/r67SZP5STyY632py+zPlMXqPiJNmtn3ykkrnCd7sjlsWFSxuPj/X2BXoAXKtoVNYVfNlreo+tv3ypBJTx/270I/pe/InKo87xYVpxWX6HvDnYQHGvl/zoa//rTmfrDu/YrN/WDd+c269xNeY/Ovbl3TclVWz49GffeH2Cfa503I/vX9pf09F8Vf//Afbf66qy1vX5CQ1nnG7gGfVA8oGkV729fjyzoo2BupauS8Hv89Zd1+pYdw76r+BxKuuUm4d1R/AQkX7iW94Dvc5/umEi7JQ7g/KeEGedDvDdV/Q9IL95JetYd8P9bDcd3pPtxHav3d6V6/v6jllXDhHtLbi5RJONZ1EM4eZoeE+0z8Ar+GF8C/wgnwbzAJfgNz4LfwdvgdXAu/h1vg32EV/AG+CE/BL+A/4NfwJ/gTPA218epn2Bv+AvtDFOPsPwAnwMbwatgE6vWx1n29zVD9WTyEm66Es65xX79T1XaV9MK9pFfnId/2qt2tcxcOqu3qwT7bquWQ9MK9pFfpId9han/0EG6oHg5Z716/WLW8Ei7cS3qp693n+4RaDg/hdqvl8KDf42q7GfQzSw+5y32+N6rl8BDuBtVOPdhfmVpeSS/cS3o1HvLNUMfRDe7Dpav2t8G9fmlqeSVcuJf0KiTcxV7G+Vo9nJfx+24J52UcLfMQbrpafx7CQfEXlPkSeJGEU/0FO4p/VycYC0OVeFYP8XpIvJ4S7wJ1/LnHvV5DlfSDN7pP/yJJf7ikP0KJl+oh3liJN07ijVf0qtroXq/dqn/lJvfp75X0n5L0n1biJXmIt0/ivSDx9qv9ZZPo5aW/1HkIl67oEX+vez2yRI95okeOEq/CQ7xrJF6hxCtW7V/ixXjsJ8hmCeeln6Qawpn3k0oP4aar+hnCmfUT+cYGo03K31XK3w32h+GqPXqIFyXxeku8Pqr+Ei/GSz+p9ZD+KEn/Ekk/Xi1Ppft4CRJvgsSbqNZ/pejlpZ9Uekj/WUn/OUn/ebU8HuK9LPEOSLyDqv3cL3p56SepHsKlq/rf716PXNEjT/TIV/X3EG+RxCuVeIv1fWnkfR1eL/HUfWnul/1otki8B2As3ArHwgfhRPgQvBJug2lwOyyAD8Mi+DtYCnfofvfyni3v3+Tr5He/Up6jb4G94G1wKCyH4+DtMBuulnwq4PXwDrgW3gkr4W/hfrgOHoDr4SvwLngEboCn4d1QU2YTbArvhZ2aMl4/yZnVSDlShRxCTiAhv8dXDklFViCaL/H+85pYjpzXxOt5jmZnXEfuCpzruB3uzQ7yeLZj0qmGn+84jjo+nB30q5zzeJx0OXva43mPS9KCdD/ejF2+n/uYccr72Y+lu0hj17/3DEjOczf46Fpyghp8FmRwTtBZ98dtyHmQlb/HRpBaxLKXvoqMQ3KRCmQPcgQ5jUQ8xb8h2cgqZDtyADmOtHw6yDIISUKKkQpkB7IfqUVOI53+wHiAJCHFyAZkL3IUOY2EPUN7IHOQJUglsh85hjR/lvSRGYgVqUB2IAeQ40jz56hfZDJiRdYie5AjyGkk7PkgSzySjZQj25EDyDHEUk3ZkHgkA1mBbEcOIcerAz7BgStwBa7A9f9+BSHzfzX//2xO4c8oSlmUkz/AvpX9Ge0B0M3SvE0Ra+2SZiQ=
*/