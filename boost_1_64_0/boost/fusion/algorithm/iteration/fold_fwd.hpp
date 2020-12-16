/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::fold<
        Seq
      , State const
      , F
    >::type
    fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::fold<
        Seq const
      , State const
      , F
    >::type
    fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::fold<
        Seq
      , State
      , F
    >::type
    fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::fold<
        Seq const
      , State
      , F
    >::type
    fold(Seq const& seq, State& state, F f);
}}

#endif

/* fold_fwd.hpp
1yn/O13yL5Ytmh+eDM9TviWy4SyDc+BMeKts1yrhrHB/ak8bZri0x7XS/zrYHVZofFwPj4Z/gKPhDdb5Z7VsViLHl2J2t1LM7i7wfdgLfqDfo4P2jqm7fr8XHIb4FNO6nWJa94ArNE4fhifIFn+MbPEnwpUWvWob0GuZ9KqWXvdKr/vMdmLf1budLlc7XaF2mq92ulLtdJXa6WrrdaT8Tg/MNztn45/q0/4n7CP9kmBP5Vcr/d5QzPA3oX6nfUrmMJffvarxtVbt/JplXNZL/9ku47Kryuuu8lLkE+FgzbM9NE4P0X2iJyyFhyp/Mtb+HWNN8+9Bej9pfC5TLOjLYW84H/aDV8MT4AJ4CrwG5sPrYDGsgGU+2frBhXABvFGx92+CqxRj+jnFmF6v2NKfK7b0l7ASfq/Y0s0MG1W4D6yCh8M7YT94FxwA74YnwHvgcFgNC+C9sFyxpK9SLOkF8AH1a/Ye2kfT/hrtEBi/E3TG6xTNV6cqJvZYjYvT4HjFHC+A4+A1cDxcCM/wyZYbroSZ8K/wTPgJPAv+CCfLlvpsmAGzYTbMkc3nFDgb5srmMw8ugdPgY3A6fBrmwzWwAL6lGOQ74AyYRJ0KYTt4LuwLi2AGLIYT4XnwYlgCL4Ol8ApYBpcrJvnLikm+VjHIP4cXwm/hXGiEN7wYdoaXwG7w0lA7+7SPBos1nveGEzTeknUdtFWs3gPgsbAdPBG2h8NhB3gW7AjzYCf5/uhsud7qG7hOb9N1U6nrZrHld1UNXKc3Sb+bYapsqcM2nS84bE5dbTXTlK5PlHTlStc7SroaS34bItKNN+//2rOgDi73/2c0Dz4Lu8MaOEqx/sfC5+Bkxfz3wzXwEviCrusX5SvgJZW3CKlReV+ovGS4IDTfqby1Wse8Bg+Df4Hj4OswG9bCc+Abiin/Jrwb/hUuh+tkQ/0WfBiuhy9oXl+nef1D+K6ut/ekH34ytK/AHK95z3BHtkP6fajr/SN4OPxY895mOAR+ovXKp/BUuAVOg5/Dq+CXsApula33V/AhWC/9voavw280z22D/4DfKgb+d/AIuB0eBX+EJ8IdMA/+BKdDKlA+cw8Ay2Ez+fZoDpfBveDDsKVicu8N34St4HrYBi5s4YvJdrWKiXE14l+WWAznpvjNv5wd68ZDkmKyZW3sGM6NFb95Z2M3bz0kKS4bV2f85sRsXBuI3Yx9a1PM5sawcR1T3aCdK3HlvWM2z66Oz+bV15NxhGQgs5EqZA2yBUk+lFj4yASkDFmIrEI2IjuQlF9hH4vkIvOQaqQG2YK0OYx8kWFINjIXqURWIxuR5r34f2QCUoYs7NVkt9r0afo0fZo+TZ+mT9On6dP0afo0fZo+TZ//rM8uiv8/paCstKwx4v8b8fanGOembwv4ACg1IlsF7byyynKmFOaRfSDNVNL4K400M/IuyJpZmjM9z5bK8Acw/Uhf2I5khd4VzUW6IrOQvCHGfyiu4/nBYEYnjZyQNX7CuJFjT4l+VjBKfEedFzOaxrQXKGpvj2eYAo/rFEiHoZbPfv61mfv516oVjX/+NVTm/c3cz5vWrtg1501D/bUoSecmFbftEzjNGBcPBM8b9iuI7K/odg06L+/aX5TvsAcqh+YZeO94gGb/mf1s2irLLsQcD6U+25nA3Xf2L94zfvHGPYk3fke8ZwV3VzwU97N/Xmf8Gu9M4y99JnBH4OzfyjuK+nbdcdHEu469tf7MBdtuSSxeSYZPc6vm3PkRZ1iOlr/m/nAEHCD/zAOhHw6CJfAYOAuacQg0/2lerGjg3Wut0vVuIN3LPs0pmmvQMzDvrVa646XnSTp7crLegQ6Dk+AIOA+eAm+F6To=
*/