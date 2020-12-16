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
ke/buvlSWKasW+LiuzXc5DdhrN7XNkOOhX36GQ51YqeUw+1SJ7YQ2it9+brYl4PaE9fqzjUB37N6/10t/8km+Zffq7Jehl2e4n21CBdLnrIJAeQprat9nrRexg3nqfa737+d9GtOLczN0n8rYKQxb9KX2bC+1aJtYKw/gW21BM5KHr9SlpHH0w55lF/3yg8at/Pp8DtI8mn+Wycc56jrL6K+KOtbZS4vY913vN5aWFhcYD/vSqAf/5Nn4nbAzhikXEN1c9of/ceu1c3PRPvujvN3GX//yrWDG9c8/na/+ZQc1P3ev1ObZ0PJksO1UK7+OVgTIdtxoLOs9sczq13dXGY9cTJ2Vn6Ddbfbf7kUVyuKuu9lTRq4fmyiXj+qeShv4nwd3F07tjLfU3Z+RnZWVnaW3RW/fi1Xqm6r1dEgOVfsDFKWyQ0AWV9+G0t/VC0q/qluk6bP0WSXBNs0bRfM8jQyvoH3d/Vgv6Us4xzmAYs3zBNYZLWp5Wgsy1MkrLx+L9fjv8Vg5ZzSUy9LbnUU27Jrz65Sj0oauBZPM1yLf9jbvk6V+dVe6yqdnrUyWOfnfN4JkOv2SzvaXwcEyLX74nb21w1Bcv1e3Nz8GiQNf+oq18cL7a+nL79E0uDSSZYb6iVxLLLlyHGRMRIyviHVkL7JdYt6i8bwedjnr/3N8beFd3t9bgv1u74ldolSvnjlOKhzJ9Vdt5KZesuffOh12eL8eZJrQ+PnU+ZNNPksft1B35aba4PV+nfaX+sAVQjlWh71c1ky/2P93Cypqzsp2x8Jg3hfbVg3HEu0z4lVykNCXbnUSLlUyrl7D+Ep5Tqvn7FcGnfONjsHJ+vncjUq0zkvQ+3Pyeq++ZC/4wT1XKfmSeqOHl9mcVFRtlI/nD57wQFa5h5Rfs/ggxiiXMP01/ZNblkYP/sN3heo/V1Srn2W2Mj8HBtpUrdlri99Pjs5N8l7KnJxns1LjukJ9vkI+zdTOWdo+dXvDQxv57Tf+jY+7HOpEmdY3TaJLrbxZenrst7uHvbfAQek7B6SerGX0D2KeAfUll2u1VrMt7mVuyrpeanMdOr2/R5DnZRzqP3nROZFlOOrpeP4+/0smVJek+Q36zgMVY7tQMmfPgyNKN38bl4zSM6j1D3lfekg5+9q473LALvv6uICW1Gx1ZadJecEp98o+jlhTy/9u12vA94h+jmAM6Tr37SRxnrGMa/iOJ3poM1/0FbNr+N8lYvlcyFjDn6FubUaOxbhQo0haOyYBvMxB42fu+tCzdF1ocYKNHbuLvMxKI0fK3Ch5vqar44tGPWnqoVbPn7/w5EBV7fcHrs97Nzm+rJ4SduOtPlUUGYXY5Z8+MOaaGMOBmBPHIgROAhH4mCcjENwCkZgJkZiNkZhPkbjUhxeO/dUE2lzkbYY0lX7Q+fJb+R5Xlo68zEGF+AETMWpmI5XYAYuwmwswoV4Ky7COzAXH8LFeBSX4DuYj6ewAJuSZiH2RguGYRGOQivORRtehcX4GyzFHXgVPoar8ElcjYfwavw7/gbP4DXYgn1cg63xWgzBdRiL12McbsAs3IhL8Aa8ETfhTXgTbsObcS/ego/hFnwKt+KLeBu+jbfjR7gNP8Ht+jPapT0F0wkVDs9oj5XjPhZ74TgciONxKMbhVJyAyTgJUzBejm8iwRJgH38LjJP4T8lYgr9jLzyNA/EfOAS/xDj8ClPwjOQ7vAnrSrwvSb3pIc/nV17J8mz5uVJf50l+5+MYTMF4XICJeIXkPxUzMROvwSzchDn4FObic7gEazAPvUkzH1uiBQfiUoxAKy7GYizE5fgirsRXsBS/xKvwW1yNndmXMhyLV+N4XIOL8FrcgNc=
*/