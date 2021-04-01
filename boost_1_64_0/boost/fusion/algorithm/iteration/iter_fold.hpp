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
hb13w81EUFEq3ZEtE9e93QY8VCx44U8nSkARmcr0VadnrZMWOMkO6iAsg1US4acu8/STs6sTDFKFY1JKwJcEOTByMy2MihgBv0Ae/rYkSj9Kas6C9acfa4x+mgRVRaFxlXmiY7ADxiHiQPNsFei5TYSyvcsmxreCs7++vs5Izfh2mUabw1C/2RlN0ynmjuHBRgD2CYVpm8XMaEDq2HsHgfsF8FLyK0tvjXYTKlN0c9Z7jbz5LhNhS+eTV2NKkZiBPlAzzawm3ECGC/u7x4vYK5CsH/Z9Kjzv5+Qs1eEstu30JPYXn93FcYJaGlZMXibnsh0Y7UOoy7jEkVU5ge9u1zj3V+SNtIkAuyWCXsRwuEUDhL5qLG/uIqZzz9OmxDVI9Sr9F+cGnWV61DrJDKeQ/xDLjeY9szVAQs6hXNY40vOb5r8UQT30V8UrmJwvh/hWw/ERVeXGnv2w/NY0ntnlzBqvfiuUF1Ugp3l4U4X7dWMJ+m8d3niolVn0V/pKSdVqp06OG2Sxs8JtKD1folfSWuJ6cWVuvFpTGZRpE2QRJCA/ozGU2Zc/ynUShA==
*/