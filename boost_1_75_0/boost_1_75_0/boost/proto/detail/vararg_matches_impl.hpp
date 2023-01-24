#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/vararg_matches_impl.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/vararg_matches_impl.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file vararg_matches_impl.hpp
    /// Specializations of the vararg_matches_impl template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (2, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/vararg_matches_impl.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, N, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::BOOST_PP_CAT(child, BOOST_PP_DEC(N))>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::BOOST_PP_CAT(child, BOOST_PP_DEC(N))>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, N + 1, To>
        >
    {};

    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, N, N>
      : matches_<
            typename detail::expr_traits<typename Args::BOOST_PP_CAT(child, BOOST_PP_DEC(N))>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::BOOST_PP_CAT(child, BOOST_PP_DEC(N))>::value_type::proto_grammar
          , Back
        >
    {};

    #undef N

#endif

/* vararg_matches_impl.hpp
GL//tyG1NWJOmMF0+qIoTaOoOA3E+3Hend5CCD46a4Ml3deC+i3Byn+nNp38ynB6uoaDlhBP8DDmW9i4ieXULgFgATngo5PsnF+Vnlakc5+jyJdj/ypxruvMxNSPbmuk0UVYGozOV5bT6QQxN5khd8MmqyQcfWvdAy59mMVYtfnP0wlatg3lRU4VbFMnMOwG36YGnAbUFQAy+VkHOTIwb7C+2DKLroZm84q70TUBPeVmE4NeUeJXWfq4ebo+vSjxTrLADD5p7acgn6XNpLXdqwbHtuHZmbqqjo6bBHy+thUh/2+uc6f2RzGyGy4y2N7DB7vOOb4hNx8F79+Ro+LcuiF11zIZCvasirSvh2T4fZPr88jvwbXU2vPliWi7hpTUaClTFVEGXHa+dK4jPz68fYiV88jHWfBam12Y43zF37HYgLm+gHpDSM9MJMcX7jhoO/Oo9Bwqci9JHuPQjynbXCSI6fUGZyfdPKeO7yTE/AT5qyafLNSvcjb/LPTUz7gTls3OnqIJ+fEYW2ZxE22pfES9EKIpn9FK6jYzSf3UWUbQQH7yOtY+FGaAyxWTm+HHcwqaX6gP9jubIj7wJuf1/Q4erd0p0oT4h5NpOuPAM8F4yPqlPEVq+kF3q1yJTosfHs7Yv2+ZcI3Qrfh1cajqeQkzWmUkhhhgAAaDfDz0ZhTHYd9I6ajcKM1/+n+ztPY5fjOGf5k+fSZ0fIJD
*/