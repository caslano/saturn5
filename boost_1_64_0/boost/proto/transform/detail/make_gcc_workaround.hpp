#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #if BOOST_WORKAROUND(__GNUC__, == 3) || (BOOST_WORKAROUND(__GNUC__, == 4) && __GNUC_MINOR__ == 0)
        #include <boost/proto/transform/detail/preprocessed/make_gcc_workaround.hpp>
    #endif

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_EXPR_MAKE_ARG(Z, M, DATA)                                                   \
        detail::as_lvalue(                                                                          \
            typename when<_, BOOST_PP_CAT(A, M)>::template impl<Expr, State, Data>()(e, s, d)       \
        )                                                                                           \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_gcc_workaround.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_gcc_workaround.hpp
    /// Special workaround code to make the make\<\> transform work on certain
    /// versions of gcc.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #if BOOST_WORKAROUND(__GNUC__, == 3) || (BOOST_WORKAROUND(__GNUC__, == 4) && __GNUC_MINOR__ == 0) || \
        (defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES))

        #define BOOST_PP_ITERATION_PARAMS_1                                                         \
            (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/make_gcc_workaround.hpp>))
        #include BOOST_PP_ITERATE()

    #endif

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_EXPR_MAKE_ARG

#else

    #define N BOOST_PP_ITERATION()

    // work around GCC bug
    template<typename Tag, typename Args, long Arity BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct make<proto::expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))>
      : transform<make<proto::expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;

            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param   e
              , typename impl::state_param  s
              , typename impl::data_param   d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    BOOST_PP_ENUM(N, BOOST_PROTO_EXPR_MAKE_ARG, DATA)
                );
            }
        };
    };

    template<typename Tag, typename Args, long Arity BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct make<proto::basic_expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;

            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param   e
              , typename impl::state_param  s
              , typename impl::data_param   d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    BOOST_PP_ENUM(N, BOOST_PROTO_EXPR_MAKE_ARG, DATA)
                );
            }
        };
    };

    #undef N

#endif

/* make_gcc_workaround.hpp
qWHAsTs8DeRb3HHibXy9hOpTymJRT1zjknDUoMbeEZ2jdLP7QXYvtmbfGNmSLm8J6BsWLvvGZcTPjW/eaeqmy7VrI/Um7RxM0LB3Ndm7wkdTfHM5j29MfXhFaA1Q3q2M9eNFikRfqgsP3WDH1nfFMhjp6eFXbP7ya2Gj73NtlOYvV5CNvr/JnqlcQGcqIcreI6nuTyCh7Bk/Zw/AsaPtJpajGOgq3v77eL5Rz2cuZ+uyH2yyvvxDwp98uAkf4cuvobpcW3MdRBc+6pmSm+LrVGeJdf+PEd+Ps378Ou8uHsW+9U7shjrl3LW164wu0s6ORdbds7Bz9E9OMr4e7/za9SZ/Vbm6/xSPP+0eSpd51MCtsADz/lPP5kCfEfr+bBM+Qt+fI73c0FTjDEWtO3dU7o18DKT58k1NdhyqozHwC1TeF9n89za2z/ElMf5+meT9BvnjWyj/V5omPj8xmTvUuvyvsXW6W5m9fl3o77YmfIT+vkHyfLNm7KEnKo5bcmWxECvHTCbHHibHHUKObzfpj9gDJzm+W0uOSdwVM/veog3uFDHQXVTWD4guWmOccs40j+IMqI1JZ7KY1I5Ldu/UfY/hh3x834f95HZmW+1Mp/eKev2Y6vUj8qM/oXr9lOiO9K2rZUsljKN2L4nCFOY3f+7ru3h+iUIZM7K4Igsw95sVJusvhaz3kaxVkvV+kvWBpgnPFZay2wtbbWwvYHTfhO7J4K+ynZ/tBHvUBbA8gOzM/W98baN/c16/hmwKcBOebziE2fKDwpZ/14SPsOWHqG6/r7Wm/JzutU1teKRpUms1zoQuHu6K9IvpXhCW7O6PxPuS/9H87g96fifuBD5q1ltNVJZD1Q11nM5aPsbn/8/z/MeimvrzqYvuZfOzGP7YHzC+xoQ0rRFWs6qD4q+9PP6a4EwfH4P4nEX/C4h6kuzrzywW2Eox1tG+u5lOfOr2hadM2+n3amkeQn3hr7zfP8d9o+vYuP030UeeacJH9JG/Ux3+0STej2X3Mf/F6ncv64OqmfNHDqTx8fGf2uzQ1jXbmPJwFlN675uYunfuqlDbTTNOZEOhNGTXIKc3I88kYqSDiOcMw6OqFtH50ZnNzNfUWFtzfeWPxHg1m+pygKg37rHiI+5REu1BRIvviGft9w8Kv9xIemtodspqovzNlP9IZk/0orjvvns92bm7/tjK6jpzku8WvFXsmbaTTF+kmGkeyXRwsx0Xm9hYc2iztY35QkcvaMZH2MZhxO+FTEfXCRkOpzxX077HQsrzouZJvbUy6Xj3xcRvuc/npvnTLErDjwQd5jlFHyNlx+6XcL3v45svwbHWZO4xYt+yudZ+T8nu9+Br7TVnHP/K5T2VOSkbWy5ge0wvY+22CN/l2tXLm3XaH7cvpvZbQvQrxXkSobfgE1/ivNdjbJ64jNngccIGlzfjI2zweJLnBK/9p1ud7MO7Ru659RWm/R3aleR3XsFsot6uPbg8TN3GQMGzxhwgkgx7d6ktgMWAJzdbnaxstr79FJJlNvn2U1kbLqgfu07XKfTVRfrqbg6cp2GM9Ld3D9GvMvT0njgbU8+S51qgoQjlWU15nvLNefWMMZ8b4vdMDMyebwkhH878ePvtl+g4yMmX3UH57jLrVYCxu4sdyIdzix05ogkjPU/lOtyyTtJ7zEiXKX0z0gtU2aP/C9JHAL+d0r3If5Ta7uHXIH0s8CWWf7EqeXitj2Xsbotu/4Og9D5mPydM8n7xZ1gcEBX9INaMj2jXftL5umZx1l+sfySILsnGgO+zefd6kX8DlXMnjSEbKf8mlv9HrP++kvXf04Xcr2rGR8j9auKXqjUe7OM+ouaXbva/sTHo9Os=
*/