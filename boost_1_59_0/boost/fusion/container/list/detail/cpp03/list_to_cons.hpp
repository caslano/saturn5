/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LIST_TO_CONS_07172005_1041)
#define FUSION_LIST_TO_CONS_07172005_1041

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/list/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#define FUSION_VOID(z, n, _) void_

namespace boost { namespace fusion
{
    struct nil_;
    struct void_;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/list/detail/cpp03/preprocessed/list_to_cons.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/list_to_cons" FUSION_MAX_LIST_SIZE_STR ".hpp")
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
    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, typename T)>
    struct list_to_cons
    {
        typedef T0 head_type;
        typedef list_to_cons<
            BOOST_PP_ENUM_SHIFTED_PARAMS(FUSION_MAX_LIST_SIZE, T), void_>
        tail_list_to_cons;
        typedef typename tail_list_to_cons::type tail_type;

        typedef cons<head_type, tail_type> type;

        #include <boost/fusion/container/list/detail/cpp03/list_to_cons_call.hpp>
    };

    template <>
    struct list_to_cons<BOOST_PP_ENUM(FUSION_MAX_LIST_SIZE, FUSION_VOID, _)>
    {
        typedef nil_ type;
    };
}}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#undef FUSION_VOID
#endif

/* list_to_cons.hpp
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
*/