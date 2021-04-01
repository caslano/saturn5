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
VWfLrFSQ8O964EVttqLEuNKdF6qsnqEIEuUpDx26BzTdlAsuRMYPqMISUltMvHn0oMXIVgLmfcDxzo5RvpgWScmWDOhy/vpXgJUydqZYNC7/vwRaYt/pW2qSawSm5CyqSA1rtjhprEFIvp/ahBeHWSVap19WM3Mpx6Ai0XX2h1xK3SKJbXNgf0gUZwtWs0/n1OdZQ5t3SmFCT0UON/VuTU8kkwAG1tImjSEQ+WazGOhezF4d5BbwNuLWU2Dss217Kuzxmx7uvoNChAGPU4d9BIwAGA67/EaY2LJJxlFLc36CdxDhpH54Jxb+1NduAQN1RSZuKlE2Zd90sAXFlP2d4agWGo9nA3Rl4vCJGq4lpVrRjq5IN//3iyOEkAnndeENhx3r0LMr0EPLcqsiLWZgN9HPcx9pMgCMCM1/OGC7G1NvoPeDkShF3Yzjb0n58WmsDTOG2Rd4KbSlBV2QIoJc10xzltaIzQHiKcsOo/xKnD3zrDMFwGKzFdqyhuZMn1A8DJdzAWJaJ/uLQ4ZArEcm9CcxOqCodNKP+mXIKU6F6UeXqYS57cmdFESuDA==
*/