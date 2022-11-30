/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_DETAIL_DEQUE_INITIAL_SIZE_26112006_2139)
#define BOOST_FUSION_DEQUE_DETAIL_DEQUE_INITIAL_SIZE_26112006_2139

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/vector.hpp>

namespace boost { namespace fusion
{
    struct void_;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/deque_initial_size.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque_initial_size" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
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
    template<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, typename T)>
    struct deque_initial_size
    {
        typedef mpl::vector<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, T)> args;
        typedef typename mpl::find<args, void_>::type first_void;
        typedef typename mpl::distance<typename mpl::begin<args>::type, first_void>::type type;
    };
}}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* deque_initial_size.hpp
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
*/