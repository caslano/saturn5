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