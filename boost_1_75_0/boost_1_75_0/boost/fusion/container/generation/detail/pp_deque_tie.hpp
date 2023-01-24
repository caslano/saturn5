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
gomBLPHNsp9Ho19sL9MNHCdcPSSDJKro8s+W5WuwVs6W9aFan2v32SaWrbMOvn5+91qUse6wrFS5zkvKUPMvFf5SYwylIm7UQmkI+jytbnNPunu1c3aocWr82bTgNwZNSOcEBLUxR8joJH+m30mule9r9DHTyMHcmMdv5MND9F3srAjmFWPJHW6V9Ad7V0nN5Lmcv9FYunr/qQVNPDW/6eeywsl2W7UxZpRMlFJGmlpP6XvhfuKVc0B5pXKONAyL4hwIYkBYOO+iTCqj0q06D1JXsicGOJu0e1GDvYG26eBPtF70xUC098yOW1vKLkiAm9tNLeeiHvnUyHwUNcfoNUOBYkg/IXmCRMOKNhv0Z2lMDHMU/bmaWpSdepDvv3x6P+bmm7n/EOads3XNbOpXLsdg/o7EsVTPtgSfOP9fibqKlo0jg1Lmjq8Pyv9KWN/T8hyQ+jtkfyFZ+dM+zoFntEml2NUkSCbg0jvoY+RwAcG73xZbx16IAKU1HTd0u6LFyz1Rnmzk2MLASWhXUSIBkkmKd8tdzspABYgPmALz/TZYe7Z8BDqx6Vhy0LVQ/LUnqvGcFMseMglU5yUSNjQ0IcWupXl6gB5fHPYw1gbLG3MHa8pKiS3caGpkHZXDprFQYqHbVfAQM0r8rEvu6C8e8sxM1Lz4kClAEJDFsbsgnSkQQMo6XG91A35tAp4OArQLMGgq7C+ekA5RQqfl
*/