/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_ITER_FOLD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_ITER_FOLD_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/reverse_iter_fold_fwd.hpp>
#include <boost/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/add_reference.hpp>

#define BOOST_FUSION_REVERSE_FOLD
#define BOOST_FUSION_ITER_FOLD

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/iteration/detail/preprocessed/reverse_iter_fold.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/reverse_iter_fold.hpp")
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

#undef BOOST_FUSION_REVERSE_FOLD
#undef BOOST_FUSION_ITER_FOLD

#endif

/* reverse_iter_fold.hpp
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
*/