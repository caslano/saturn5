/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_MAKE_VECTOR_07162005_0243)
#define FUSION_MAKE_VECTOR_07162005_0243

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/make_vector.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_vector" FUSION_MAX_VECTOR_SIZE_STR".hpp")
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
                FUSION_MAX_VECTOR_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct make_vector;

        template <>
        struct make_vector<>
        {
            typedef vector0<> type;
        };
    }

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector0<>
    make_vector()
    {
        return vector0<>();
    }

#define BOOST_FUSION_AS_FUSION_ELEMENT(z, n, data)                               \
    typename detail::as_fusion_element<BOOST_PP_CAT(T, n)>::type

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_make_vector.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_AS_FUSION_ELEMENT

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
        struct make_vector< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_VECTOR_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>
    make_vector(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& arg))
    {
        return BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_make_vector.hpp
kuZ2vCS60aNAm32AuyBBihzfd40gRUxqlQAME5N6IEGuUsKuVw5jYJwzGZb6dAN4yQQUxhMqKYBCEYLU+25Am5MgJYOB/7tySzmOEGUUWGrkBlD1784WpEV0M8c5P0oA6Ihuj5HQf/c0Uv88JyYlQaF3+gBKQcI4OT6JhjBugYON58SVn73cGjp76YoAs708nuCp2xEcxMx/x0SG5RiWF84tBDLkrNgUAW1q9lvvvRAjhmuBn07SQ2ix9r087Ay9IfQQ4ak1LA8Ebz32BeUMFpuEb4sTi0HYf1o+CTp5P2IY24ZoDLK6BycfCdrQVNNtbBbAm3he7jrHpNZAdzkzCD2e8XGyYSPFatVrR/QTfP3aQP40LRZUToWlXlcpV5WYgiJQ7I/FbS55u5C8ob/CH9WtmUnOH0s7bkFNmnw78AVfB6bNlgObIDfBfx+VfwoSlX/mYcTXoBCmUlMBzOlXwEZOTvRfEMDCl7t80S9rIEdvH0ANOa6eQBLX8iN1gHNmTWiAJBYEezgB36SYMN3GDNK8IDibxiRkqxxZxAx+k0fxCsN71lz0mOFbOkvsMYMaNZ9snvGMAb/C66tanpwEsV6GDLoTWzFO5bNWudvTw5OOYZiWc/6lrmkXrs11CKdStPW56w70iGMUZuEiBrv56u84r/vpTi4Z3u0guzqyEBLOgjjuIXaPiiHUITxs2sRnU7i26rvE/iexSV+G
*/