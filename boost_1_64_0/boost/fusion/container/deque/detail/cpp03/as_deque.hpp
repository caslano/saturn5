/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_AS_DEQUE_20061213_2210)
#define FUSION_AS_DEQUE_20061213_2210

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/fusion/container/deque/deque.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <int size>
    struct as_deque
    {
        BOOST_STATIC_ASSERT_MSG(
            size <= FUSION_MAX_DEQUE_SIZE
          , "FUSION_MAX_DEQUE_SIZE limit is too low"
        );
    };

    template <>
    struct as_deque<0>
    {
        template <typename Iterator>
        struct apply
        {
            typedef deque<> type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return deque<>();
        }
    };

BOOST_FUSION_BARRIER_END
}}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/as_deque.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/as_deque" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
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

#define BOOST_FUSION_VALUE_OF_ITERATOR(z, n, data)                              \
    typedef typename fusion::result_of::value_of<BOOST_PP_CAT(I, n)>::type      \
        BOOST_PP_CAT(T, n);

#define BOOST_PP_FILENAME_1 <boost/fusion/container/deque/detail/cpp03/as_deque.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_DEQUE_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_NEXT_ITERATOR
#undef BOOST_FUSION_NEXT_CALL_ITERATOR
#undef BOOST_FUSION_VALUE_OF_ITERATOR

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

    template <>
    struct as_deque<N>
    {
        template <typename I0>
        struct apply
        {
            BOOST_PP_REPEAT(N, BOOST_FUSION_NEXT_ITERATOR, _)
            BOOST_PP_REPEAT(N, BOOST_FUSION_VALUE_OF_ITERATOR, _)
            typedef deque<BOOST_PP_ENUM_PARAMS(N, T)> type;
        };

        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_FUSION_NEXT_CALL_ITERATOR, _)
            return result(BOOST_PP_ENUM_PARAMS(N, *i));
        }
    };

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* as_deque.hpp
uFdiTVyFvXA19sY1OBjX4hBch2MxT8p9PZpwA6bhRlyND+E23IrHcBu+jNvxz5iPn+Iu/A53YyXKYg9Ww71SXld8pF0Rxkt5NbGO8WP7DeH+JwTvxrtwKEbjMByFwzERYzEdR2ImxuESjMeVOBHrEokJm+IkHIjJmIQWnIM5uABn4CqciZtxNh7COfgCzsePcQF+igvxB8zFmuRhEd6G92N9XIp9cBmG43KU41/aAZF26/nQ/vi/IPcPb2MjfAc747sYhRcxBv+CX2MEoVS2Fy31tyqGyvbSZKyXdAzBqdgfMzASp6l9tqUdDi6X7Wj7bHeW81IXbI7dsB2GYAfsjv0wFCOwBw7GMJyKvXER9sX7bfmV66q0qYGdBtfV0RLfWOyGCTgax8l2x+McnIAL8B5cgYm4AU24BSdp5pMslviop8RnP5/kJzIf6afYGT/DXngJY/DveA/+A5PxS8zFUtyOX+EuvIyH8Vt8F7/DEryCX+O/8Dv8HiuTjn9jCF7FUPwBh+OPGIs/4Tj0qUK+sRI+jFVwF1bDA1gdj2ANPIU1sQRvxQ/xNiR+rh/STgYjpBz8pH+F8jsr8wy+ikH4BwzBc1Ieb6AJ38TJ+CfciH/GTfgWnsQL+Ad8B5XI3pX8XkRffA9vxRKshx9gb/wQ++JHqI4hckneXcq/tferX8lYLpexKX6rzlMsbVGQ/OjmM25QWTO/ryzX3MVySbJcBxfL5bu5XIks187FcrRtkHyUPy9zhCzXwcVyuZrtRfs4n5c5X91e+cuVyHLNDZbrpt0fX0q85S/Ht3H3tpcky3VwsVy+LNfOxXIlmu1d8HE2vzSh9Fr6lhuMGSHL8a1V4nWxXJ5ue8bzQRfJch3KX46DQuJ1upyMefOV8+OqPvXPT+phU2yIZc8TZllvjsHzRIEcj09iSzyC3fEpHIhHMR6PYSoexxw8gbbrmny3w54G17UD8nz6KNbDx7AVPo498CB+LfU/SbZTJOe5Zsq3JtnOSUnnKUnn89gRT2NffAlH4iuYhGdwCr4q6X0N78PX8UH8A76I5/AdLMbP8Q28jG/it/hH/BHPo7/MhxqEF7ANvouD8CJOwPcxDUswAz/EOfgRrsG/4h78BI/gp3gcP8eT+IWUB+mX72nKdzZbefS05l/e88h5vxYG4h3YFmtjN6yDfbAuRmI9jJH6cQ82xGRshDMwAOdiY1yPTfAhbIonsBmewiD8NzaX60RrTMc2mInt8RB2wCPYEd/FTliCnbEGeemCtbAr9sJuGI4hOBa74wTsiYuwFy7FPvg09sWTeCe+jv3wfbwLP8AIvIT98XbKLxIb4UBsjFHYGQdhVxyCYTgU78IYHILDcBQOxxk4AtdhHG7BeNyDo/EQjsETmICncBzK+035JseyBu83v5T6XYpt8CvsipcxHL/BJPxW6vUVXIr/wg14FU/jD/gu/oj/wJ/wiswb/T1Ukut6ZWyNVTAcq+JQvAVjsTrantflGxusN3henyjnnXuwDSZhF5yEv8FknIa/xaU4FZfjNFyNmRIPdUO+aynfu2zx9LYed/K+SuLJxgC0YEuciR1xNvbAeTga5+NsXIALcBHm4X14FO/Hp3EJvoZL8Q1chl/gcizFlVhVeT7DAFyN7XANxuNazMR1OB/zcCFuxKfxIfwLbsIPcSt+hdvwDvK4A7vjTgzDXWjG3fgA7sFNuBcfw0fwD7gP/4iPSn1/DD/Bx/EnPIgtqX+HsC0exigswHR8EjPxKVyER/ERPIb78QSew0K8gE/jF3gS/4nP4Pf4LNb15RyFTfEFbIMvYjc8jT3wJc1xIN/deEbSHwd3KO/fsTY2xjoYjP7YE+thX6yP47E=
*/