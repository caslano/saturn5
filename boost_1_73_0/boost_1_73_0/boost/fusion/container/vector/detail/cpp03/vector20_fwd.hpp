#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR20_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR20_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector20_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector20_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    // expand vector11 to vector20
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector20_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (11, 20)
    #include BOOST_PP_ITERATE()
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

#else

    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename T)>
    struct BOOST_PP_CAT(vector, BOOST_PP_ITERATION());

#endif

/* vector20_fwd.hpp
nf9kguMq6a0yLp9s9eV6gawMTaJrjITBQjNYAIwK4ROAbyWHvlLx2TzxQ+ton4RTbo+Kkqq8a+jfREfwurm5k5KBZARv7cGwDTHEHFb66xrlXuunKKRSWeVJvbpVr1rzRfuyNej0ulRd9LR3NTAwgJkQy8WasYO22o1RDFpNk8Li6870shxT0cakvTMjNyW1FAr7Oo5VVJXgYkng2OjR6l1AN5dCmHCcE6GoI6/osXCYqUViclDEXqDol+fwD+bD/ndBGOac6tciEv9H5zlbg4AOBor+0GEypWiUYrCLQ6q+9/I/rjonhe6r7A3YrEr+QPTCiz58rufCJyrDZQ2s/RR/U05PMV8ywSChsLVAt6w8SsqBVZGTS8RfRQsyQ5YDn8pNPaCXI69046cjiR4CK42rGKatXweDi/0XWgDdclquLK5j4KpkRfPGCntwdfqesaTPFzK62zAbcYL2hGLiwoiYPF/c5Si/PIGsidk9Y1VGktMa+GcLAwPTLSc3lGhbqFB3tdWUJxrmyOUwem8WcnZziJdS2b5SOcMsofumqc2USk7YB36PEiEq2qrjDxft/eh3Xac0vra9ZPcZbK+TRsqibyHppIgG6vKEYkUNFIZQcDA4m6TFqGcV96zw59NlZ4CkWDXCgbGdaRrl
*/