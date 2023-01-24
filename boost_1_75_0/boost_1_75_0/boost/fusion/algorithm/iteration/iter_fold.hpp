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
XnvmXkLlRepP40JR+dghJEgD7IXxpIewIC1DF6SZGK1Kp1VFGk73PYYrYwCCnrE0lgKtZ7n+NUTE4PVPgts3WEIFXmpE5ymbADQ2s3eYAxbD6dAKDBaxhGXKQBs2VqQ1RqO+x0JogvxohZw0uIto15dbDJh+N2NflbEvOT/NHMgnTSFUQ9XhSePhKdkddtJYYghHyjNuP1ZzaCCdNMdCTppjxpOmntuXnsvq8cMVGcYTwsEnTQbvaLIiXhRSpobrqeV6arAeT0iZZVwm1BtdXkiZQm6rhNsqxLbSQ8o4uUwBl3FimZgMOrEO8rFRz8fGQZ4SPOvtP2Xg+XLQcGI5zJEKfqQXlCdWTcQaF+kF5Ym1LGLBSXrBGC5YGLHpK/SCFi7ojFiwWwaegc/fKqUkQL/CGYhOcTzqwFw6A7uIjq2axZ8Sen8ZQMPvjtI5EEAL2+Gk9IiTUhxWbjN5PXYrkh4BJ2qVGB8KrwhA8xJtJXMGfZqvjEDD7AY8IMGLYbmJ2n6Oj854s3Z04tHkt68rNxydD9DRWWbWzyc8OnE1FfpGHp1ohd+qB9icqmZb9SVRRnD++jybAXA38y8C0Y/4FwHjW/yLwO45/kUA9ij/oi1add6pTl3twxvO47OTah0pf1KTQ+VP6s958id1tpf8SSOxnRd6jNoq9/4F525Xkd607S84d91mIyb59lz+IMXYzZRQ4uCUOE+cu7PP
*/