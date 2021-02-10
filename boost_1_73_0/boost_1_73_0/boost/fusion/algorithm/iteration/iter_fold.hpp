/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_ITER_FOLD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_ITER_FOLD_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/iter_fold_fwd.hpp>
#include <boost/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/add_reference.hpp>

#define BOOST_FUSION_ITER_FOLD

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/iteration/detail/preprocessed/iter_fold.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/iter_fold.hpp")
#endif

/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#include <boost/fusion/algorithm/iteration/detail/fold.hpp>

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#undef BOOST_FUSION_ITER_FOLD

#endif

/* iter_fold.hpp
Mf2FC46NXGUXmH5HmmPavRmOFZEd/OrrYdjX0GE2FucKjDxeMI1JkQKrxq67SGxaWlJ07/ArXwZDfhCHuWttRWqep7HRt/UGzDoex5vXb/UdFifaSBLYaLwTw+qRy+ICG7tYjLFDrj+JvfCKD8bkEVpYIDvMdsMVmVpMfZiPYskpUqUFF9iAadIYZr+IcEXZLHZF2U4farVPg53WYUWufQhDlM1iV1ShrE96g8wFNuKn5piaqcQ07VLDlE1bw0SuClZd0/XV7qq5UKlzRmInbTtCqlfA1JklMD1TXoWTPhcY1tkeF6tQX1HT5/P4PL1hkFaycBA1YO28vRGyaJbOhcs1LJ5lBykRkHfvBba6RtbK+eqQOollPbuL0/62J7Et8E7aYSMOF4y523zaM3EUG/l8oo51IVaHyxh0v+ER2QhLYtC6L5etw2DH4ndyKGaVKN6yY5gW6qlg/DMxEgNzWQvb5tjolXOKOS2l7/uLmBotLjB510bFSvMBffBRx4r0TAam+6BIeDtfxXf56RRl8VVk+HhOCfZFNYKBnQbWWurPovxNeQ11DnFrlEa7Y/gUj8T8rU5Mqlxe82B/Davr1F4PS8pprMns47WHjHxvj2LdAbDyWTSK8W8XqphTWC+PGK/XXhgxDtNj/DHm
*/