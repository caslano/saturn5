/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_AS_SET_0932005_1341)
#define FUSION_AS_SET_0932005_1341

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <int size>
    struct as_set
    {
        BOOST_STATIC_ASSERT_MSG(
            size <= FUSION_MAX_SET_SIZE
          , "FUSION_MAX_SET_SIZE limit is too low"
        );
    };

    template <>
    struct as_set<0>
    {
        template <typename Iterator>
        struct apply
        {
            typedef set<> type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return set<>();
        }
    };

BOOST_FUSION_BARRIER_END
}}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/set/detail/cpp03/preprocessed/as_set.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/as_set" FUSION_MAX_SET_SIZE_STR ".hpp")
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

#define BOOST_PP_FILENAME_1 <boost/fusion/container/set/detail/cpp03/as_set.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_SET_SIZE)
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
    struct as_set<N>
    {
        template <typename I0>
        struct apply
        {
            BOOST_PP_REPEAT(N, BOOST_FUSION_NEXT_ITERATOR, _)
            BOOST_PP_REPEAT(N, BOOST_FUSION_VALUE_OF_ITERATOR, _)
            typedef set<BOOST_PP_ENUM_PARAMS(N, T)> type;
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


/* as_set.hpp
CFvgw+iLyzEAV2E4PoGjcQ1m4Vp8HNfhOlyPW/FJ3IEb8HXciOdwk5Rns7SDLfg7Po11Kcsz2ASfxea4Ffvhc3gXbsM4fB4XYoEs/wuYj9txI+7EHbgLP8MX8RLuxmos+16shS9jbdyPA/AVDMUDOBwP4Rg8jNF4BKfjUZyFr6F9e5N7hhhqsr01tbDesTn2xhYYjS0xCdvgEmyHT2B73Ii++Ax2xB3YCfdjZzyKXfB17IqfoR9eQX/8GQNQqcdAbI3d0Q9vwV7YA/thEEp8YbkHiKRLhvjCj1RiOXAF9sLHcCI+jnG4CqfjEzgbVzvPu+U+HWU0Oe9eJ+e1f8OOmK+ZLkamCzWZboP8TtqI/XATSnxex70tzoWYzhCfd4/EI9mLLXE/dsCDOBwPYSS+ipPxCN6Nr+EiPIaL8QTm40k8gqfwNXwTz2IhXsR3sBrleBfr4HtYF9l3SDw4uccEP0p5tfHgzjJeE/wQe+BFvB0/xiz8BGfhZczFr3A1foPP4hXcjt/ie3gVP8JreAO/x6qVJC4L/oh++BP2xJ8xHH/BeLyBi/FXXIoUfP4bWBmLsApewur4FdbQtoM4iX9lsj4LZH2+gMG4Xf1dJPdu8DmT30VPy/p8FjviVuyDz2EEbsNkfB4zsADvxxfwYdyOK3EH/g134lO4C7fgi2hvV3LvBRubtKtcKccSbInLsAM+hMMxDyPxYZyMj+LduELa1WP4ND6Oz+FqaU9r8Atci5cxH5VCrMcauAHr4kash5vUdiX3RnCiSbvqLeUNxrbYB7tiP+yBA/B2HIhZGIqzcLDU3xCpvzB8DIfiLrwN9+MwPIDh+DoOx3M4Aj/B2/FTdMSBHYVtMBI74hi8Fe/AEIzCO3AcjsPx6GhXB0vYTzwj7epZ7Idb8Sq6VVLvPVhmSv00V87jZbq7mH9DnIgtMBrbYQz6Yyz2xHgcggk4ChPRikm4HCfhKkzGdZgi63ky7kArHsWp+E/MxC8xGytRrmnojtPxJpyBXpiDXXAm+uEs7ImzsTfOwWi8G2NxPv8l472YiQsxGxep9Sj3ELCtST0Okd+ZYdgSh6JMxwHa9XQ1ZbqbZLpaqB5v4lwfb16U480e7IV7cSK+jHG4H6fjKzgbD2j3M/GujzevyvHmMHbEI3iqGu0ugPgGpOUkJQbITtyAblvcLKfQVWyR3RmVbfEgkokNkktyFTOkJT/6rVamJe0jhfTRxxDpzA/ZqpyMe5Mc8UQ8+OEQwvdkxs01xBZJmFo8vogvBpOW8bctpEJSd4ZPYJglk3FJOX3JF0uKQRLG3x1xSOZkMh+8xHePfozD992kM6QbpOAsloEUyd+ySSGU+RrjJ+BKvudmUR9cML5CqtqVcjHMFwuyyItxtPFMoqiDC9g4m+kYFoIJJEsI0/G9Jc7h+xbKuBIdMU/CQpgOtzLsOp5CY/yTy8p0mjgoC887Y6F4T6OMDLtG2keZikj151VRY6QkTGN5cQ4uJ93wIy/0ZZzG/cmPfwehtz9pOsvBv62kYP69T2kH6IipspB/ryFpY6sc5Ps18pQYK2zklFWZL2kD369g46KqpnFXwhgezPiRpILzLKc/efDvcMo2n7/nk9bw/SAWkdwGUn7GSeDvpxleK4D5oy/D3XIwgLJiJCYY4rZEMvwIhg10xm6ZMJAyk4wxXFYyzEeRac6QrpCC+V4wkHmQGs+0x3WJwGy8QNmLGJ7Ad7dQ6go74xrKmSNxXlZiRGjp8V48BjEt6chMysmwUP6dRrJ0Y1mwgFRIslygrAy7NFMfC8ZtsDMezDKJCdN9ljMuTMQse2yYNOp+If/eQgpj+EE0xoq5hm7dWTb+ljuY5WGaLXg=
*/