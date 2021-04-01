#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR30_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR30_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector30_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector30_fwd.hpp")
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
    // expand vector21 to vector30
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector30_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (21, 30)
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

/* vector30_fwd.hpp
HH3b3RQxGnrqZrZHKivxp0sedqXdZXzan29vZHJJmCD8krsLAgMuywt3w9AmxQBwCNR8QPF7E5NEfvXFn9oKqlIkZAXObZcagrDw9Qols0QsHmwxDIUuKgPCULZZB5BRX8pD2une4l3s4fa4mJQ52Ny+eBuwGVGpW1FHasw5vIP21pbnm/p/HDja7NOMLokSyMDNFVHhw187K4dMzl2wf76lsCvkkWW92r+MNtE4gw8+kaHSHnIWxBcwlaKY2hVBPPOwO/LfOf5J/2LcDN1pIR2xOP6jk6k23qCQVfRynSo9FnvuzQhp6LotnunGvhxIGtTKHXzT2o5veAzceMs5qEv/KC75f96zMOc9g+jMveAcy5YoJ2+wizbcvCUP3Lwd2jWn8RJiY+8DU9NnGf1jZKY1iT1x6wMy8rs5I/jtKX54hx4XJkH2YHzxATIsf549FbyBl4Jqf2uy19Lbe9Ve3lLipwQbieZKrfgms44y8+2+tpUjRm2YVv2gCz4QqPuA0xjT704WEtJbsBaWj6LMuU3neVUqX3WsdJj9xMRLjNx5zJwfdlpZsLOcMA==
*/