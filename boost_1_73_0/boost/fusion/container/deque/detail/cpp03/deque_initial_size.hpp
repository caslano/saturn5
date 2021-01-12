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
947U9D63TcQGPMt8i6hKnCBOMe+dTz0/7/zW8ML5nkbeF7RNJ8MxZasfl2YEZV3nw2Hq+50O7wXRr7FtrfRT/aalqTY77fceJ6g8nzu855O9/8/U3Gakpqk72NJu9HcO28cy1slq1f9E1f9pRpazHZHHl58+zdHulrFMflb9RhjneqdUd4oWQJo/69RJPw6yTjcTR4kvs91DHFQ0W7n7CnVd29et0d6k1A2slrVRNrAMSbMv
*/