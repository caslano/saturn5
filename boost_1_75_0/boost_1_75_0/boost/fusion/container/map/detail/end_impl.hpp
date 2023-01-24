/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_END_IMPL_02042013_0857)
#define BOOST_FUSION_MAP_END_IMPL_02042013_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map_iterator.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template<>
        struct end_impl<map_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef map_iterator<Sequence, Sequence::size::value> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
G2RYqBbQ8wsskgZ78vqmSjuL3VTnOX0NpZ0PB1CdaMJf0mCw2kwUI17D1V//sBl6O9FM4bDezrSLIurtPJAbSsbwqC5PPovejlS4/uKCyF547zDst5x+hNbfa5OIVqFgDgXfPWLyv6Traby628y1aqKJXTe6qTKxGFqSgN7tH5kZGGgl3vCej3Tf8TqfVbKJ9fwuT+WrJDEd5YGX1MRm2PA71JqXmP1pSJRcNrolTM/F54cog0TmH769yyTiAOqzIay6raPClWQRAStLQQSrsvRq/JuGf68Tf0tOXyG6VNTJU7oK7Wj5QZ44UcrPpESZ+LbjRrWkC42dz8pzbOqEYc9OHf/psDkBUvCVI5Jzs3ofyVJ+yqp8pC6n8pGFopMLAZSfRpqpT68za7ukPvFyNh1M/5FVkSoSZaffiabfHaOIfle2qvUv/q1Ji4GRbSLMHAk+iFYV8MVIxIwfSSqsgo63IA6hsYTKySYLCakmCwlwIHe1JvBTxNqphjO1VOlMTVpISGKu/l8jyELCbrve6NER0O3Z8tpXoE6ZdFBrtr2bLLK9YS1p70lub5zR3gxqr1hvr82Z2ovT2zswpQXtncPtWYz2OlB7FXp784vP0J5Xi+f2HmxJe6/dTO09H6u395aIQn+cOHnOmtKlVvrd/CTOOSUbPfFECxrtxY1eYjR61c3YyVTeVR6Xt9bM9KsHoGG5cdT31x49Q997
*/