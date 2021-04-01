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
H9nEujsKvLa+tfNdMvWADSrpHt9LPam5XminTST3V1+MqsUPjox1948WQ4NeOmS1jlDsGNuqkSdduCmiDvqGaL3iF8PJZKMryThkI6Sk4HmKGtxubvCFSlhr5SIFcdbCiB5bHU1daFQTNXXFlEm1kUQTztwzbIF/vAGvbhJKcVAa25/vDvk00jYP6v/WMOCT0WZqIkJIQg/W5pV5SF5lFXpUFAN6w6F4eY4BMXblhf0r0trFzfrQNP9Oh/p3dMzqrmfNh9I63BaPe7R9EoSUtb//PXuWnGMZtUmI/SrCPcfYcfxAAlb1KnyUDJMwvA+HXJmLqO6+oYEbNC5pHD8ph2DlQhh3hYwQlECMIpOqd/Ats7HpcMrUz4t34PtyKlscqZxSYD9aHL9JQaVSks/SWe4GuNLQUThnDywHAN2AqidShPzYzyEEoXfZfqVQ0vkdozTF6xT841zO9kMIOvcaw+377RsnHl4TVYJwnp/4TZkfTzaZqC9ICELANMWbXuzdQcZ1/aZKNjhPVLe0gUgdCcI5RV7fh7vpiOZOCE1NI7Dlw7Dmlo+9KWvjAA==
*/