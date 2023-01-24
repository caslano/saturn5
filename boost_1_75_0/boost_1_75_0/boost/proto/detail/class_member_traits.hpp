#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/class_member_traits.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/class_member_traits.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // class_member_traits.hpp
    // Contains specializations of the class_member_traits\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/class_member_traits.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    template<typename T, typename U BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct class_member_traits<T (U::*)(BOOST_PP_ENUM_PARAMS(N, A))>
    {
        typedef U class_type;
        typedef T result_type;
    };

    template<typename T, typename U BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct class_member_traits<T (U::*)(BOOST_PP_ENUM_PARAMS(N, A)) const>
    {
        typedef U class_type;
        typedef T result_type;
    };

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* class_member_traits.hpp
dCW6E9FEMmHvq+ur74sOZYZGhkaHxoeyQ5QyH+G/mixHfrZoWbQiWhwri1XETsaysYkYxfmbiWOYhCuiWjQcjUS7o5nocHQ0OhbNRieiph5zj7XH1mPvqevResI9kZ7unkzPcM9oz1hPtmeix9Rr7rX22nrtvXW9Wm+4N9Lb3ZvpHe4d7R3rzfZO9Jpi5pg1ZovZY3UxLRaORWLdsUxsODYaGxPlm+LmuDVui9vjdaKmXE9Zx7F4Nj4R53paEzbUsk7UM4J6ZhLDidHEWCKbmEiY+sx91j5bH9db6wv3Rfq6+zJ9w32jfWN92b6JPlO/ud/ab+u399f1a/3h/kh/d3+mf7h/tH+sP9s/0W9KmpPWpC1pT9YltWQ4GUl2JzPJ4eRociyZTU4kTQPmAeuAbcA+UDegDYQHIgPdA5mB4YHRgbGB7MDEgGnQPGgdtA3aB+sGtcHwYGSwezAzODw4Ojg2mB2cGDQNmYesQ7Yh+1DdkDYUHooMdaNvhtE3Y+ibiSFTypyypmwpe6oupaXCqUiqO5VJDadGU2OpbGoiZTpiPpI9MnHEki5OW9O2dFm6Im1P16Xr0y3prvTedDSdTI+kj6XH03TUcrTsaMvRyNHhoyePorNHDeI7zabo/+pInr9+j+u/AFBLBwiWUbN+qckAAADSAQBQSwMEFAAIAAgABZIlVAAAAAAAAAAAAAAAACwAAABiaW4vVnNk
*/