#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4512) // assignment operator could not be generated
#pragma warning(disable: 4510) // default constructor could not be generated
#pragma warning(disable: 4610) // can never be instantiated - user defined constructor required
#endif
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#ifndef BOOST_PHOENIX_SUPPORT_VECTOR_HPP
#define BOOST_PHOENIX_SUPPORT_VECTOR_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#define BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL BOOST_FUSION_ADAPT_TPL_STRUCT

#include <boost/phoenix/support/preprocessed/vector.hpp>

#endif

#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_SUPPORT_VECTOR_HPP
#define BOOST_PHOENIX_SUPPORT_VECTOR_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#define BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL BOOST_FUSION_ADAPT_TPL_STRUCT

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif
/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define M0(Z, N, D)                                                             \
    typedef BOOST_PP_CAT(A, N) BOOST_PP_CAT(member_type, N);                    \
    BOOST_PP_CAT(A, N) BOOST_PP_CAT(a, N);                                      \
/**/
#define M1(Z, N, D)                                                             \
    (BOOST_PP_CAT(A, N))                                                        \
/**/
#define M2(Z, N, D)                                                             \
    (BOOST_PP_CAT(T, N))                                                        \
/**/
#define M3(Z, N, D)                                                             \
    (BOOST_PP_CAT(A, N), BOOST_PP_CAT(a, N))                                    \
/**/

namespace boost { namespace phoenix
{
    template <typename Dummy = void>
    struct vector0
    {
        typedef mpl::int_<0> size_type;
        static const int size_value = 0;
    };

    template <int> struct vector_chooser;

    template <>
    struct vector_chooser<0>
    {
        template <typename Dummy = void>
        struct apply
        {
            typedef vector0<> type;
        };
    };
}}


#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
        (3, (1, BOOST_PP_INC(BOOST_PHOENIX_LIMIT),                              \
        <boost/phoenix/support/vector.hpp>))
#include BOOST_PHOENIX_ITERATE()

#undef M0
#undef M1
#undef M2
#undef M3

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

namespace boost { namespace phoenix
{
    template <BOOST_PHOENIX_typename_A>
    struct BOOST_PP_CAT(vector, BOOST_PHOENIX_ITERATION)
    {
        BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M0, _)
        
        typedef mpl::int_<BOOST_PHOENIX_ITERATION> size_type;
        static const int size_value = BOOST_PHOENIX_ITERATION;

        typedef
            BOOST_PP_CAT(vector, BOOST_PP_DEC(BOOST_PHOENIX_ITERATION))<BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PHOENIX_ITERATION, A)>
            args_type;

        args_type args() const
        {
            args_type r = {BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PHOENIX_ITERATION, a)};
            return r;
        }
    };

    template <>
    struct vector_chooser<BOOST_PHOENIX_ITERATION>
    {
        template <BOOST_PHOENIX_typename_A>
        struct apply
        {
            typedef BOOST_PP_CAT(vector, BOOST_PHOENIX_ITERATION)<BOOST_PHOENIX_A> type;
        };
    };
}}

#define BOOST_PHOENIX_SUPPORT_VECTOR_ADAT_PARAM0                                \
    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M1, _)                             \
/**/
#define BOOST_PHOENIX_SUPPORT_VECTOR_ADAT_PARAM1                                \
   (                                                                            \
        BOOST_PP_CAT(                                                           \
            boost::phoenix::vector                                              \
          , BOOST_PHOENIX_ITERATION                                             \
        )                                                                       \
    )                                                                           \
    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M1, _)                             \
/**/
#define BOOST_PHOENIX_SUPPORT_VECTOR_ADAT_PARAM2                                \
    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M3, _)                             \
/**/

BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    BOOST_PHOENIX_SUPPORT_VECTOR_ADAT_PARAM0
  , BOOST_PHOENIX_SUPPORT_VECTOR_ADAT_PARAM1
  , BOOST_PHOENIX_SUPPORT_VECTOR_ADAT_PARAM2
)

#endif

#endif

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

/* vector.hpp
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
*/