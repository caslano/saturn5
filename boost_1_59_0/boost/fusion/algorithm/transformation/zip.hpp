/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_ZIP_HPP_20060125_2058)
#define FUSION_ZIP_HPP_20060125_2058

#include <boost/fusion/view/zip_view.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/support/detail/pp_round.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>

#if !defined(FUSION_MAX_ZIP_SEQUENCES)
#define FUSION_MAX_ZIP_SEQUENCES 10
#endif

#define FUSION_MAX_ZIP_SEQUENCES_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_ZIP_SEQUENCES))

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/transformation/detail/preprocessed/zip.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/zip" FUSION_MAX_ZIP_SEQUENCES_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

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
        template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PP_INC(FUSION_MAX_ZIP_SEQUENCES), typename T, fusion::void_)>
        struct zip;
    }

#define FUSION_TEXT(z, n, text) , text

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/algorithm/transformation/zip.hpp>
#define BOOST_PP_ITERATION_LIMITS (2, FUSION_MAX_ZIP_SEQUENCES)
#include BOOST_PP_ITERATE()

#undef FUSION_TEXT

}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

#else

#define ZIP_ITERATION BOOST_PP_ITERATION()

    namespace result_of
    {
        template< BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, typename T) >
        struct zip< BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, T)
                    BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(ZIP_ITERATION), FUSION_MAX_ZIP_SEQUENCES, FUSION_TEXT, void_)
        >
        {
            typedef mpl::vector< BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, T) > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }

#define FUSION_REF_PARAM(z, n, data) const T ## n&

    template<BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, typename T)>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, const T)>::type
    zip(BOOST_PP_ENUM_BINARY_PARAMS(ZIP_ITERATION, T, const& t))
    {
        fusion::vector<BOOST_PP_ENUM(ZIP_ITERATION, FUSION_REF_PARAM, _)> seqs(
            BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, t));
        return typename result_of::zip<BOOST_PP_ENUM_PARAMS(ZIP_ITERATION, const T)>::type(
            seqs);
    }

#undef FUSION_REF_PARAM
#undef ZIP_ITERATION

#endif

/* zip.hpp
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
*/