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
uhV5c65t3r90U6K5jiVaBXX7PmjPjbqrXgjd2qmJnwY9OWGcTtrzTMjo6bjx+Su3RWVZh+j07YieOJjoN9QRf9R3JTo/D54rES3O2MPvOcgY9XzmVM3ra2Zp/jqRPu50HvSoTnTWbXGarSDLCSaNrzcrRSfHET10R/N0sX7k5fT4mcX3HJ2nwqLx+QO7oM6WJNpioeb1WxmiNdaE3iwGWstCnzch+vO8JrblTOB/FU6s5vUdJ8V01kbZJ92heb7/cv+u21eC1tppopMYWT0xEfTwXOjdeNTzOBg6fMs00Cfo2NU3dXsCOMp3xurI79KoT+Z+Mcr3DXc1f/uA7xXm47p/51feBnI4ESfQ98dh58uvD32ZkujBLNFn8xL9sTDwvaH7sLG/4Y+WPhD2Af27/O7u9ObfNtKbcSnRUTqu8/q8bcXPP8nZR3Ap0bnHd947CXVqzwhfBOH0nYl63A++Dj50EHo6GfL/HXyDezXO54KNz0F00wzwhyuhvLsjHXzvph50+mLowuJET1dg+5DHiyWUGXZ7GXzGLkvB1xwkzufI0fDVqMPDB0D7DKJtdoyxc5CvKWdHHe4ppvE6/N4RC8XX96Tj8zuuis+/3a17+pNX7bx+Y0Uxvx374LcWHH3/m8vQltTi671KkBmut5ibaPN5iO7F7xmbQV/PgexnRZ1eQXTbaUQz4HprtENHQ8734W/cOfAc7PHLzYl+hD3Uoed9kMGzqKOJN4a8faId1iZafSJgG6B9Q9pDL4eOFoBB3x8pw7+B7kKzQRdxvSb+fr8Ecro9ztszx6D9XBQ2uCLuow4Ogz9cEPJmjw83jX4Xh0ygyyeCXj98ygZ7Efko6zVXRP4I+T8CNlDYHm1MFboxM+ozA2Bu8IZ9BJD718hfBn+VaWE3kN9dQygzfN1ELtHn60FuaBf4Y+UJ4vOZFoQ89uLaioPZKzwT2dqix4nrLxO1X5dfw/lD+Ni7oUenXIK/W5r3Vjqs+Zu/bzSdX2EL++/dQzcP6Lz+PqL3wXxE8x3/7+l+6HJvCfy9emjz/FHk79Q62pp14Y8iH/paKK+Ju8RVsNMpjoBtg+ca6yJPcyJecmFfUfsw28LN39y48GNRPSyAZ05CG3IMUwdLo53fZN/4+iqk22dZsLyQ5Qa5LgadXxy+eXzYCTI9F+wzizjikjWgkxbSQWZ7wGdPFenjLmfgWbSviwTdZbHplVClaZrnR++BGGW97s+9uzzyjHZx57VwviHaGPzesCD8CmTyCZPHeWcG/yOb5+8gL2fOGWO/70+JjjXHidoYxA4XzoiyoE14aXrYxMrQf9TRWtNBn6Cfa6NsixwDfeqDXk4J2z+VaLU6ZA77Ph6yHMdDPuEj37wadXImnocfnOUGxBt3oE1G7LNjHjHgjrBp+ITn8NxssK+9r4dvuQq2Dru96zq0/1E7djzO14cNHBvJ8UgHfgFlP2GoexmKUVlPRhy8ZBn1cATyDbvdM7KL8Zl2ffabIppbgM+JaCPAa/X9wBtt/Iyw4/kvgO+C3a2DtCcvDl93H2x+mSgxZPBHnRId590axSOQwQ1RbHjoJPA/iEeHofOL3QbaUVxRL0f+eiBO/x7y9P3UUd1uG+npUZ08Phps/k67TvO3tgJswo/x3yD7ceEDdpsQZdoBchrlmzh6kNvv0LUHl4IeRzY96W6Q1RLN85tnbv5ugHKMN24U/0zNtD+Hx+d3Qa9eLnTncz9iEOuASE7rI0ZDXV97DyO72dE27wm+m8f3bp0OMtkXOgEdfHyK7nQLDI1XriHjxz/sXXl83EUVnzbpSaG5U6BiqYgIWNu0FKhQ2CSbZtt0N93d9EB03Wy26dJkd7tHDxA=
*/