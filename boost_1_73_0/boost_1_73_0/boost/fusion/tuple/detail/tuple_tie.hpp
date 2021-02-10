/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_TUPLE_TIE_10032005_0846)
#define FUSION_TUPLE_TIE_10032005_0846

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/fusion/tuple/detail/tuple.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/tuple/detail/preprocessed/tuple_tie.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/tuple_tie" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
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
#define BOOST_FUSION_REF(z, n, data) BOOST_PP_CAT(T, n)&

#define BOOST_PP_FILENAME_1 <boost/fusion/tuple/detail/tuple_tie.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
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

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_FUSION_GPU_ENABLED
    inline tuple<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>
    tie(BOOST_PP_ENUM_BINARY_PARAMS(N, T, & arg))
    {
        return tuple<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* tuple_tie.hpp
FAEoxCyLZiRR0bNcoxYH8s3GMwe5rc9RoYqffnqmb4AZ+VqoEUpb1DK1vJ+S1MIdhB6FZ9FXFzs2Q6tpV4xuOcortumnF4pXXBPfBwupA+JitY04YScjBgISSMmYwF6r0BQ31DMOGs+3spCHWTZVQk2TdY50j/fU94syfTVZJUF+J5iqL5jNsxlGiljGMtZEOWopk+GEUil++PgCMcQ6yq10YdffHXT6e3s7/OHgvP8b/3bea3f5t7ODXk+eHh725btXvf+Q37qn8t3h4aF89e6If+m978kzTHf6+q18+Pfz036bf+22+93BWbdtfYWGee+rs9Ne3/p4qPp/+7v65aj/ln/DkAH+7bjT6w/MRxrJfKRRrI+d/7DfMx/pPfupWhG9Zz6iEVVtSLuvN+4PMxfTzPSs9qPTX7dDfrdFBSJU7vTk+D3cuhtW6mNWUFYS4Knes07/R6UQVNpRKzdiRbOWlVXQBGPd0nn2FrJg3QVyHyy7QWwFkGmbIDMdh8k7ce+FyXcmIoKlJMLNvz8LyAAAdK8pMUpyNMR33ieP+Pv5n4lDFSUXURPHaskkWqUras3ko93af09N8aNJmWe0l/ZyzGpqrQ/cL0g8tUmQqmDA/lkcS16vtKfcvo1VI9ZLgLGFtJGwFWx3iQWp
*/