/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_PP_DEQUE_TIE_07192005_1242)
#define FUSION_PP_DEQUE_TIE_07192005_1242

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/deque_tie.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque_tie" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
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

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
                FUSION_MAX_DEQUE_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct deque_tie;
    }

#define BOOST_FUSION_REF(z, n, data) BOOST_PP_CAT(T, n)&

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_deque_tie.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_DEQUE_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_REF

}}

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

    namespace result_of
    {
        template <BOOST_PP_ENUM_PARAMS(N, typename T)>
        #define TEXT(z, n, text) , text
        struct deque_tie< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_DEQUE_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef deque<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>
    deque_tie(BOOST_PP_ENUM_BINARY_PARAMS(N, T, & arg))
    {
        return deque<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_deque_tie.hpp
XedBzpSKeTN2xl6X8s7Wtp+lHmek3Ucm9W86zbieZOm7f4P0se1M+oK6leW7jhW5+N/FHAN6Y1w0+y1U+u+vl3qsJn1FJlXaeuQUFBQyZiWd1irg0Pdm7mjD8QSaPr9Xyb5UH2uROueTzupzh6Yv+1rZjlw5/nJI1Up7Fmi2Iy/Dwv/T255LNx9+r6u2wfVa4Wr9/RhpcS330q8VtPtT/7jaL/XZJc+PHiedU455i+t4jIv5/GmvWeI1n0ntflS309Rg/XqZCjX10rZTgfefyYupn/1avehaidWnzMGCA/BbZT/OcdbPOeZTTv6yDz/x8HvxhOr7PnW+6/d9tc5547zOZ4Y3aY8Dfle6jxdNcd1mL+Zcd/5+SNN8Bot1fiuYNL8Z5btIc+2k+t5hPRn7I9e0qvenUrT8BkgLZv1rbXOtxRWpf0vq/wYs1fwGtO0L9XXDrKyCgvQZWY5zu3yX6tznSNC5f6H+HgmRfvSpcm6ZQvpOObcsUB0byjZykrSNrvP+mNWMAVMfnwVjbVnJuU/1mdeOIWgsY1Zl3GUWno/k3wut9XO5u+LNd5xynBbfIsdpLvEM+btgoe1vBiJIZs5t+D7S9XiL17mXYTK4l5GiuZdh39YQa7soJdmOj1D2QTe282ml756tLrqfZ/V3wnlpl16sHI6t8EfqWm3btsy8VOsNQNdTjrTPBg+f6WL5TMs1sdtns1xzj03GXesey7Ha6xnN/t16va3w8fIdM4Z0gcyKF1m3g28X3/av5veU4X5T7wv1NUSY+vtbM+YkRqmg/PemMl75n0qbL1LPmz3LnJqf43U99e4haO+/hGnOcerPbwIVUZYu8pu+AwYo4ySLVXXKzLLeFKZejMr1PD5Z+Ywsv8097snNtnpl0ajOa4568prqHqxZvV2651HntrZz3lcyPp9r78tq74to2iQtRO6zsQGh+A7Wpk1Mt6vahNtT3GOzNYmX96WvuEPVJsbbKfViMx3X59prM/m+8XL7413azrc2sZ8vToa4j/mrF0W+dxiNh/Rtjuc6BnOiZzdzH28XxLpVhuX6Pt9yHR/mRK9qpj83fNjSn3dueHNz/bnhTUt/2bnhHffSm+uPAS1d+vONAZ3ZQn/sZeXSX2bs5UD7trdw3/bgKKUjqcEc8ZmFZl+2/4YQ/WMgIdR9POQJZcyiQbkXOyf/oVD9OfBNy36eOfDt25fS0n1M5mylU7lRueY8szIjvi/HuPY+SQx2s76mZDS9MDdDs6916nQdbVFpUCdfxx6v1xkHHqIaB66uy5JWztjjLUgRpOuV467EoC5cM/qyX6hLTZ8B+Y4wrl9wa+3nE6lfrEH9fP2M3hDi+TMq42sN55vXH2/668Xq1h9v6vs42l9rvOzPPS5Wf7zyrzde9lHreNl6rWrdNyIvtdGknXOfOHvt19FG46R9H0d7yHrcPvdayufbZ7b45F/3lMWdarfrnG18ramW9I+QfhMppE78O06eqUQE2sa9RGELjMb22AtHYm8chzGYgn1xGvbDm7E/rsIBuAZjcT8OxmcxDs/hMGxCmcOxBY7Evjgah2ACjsAxOA0TcQaOxVvRhMtwHG7C8fgHTMIDmIzP4wQ8ghPxfZyEH+MUDGHbb8T+OBUHYirGYzqmYQbOwOl4K87AEszGO/FmlFji0ueCbSSlaGKJ59exjSMowEFoQfv7ymp430x53yx5Xy7axhVKnwPpi5CiGVcYI+Ns+mEU9scJOACnYCwuwMF4Ow7BbTgUt+NwrMQReBTj8RSOxK9xlIwvGY1NcQyG4VjshOMxCpOwJ06QfvVldaSvgfRBoN7We+JrJZZhhoyHzMLROAOTMQfT8GbMwd9hIc4=
*/