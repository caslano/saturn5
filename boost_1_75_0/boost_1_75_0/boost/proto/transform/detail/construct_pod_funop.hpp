#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/construct_pod_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/construct_pod_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file construct_pod_funop.hpp
    /// Overloads of construct_\<\>::operator().
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                         \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/construct_pod_funop.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    BOOST_FORCEINLINE
    Type operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, &a)) const
    {
        Type that = {BOOST_PP_ENUM_PARAMS(N, a)};
        return that;
    }

    #undef N

#endif

/* construct_pod_funop.hpp
wVgAXWmIH10hFzSWwNRfp1fBZbp2uhZNOrMQPKMK6j2BUQT+Sm9w1G8KmRnOOSQFX4zgPplhWtunmmLRDmGXq+SCaUhb6ca6jBYaomJr/9BR0C3uQ9yNce7RFO5NGfwgAGbmbJYNocfkp4obud1FE3uENDsv1EcOsDP+2Hlyc4GELcvdSLgs1rE0Ie9kLm/qdYGizbsuVkDrHbULXLXs7cCMnw099+mihM+oRLZh1YxTaB8Zp152GKeQWMrZTznMbhq+oQOPW5SMsOCfA4AdPaVstqCkgVaLP5rZnULBAJMb/03kx+sD2mRLMeuioYmjRnpNUs+gocHVh9at3wlTdspMX22HYiwCxFiPrIXHTb8CI0hqG/RWTk65vInuntUlUX6odw9t9DIcCz8JP5nccT8FHpSKlD/GynwNHnuJQYg94d6lnbosb9Z32yIHXjDvkDx30k98TyGIHwjCxTCgyS8ZbOIgFb6CYq9B7QK49mz2tqLuLye1GI3DpMy3F1qB2bsUaaqXVwJzDENl1iWT0U1v+KrZvmSnj3h/M+OoZrptHIrHz7klT7rfeeS6WT50uAJZichwrkwSqnrf9Ceub/Qnpg2Ig+KQNcG38d0fjQmQMtvvdeFT0dDHVmgDpDHfKJPfmlnI2s9moJG/PRl6RmvUxm//8lnly9BEY2yvJljNEVmixlHox19Y5LzOX/onOZ8toiEOcli8ubo7
*/