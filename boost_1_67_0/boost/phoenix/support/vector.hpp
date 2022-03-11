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