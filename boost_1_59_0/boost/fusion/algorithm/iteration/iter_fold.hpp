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
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
*/