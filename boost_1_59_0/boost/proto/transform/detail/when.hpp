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
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
*/