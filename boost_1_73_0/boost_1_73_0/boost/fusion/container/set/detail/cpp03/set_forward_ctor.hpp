/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_SET_FORWARD_CTOR_09162005_1115)
#define FUSION_SET_FORWARD_CTOR_09162005_1115

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/set/detail/cpp03/set_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_SET_SIZE)
#include BOOST_PP_ITERATE()

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    set(BOOST_PP_ENUM_BINARY_PARAMS(
        N, typename detail::call_param<T, >::type arg))
        : data(BOOST_PP_ENUM_PARAMS(N, arg)) {}

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* set_forward_ctor.hpp
E2Vk4yqW0NDeoxek4M6z7qbWJppugyNf9DZ2QQ2crt3+YvFDGU0S1T+aJJA0moCYD9HDmdowhrWlG4eNnaNN8qHa0j2A404abj2Xp41HgIHUqC9XbGOmjdrOAte4fgwNsGM5Rb6p+BT6TtpmU0cC+K0xVeyj95Gqok7fW+BecAnNVR6cDy5hwoMYkXsrXDDjCf1abWBEyCNdmn4JkvEPXCpx2imVxpPGNb5KMbzPLQFytXGoO6KfE1h5hyHB/mDtjQe7SRExQGHQUfS0xxouGKmqElIViCQu9wAIi1gKcarRNh7A0DDR5W6jrs62zRGsjkezOZG4hdV2pwcH4Ix26ARwq6xHufGCqFhjkFyllcExiejVWq5eVW3U6qqq3StfZiP0r3yVjWozCCUyicEPxBZu1HO+CoDT0bz3aFXRjgHJCvVBZhhQ7FAfYIgBpbf1Id0NYQ/lnAhgIdohnhMBLPzf3ZDwP60N0/Bb33ixjS/U0ZL2rcclbnp8aqk6EyZpGDuP+bvsxbzboNNiZB+mQMs2TGVCCZtx8/0JwqRcaGNtkYy777fEYGmXnEOvNk8D1crfW/iOskZ94wXZMtfeP7iBnGfaaS4DwJETO5RdIkTPFVMh7hXlbNqOiESTdkX2ZEzbZbHbn5xBNibx
*/