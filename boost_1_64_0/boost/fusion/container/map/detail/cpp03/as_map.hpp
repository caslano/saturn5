/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_AS_MAP_0932005_1339)
#define FUSION_AS_MAP_0932005_1339

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/fusion/container/map/detail/cpp03/map.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <int size, bool is_assoc>
    struct as_map
    {
        BOOST_STATIC_ASSERT_MSG(
            size <= FUSION_MAX_MAP_SIZE
          , "FUSION_MAX_MAP_SIZE limit is too low"
        );
    };

    template <bool is_assoc>
    struct as_map<0, is_assoc>
    {
        template <typename Iterator>
        struct apply
        {
            typedef map<> type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return map<>();
        }
    };

BOOST_FUSION_BARRIER_END
}}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/map/detail/cpp03/preprocessed/as_map.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/as_map" FUSION_MAX_MAP_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

#define BOOST_FUSION_NEXT_ITERATOR(z, n, data)                                  \
    typedef typename fusion::result_of::next<BOOST_PP_CAT(I, n)>::type          \
        BOOST_PP_CAT(I, BOOST_PP_INC(n));

#define BOOST_FUSION_NEXT_CALL_ITERATOR(z, n, data)                             \
    typename gen::BOOST_PP_CAT(I, BOOST_PP_INC(n))                              \
        BOOST_PP_CAT(i, BOOST_PP_INC(n)) = fusion::next(BOOST_PP_CAT(i, n));

#define BOOST_FUSION_PAIR_FROM_ITERATOR(z, n, data)                             \
    typedef pair_from<BOOST_PP_CAT(I, n), is_assoc> BOOST_PP_CAT(D, n);         \
    typedef typename BOOST_PP_CAT(D, n)::type BOOST_PP_CAT(T, n);

#define BOOST_FUSION_DREF_CALL_ITERATOR(z, n, data)                             \
    gen::BOOST_PP_CAT(D, n)::call(BOOST_PP_CAT(i, n))

#define BOOST_PP_FILENAME_1 <boost/fusion/container/map/detail/cpp03/as_map.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_MAP_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_NEXT_ITERATOR
#undef BOOST_FUSION_NEXT_CALL_ITERATOR
#undef BOOST_FUSION_PAIR_FROM_ITERATOR
#undef BOOST_FUSION_DREF_CALL_ITERATOR

BOOST_FUSION_BARRIER_END
}}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    template <bool is_assoc>
    struct as_map<N, is_assoc>
    {
        template <typename I0>
        struct apply
        {
            BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_FUSION_NEXT_ITERATOR, _)
            BOOST_PP_REPEAT(N, BOOST_FUSION_PAIR_FROM_ITERATOR, _)
            typedef map<BOOST_PP_ENUM_PARAMS(N, T)> type;
        };

        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_FUSION_NEXT_CALL_ITERATOR, _)
            return result(BOOST_PP_ENUM(N, BOOST_FUSION_DREF_CALL_ITERATOR, _));
        }
    };

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* as_map.hpp
90mRY8OhezFt35PnvEfzZu/RtHPPpZ17N0t/L2ZZjbn6jkGZP9rv/X8cOby92YKvRy7vO9j9yo3vxQzVSburXMN4UAbuGCRH5iW5F/EXrIe/YiMswK54FZfhb/gO/o45eA3NfZylbRX7SfzqPs6MV5bqjVuxBX6M/rgNe+F2y9inhAyJhzZT4jH/dsmWeHayXG3cgw1xLwbgZxiIn+NA3Ifh+AU+ivvxBfwSl+BBfB+/wp14CL/Aw3gcj2A50j+Kd+AxbILH0QdPYGvMw0A8hQPxNIbhGTTfWyrtn9hUtkd9b+kkZSxUfALrYAp2wifxd3wKlZWfxoaYinJvqbRrmv4nXu29pa2knPRSTm2l3NthD+yAvbGj5PMiQdokKTtTfPxmYzskvl9ItxX+hqbzN96Lf2AwXsco/BMT0YV4p6ErzsFyuBTL43tYAfdiRTyA7pKPSvgbVkZPMlMF92FVvIQ10UU5JrAaeqIe62Ig1sNJ2AjnoTcuwia4GpviOmyGMqavtOGhlKN6TN/+Sjo4AHtjEPbHwTgcg+X4ehCn4xDZ3qG4EUMkHb1O2t2wk6Sjvnf3WTkOpmFbfA5lPWlT45ixsV6aHDcvYE+coVovQtYLtrHeS/K85JdxAKaj5TyRK+ul2DhPLHQln7gYe+IS7I2ZOBjfkfJYjom4AifjSimHuTppa8Jcid8DZ0n80yX+5+X4fQEDcQYG4SwchS9hNL6MUzEdX8BX8EV8DRfhbFyJczAL38BsnIef4D9xD76Jsv3SNsW22th+fzkeust23yvHQ4AcD71k++/DSdgbF2AflHvbpW2JPEv86nvb75Tj4C7Znx7YG6vjg1gDw7EmGrEWTsTaOB09cSbWtZ4npK0Ju9k4T/ixXG1shY2wNTbFNnIc6rETtlUfVxJfexvH1WuS/9nYGueo1suQ9XrZWG+uHMdvYHecZ11P2nBgoI313pTj+C0MxAx1Ptfb/7y9LflcLNu5BK2f0/X2P2+Zks93ZP8sV63nscH+5+09yecqHIBZsl6qEmS9E/L9oOQrSdb7WT4Pv2IdvIpD8DccyvK/41i8ho/jH5iG1/FFJBOpS9AF30FXPIDl8Ai6Ifmg7kHaF3CZ5OMO/jdIPobK8RGL9+BYDMI4NOA4fB7j8S0cj8fQiFdxgowdnoCLMFG1/VL/T7tA8e0fLp+3UKyHD2MQhuFQDMcojEAjRuIsHI3zMQrfRgNmYTRuwUfxW4zBS+irkzp9LC/5cEUvyUcKy7nhk6rl9bJ8BRvLT2K58jhZ9T0TIMsft/E9s0rOdx+gN36IbXAtdsJ12AM34Ar8CD/GjXgIs1W/N6QenHNN8d8b5+R4+k6Op3xJ53tsjz/gI/gjRuFFtO4niXe3jf3UQc4jHTEQO2EQ+mModsHR2BVTsBs+i91xId6Lq7EHrsEAzMH7cAf2Vp3PlDrvshrTP1MnddhYUY57Zf0FEt9Hcm9ejsS3FZvgxxLvNmyPn+AQ3IlG3IVTcDc+j3twCe7FTfgZ7sF9eAhz8Rx+gfmyHb9K/l1dyL/1d7bUN2N/G7+z/5T8sgD7A7AJuuJ9WE7K0Vsn9crYQOJxwZoSz3X173pZrqON9CrIebQi1kV3vBsroR4ro+W4TJd4etg4LsfKcRknx+U4bITx2BiNcpxOwC6YgNZnQ0i83jbOu1Ml3mewPj6L1u3fYX/7U1W/BwJkuYk2fg/0k+3vjz0xEHvhAzgQB+AIDEIDDkQjDlI9zz9P4v9A4lc/G8BL9mMD2Y8N0Q8bYT9sjMHYBB/DpjgBffBlvBszsBkuQl98D++xfm9JXSzWL15+pufHV8b5WA8XqI6Li7JeuI3jIl0+h6+hF84=
*/