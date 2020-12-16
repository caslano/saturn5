/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_NEXT_IMPL_SEP_24_2009_0116PM)
#define BOOST_FUSION_NVIEW_NEXT_IMPL_SEP_24_2009_0116PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::next<first_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.seq);
                }
            };
        };
    }

}}

#endif

/* next_impl.hpp
mHThQJTBij/LPjS5HAlrnWQbjlGQ5yYolJcFzVDE6sL++XAM6cJBKIfA90NnE6ewuYDWinS1uhBskC4HAwWPOZTki7WiJ8rh1PlD6XxuONTSnMhIVmkb3PLXCkLB7kmV5gvbcLCR0/LHlpNM6FGwYT+yDakq5eB3yeqcwlDEntePyocxJIdeKIeUO+vOMqFHwjjyJZco9SVD8vWBUDB9GJ0PeeRT90a+t0xrfzN1AMea77TPVFFvQRAZDtb5JMuBULDaG+Pz4XSSg1GLKui7b4kJPQIiGtV1VaoPkdlB2fOCUDAf6th8mEHzoi/K4bYeEytN6OGQ04dikvsrWy8qXbKqU/H322e4dfniHqlRo6rDa+PTTQ4Pg7QEyn1Udj4zq7kpnKxcFoYidj405It45CEsHjkUfsqh9bKzMv9J8jmV+X52T2CBzX8x4/9QqCU92KEr6EFI9GFkTFbhRoaBxZ3Oy4fJJIMS5HX3jx9QP4whUJFNNlFFzidRKNtTIAR8b31LPlxNMuiHMvjtseO9JnQwbLbO7dWdVVUGG6ukFT1nKGLXhfvs+dCfzYcycCbSP0xQFnOSHXAS7xf8r8qHl8k/GID83/tzSj+Tw1IYkUr7qCR1eiD53FYgYD7zE/lwMOnAQJTBZUkbKNd3EOS0pxoLKvr+R5Hoki4EF89feD4fXiU9GGTEFeIHvGlyORA2JlMMWpUeNPV3Bt2Yk+1y10o0jAwLO7N8DX1m0odSlMWkGdvo3HYARGjvsDFerSw8rohElWBIeN7rpnxxr7IMZfHSLyG6KdNf5LU42qmVhbQkaI6D57e8nQ+JlN80GJ8/jz7jRJPTfjCdON+tWCcaXBKTGjgOe1/9bj54yE4MQTlkvXDwdSanJbCS7EQG6kNnhXLwBzzyzQQhYTHIj/LhJpLFoUbeX/sJU8lzwjo9dDcgTa1OREJe+bIgJCzessf2o4YyP+oQKC+lNTRfnSya+le6PB6JCQ42Dr63OLY7/ElyOAzl0G7xdDqxK4J5CRSHVGgvDRqlOtYch5BDcEp34VMdznyqvjAijvZYKu4jcxrlrqE2El7v8vjusILsxBEoi+9GnLzLhPaBSBeyGGmKYi9EZr3EmGwUCp7709Rd2IhhzEb0hhwH+VWqYnBEZFjWdRKOg9dyusOWw5FMDr1EPWSHiloFNo1VWFBC4sk2Q8LjEHd3h+00N45CWSz9MeVqE3owXBdH9lJVXJLI9EVkXaVogYTfI7ivOwwkvRiOsqj+elIhVTaDhdkUlVBrJ+TVMeE4+P7rxe6i571xH/mdo/q+YXJ6EKzJJYnspyhGSzQGA7Lup7dAwmtZfGXbipHMVhwIm0gW0EWprcCQsnSbKXCINTS5ABaRHI5GOXj9HQaYnPYQ9UDL4pTODa+/UeKBP8dh55SnFAh9OIbpQyG8n0RxGrVrBwbY6ySmjjIkfP/VyZbFKCaLApEvOEpFnRdBptEkSuJpho2D+xOZBfAEyWE0ymHxG1fdZnLaHZbo5E+oXUN9roGyxWCiYGd72bY+jGH6kA8XdqR+lQpjmAaR/uqAdEEgDl4r9cACKCY5jEU5HLXl5WWkBTDKqiGt1lZKq/jDUMTGJFAOVo6Ykfvy4xsN1KswD9Z3smplKpWD7NClQMHON/oXQAXFLsfj8/1vrvrYhOaCM51yHzop9af8KvYbhITny40rgELab0xAWTR2qaAqHt0gJ5FidslKdSLolpgXFIWCn3u6bVt5LLOVOaKmdnGcujiuSaT08IzAIdYMry2HciaHbNhMnO9QGNc3aFQxNwgJv6PmK4A3SRYTURb15W93N6FZkErclymWhXzP0kTB7GWdrROTmE5kwvw=
*/