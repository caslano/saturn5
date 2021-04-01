#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/when.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/when.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file when.hpp
    /// Definition of when transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/when.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    /// \brief A grammar element and a PrimitiveTransform that associates
    /// a transform with the grammar.
    ///
    /// Use <tt>when\<\></tt> to override a grammar's default transform
    /// with a custom transform. It is for used when composing larger
    /// transforms by associating smaller transforms with individual
    /// rules in your grammar, as in the following transform which
    /// counts the number of terminals in an expression.
    ///
    /// \code
    /// // Count the terminals in an expression tree.
    /// // Must be invoked with initial state == mpl::int_<0>().
    /// struct CountLeaves
    ///   : or_<
    ///         when<terminal<_>, mpl::next<_state>()>
    ///       , otherwise<fold<_, _state, CountLeaves> >
    ///     >
    /// {};
    /// \endcode
    ///
    /// The <tt>when\<G, R(A0,A1,...)\></tt> form accepts either a
    /// CallableTransform or an ObjectTransform as its second parameter.
    /// <tt>when\<\></tt> uses <tt>is_callable\<R\>::value</tt> to
    /// distinguish between the two, and uses <tt>call\<\></tt> to
    /// evaluate CallableTransforms and <tt>make\<\></tt> to evaluate
    /// ObjectTransforms.
    template<typename Grammar, typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct when<Grammar, R(BOOST_PP_ENUM_PARAMS(N, A))>
      : detail::when_impl<Grammar, R, R(BOOST_PP_ENUM_PARAMS(N, A))>
    {};

    #if N > 0
    /// \brief A grammar element and a PrimitiveTransform that associates
    /// a transform with the grammar.
    ///
    /// Use <tt>when\<\></tt> to override a grammar's default transform
    /// with a custom transform. It is for used when composing larger
    /// transforms by associating smaller transforms with individual
    /// rules in your grammar, as in the following transform which
    /// counts the number of terminals in an expression.
    ///
    /// \code
    /// // Count the terminals in an expression tree.
    /// // Must be invoked with initial state == mpl::int_<0>().
    /// struct CountLeaves
    ///   : or_<
    ///         when<terminal<_>, mpl::next<_state>()>
    ///       , otherwise<fold<_, _state, CountLeaves> >
    ///     >
    /// {};
    /// \endcode
    ///
    /// The <tt>when\<G, R(A0,A1,...)\></tt> form accepts either a
    /// CallableTransform or an ObjectTransform as its second parameter.
    /// <tt>when\<\></tt> uses <tt>is_callable\<R\>::value</tt> to
    /// distinguish between the two, and uses <tt>call\<\></tt> to
    /// evaluate CallableTransforms and <tt>make\<\></tt> to evaluate
    /// ObjectTransforms.
    template<typename Grammar, typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct when<Grammar, R(BOOST_PP_ENUM_PARAMS(N, A)...)>
      : detail::when_impl<Grammar, R, R(BOOST_PP_ENUM_PARAMS(N, A)...)>
    {};
    #endif

    #undef N

#endif

/* when.hpp
YC0nATlavTIzJaz2n+hSw+/FQ0DZ3hJcymd4QDcb2tmL/ngmozkHbdJdQZr2nXq5yb+fsCU4KPf38FHD5kLy2riUvbFZoFUGSk3pPlyI0vgZZyitFd6pUFbeVFRFL3cIsCvu009LopF6ssG507E0hFHZLCqe4MkPgRqDCI/GtikU3OhgWIE77uUM9ebQRvGByiZd+e9pneCAMbb2O6Nn1hf9llO8+WnKe93E3d2zbayvZtUKOMyKnGLfCoIEQ80e2aD31y1fIgJC93MalLEggHDX9vtlA7HJs3bQnfQiDVpI1GYMiwvHhDhiNKd94tMfkNcePGhUbvdYnkP8lbIgaF1MNa0VEHbAhrnZYRLO857CorNHNtSIyC7zj6KhbqDUqS7yWja5QAv9W3Yc62W4MCuFZl45IuR3jCXHrEXvKMHflOazSZCeFjRRNyYifko1QhtwtSp/5LS8iK+yfz06oR+P3U4lqWTsSlK84NVpyK8obJ9m/WPr6qPWV5hVccsde0k41wAtd3VaTpEGAeVJ9/ozN46Fz5okxppXPvoizXY/k5XdV8oA+lq/WQ==
*/